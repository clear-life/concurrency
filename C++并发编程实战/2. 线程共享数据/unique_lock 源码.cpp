class unique_lock 
{
public:
    unique_lock(): pmtx(nullptr), own(false) {}

    unique_lock(_Mutex& mtx): pmtx(std::addressof(mtx)), own(false) 
    { 
        pmtx->lock();
        own = true;
    }

    unique_lock(_Mutex& mtx, adopt_lock_t): pmtx(std::addressof(mtx)), own(true) {}

    unique_lock(_Mutex& mtx, defer_lock_t): pmtx(std::addressof(mtx)), own(false) {}

    unique_lock(_Mutex& mtx, try_to_lock_t): pmtx(std::addressof(mtx)), own(pmtx->try_lock()) {}

    // 时间段和时间点
    template <class _Rep, class _Period>
    unique_lock(_Mutex& mtx, const chrono::duration<_Rep, _Period>& rel_time)
        : pmtx(std::addressof(mtx)), own(pmtx->try_lock_for(rel_time)) {}

    template <class _Clock, class _Duration>
    unique_lock(_Mutex& mtx, const chrono::time_point<_Clock, _Duration>& abs_time)
        : pmtx(std::addressof(mtx)), own(pmtx->try_lock_until(abs_time)) {}


    // 移动操作
    unique_lock(unique_lock&& other): pmtx(other.pmtx), own(other.own) 
    {
        other.pmtx = nullptr;
        other.own = false;
    }

    unique_lock& operator=(unique_lock&& other) 
    {
        if (this != std::addressof(other)) 
        {
            if (own) 
            {
                pmtx->unlock();
            }

            pmtx        = other.pmtx;
            own         = other.own;
            other.pmtx  = nullptr;
            other.own   = false;
        }
        return *this;
    }

    ~unique_lock()  
    {
        if (own) 
        {
            pmtx->unlock();
        }
    }

    unique_lock(const unique_lock&) = delete;
    unique_lock& operator=(const unique_lock&) = delete;

    void lock() 
    { 
        check();
        pmtx->lock();
        own = true;
    }

    bool try_lock() 
    {
        check();
        own = pmtx->try_lock();
        return own;
    }

    template <class _Rep, class _Period>
    bool try_lock_for(const chrono::duration<_Rep, _Period>& rel_time) 
    {
        check();
        own = pmtx->try_lock_for(rel_time);
        return own;
    }

    template <class _Clock, class _Duration>
    bool try_lock_until(const chrono::time_point<_Clock, _Duration>& abs_time) 
    {
        check();
        own = pmtx->try_lock_until(abs_time);
        return own;
    }

    void unlock() 
    {
        if (!pmtx || !own) 
        {
            _Throw_system_error(errc::operation_not_permitted);
        }

        pmtx->unlock();
        own = false;
    }

    void swap(unique_lock& other)  
    {
        std::swap(pmtx, other.pmtx);
        std::swap(own, other.own);
    }

    _Mutex* release()  
    {
        _Mutex* res = pmtx;
        pmtx        = nullptr;
        own         = false;
        return res;
    }

    bool owns_lock() const  
    {
        return own;
    }

    operator bool() const  
    {
        return own;
    }

    _Mutex* mutex() const  
    {
        return pmtx;
    }

private:
    _Mutex* pmtx;   // 指向管理的 mutex
    bool own;       // 是否拥有互斥

    void check() const 
    { 	// 检测能否 lock
        if (!pmtx) 
        {
            _Throw_system_error(errc::operation_not_permitted);
        }

        if (own) 
        {
            _Throw_system_error(errc::resource_deadlock_would_occur);
        }
    }
};