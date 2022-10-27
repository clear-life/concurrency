template <class T>
class unique_lock { 
public:
    // 默认构造
    unique_lock() noexcept : p_mtx(nullptr), own(false) {}

    // mutex 构造
    explicit unique_lock(T& m)
        : p_mtx(std::addressof(m)), own(false) 
    {
        p_mtx->lock();
        own = true;
    }

    // mutex 和 adopt_lock_t/defer_lock_t/try_to_lock_t 构造
    unique_lock(T& m, adopt_lock_t)
        : p_mtx(std::addressof(m)), own(true) {} // construct and assume already locked

    unique_lock(T& m, defer_lock_t) noexcept
        : p_mtx(std::addressof(m)), own(false) {} // construct but don't lock

    unique_lock(T& m, try_to_lock_t)
        : p_mtx(std::addressof(m)), own(p_mtx->try_lock()) {} // construct and try to lock

    // 时间相关的构造
    template <class _Rep, class _Period>
    unique_lock(T& m, const chrono::duration<_Rep, _Period>& _Rel_time)
        : p_mtx(std::addressof(m)), own(p_mtx->try_lock_for(_Rel_time)) {} // construct and lock with timeout

    template <class _Clock, class _Duration>
    unique_lock(T& m, const chrono::time_point<_Clock, _Duration>& _Abs_time)
        : p_mtx(std::addressof(m)), own(p_mtx->try_lock_until(_Abs_time)) {
        // construct and lock with timeout
#if _HAS_CXX20
        static_assert(chrono::is_clock_v<_Clock>, "Clock type required");
#endif // _HAS_CXX20
    }

    unique_lock(T& m, const xtime* _Abs_time)
        : p_mtx(std::addressof(m)), own(false) { // try to lock until _Abs_time
        own = p_mtx->try_lock_until(_Abs_time);
    }

    // 移动构造
    unique_lock(unique_lock&& other) noexcept : p_mtx(other.p_mtx), own(other.own) {
        other.p_mtx = nullptr;
        other.own = false;
    }

    // 移动赋值
    unique_lock& operator=(unique_lock&& other) {
        if (this != std::addressof(other)) 
        {
            if (own) 
            {
                p_mtx->unlock();
            }

            p_mtx       = other.p_mtx;
            own         = other.own;
            other.p_mtx = nullptr;
            other.own   = false;
        }
        return *this;
    }

    // 析构
    ~unique_lock() noexcept 
    {
        if (own) 
        {
            p_mtx->unlock();
        }
    }

    // 禁用拷贝构造和拷贝赋值
    unique_lock(const unique_lock&) = delete;
    unique_lock& operator=(const unique_lock&) = delete;

    void lock() 
    {
        check();
        p_mtx->lock();
        own = true;
    }

    bool try_lock() 
    {
        check();
        own = p_mtx->try_lock();
        return own;
    }

    template <class _Rep, class _Period>
    bool try_lock_for(const chrono::duration<_Rep, _Period>& _Rel_time) 
    {
        check();
        own = p_mtx->try_lock_for(_Rel_time);
        return own;
    }

    template <class _Clock, class _Duration>
    bool try_lock_until(const chrono::time_point<_Clock, _Duration>& _Abs_time) 
    {
#if _HAS_CXX20
        static_assert(chrono::is_clock_v<_Clock>, "Clock type required");
#endif // _HAS_CXX20
        check();
        own = p_mtx->try_lock_until(_Abs_time);
        return own;
    }

    bool try_lock_until(const xtime* _Abs_time) 
    {
        check();
        own = p_mtx->try_lock_until(_Abs_time);
        return own;
    }

    void unlock() 
    {
        if (!p_mtx || !own) 
        {
            _Throw_system_error(errc::operation_not_permitted);
        }

        p_mtx->unlock();
        own = false;
    }

    void swap(unique_lock& other) noexcept 
    {
        std::swap(p_mtx, other.p_mtx);
        std::swap(own, other.own);
    }

    T* release() noexcept 
    {
        T* res = p_mtx;
        p_mtx        = nullptr;
        own        = false;
        return res;
    }

    bool owns_lock() const noexcept 
    {
        return own;
    }

    explicit operator bool() const noexcept 
    {
        return own;
    }

    T* mutex() const noexcept {
        return p_mtx;
    }

private:
    T* p_mtx;       // 指向管理的 mutex 实例
    bool own;       // 是否 lock 过

    void check() const 
    { // check if the mutex can be locked
        if (!p_mtx) 
        {
            _Throw_system_error(errc::operation_not_permitted);
        }

        if (own) 
        {
            _Throw_system_error(errc::resource_deadlock_would_occur);
        }
    }
};