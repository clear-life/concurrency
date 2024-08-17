class mutex : public _Mutex_base 
{ 
public:
    mutex(): _Mutex_base() {}

    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;
};

class mutex_base 
{ // base class for all mutex types
public:
    mutex_base(int flag = 0)  
    {
        _Mtx_init_in_situ(mymtx(), flag | mtx_try);
    }

    ~mutex_base()  
    {
        _Mtx_destroy_in_situ(mymtx());
    }

    mutex_base(const mutex_base&) = delete;
    mutex_base& operator=(const mutex_base&) = delete;

    void lock() 
    {
        _Check_C_return(_Mtx_lock(mymtx()));
    }

    bool try_lock() 
    {
        const auto res = _Mtx_trylock(mymtx());
        
        switch (res) 
        {
        case _Thrd_success:
            return true;
        case _Thrd_busy:
            return false;
        default:
            _Throw_C_error(res);
        }
    }

    void unlock() 
    {
        _Mtx_unlock(mymtx());
    }

private:
    struct mtx_storage;

    void* mymtx()  
    {
        return reinterpret_cast<void*>(&mtx_storage);
    }
};