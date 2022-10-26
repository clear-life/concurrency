class _Mutex_base       // base class for all mutex types
{ 
public:
    _Mutex_base(int _Flags = 0) noexcept 
    {
        _Mtx_init_in_situ(_Mymtx(), _Flags | _Mtx_try);
    }

    ~_Mutex_base() noexcept 
    {
        _Mtx_destroy_in_situ(_Mymtx());
    }

    _Mutex_base(const _Mutex_base&) = delete;
    _Mutex_base& operator=(const _Mutex_base&) = delete;

    void lock() 
    {
        _Check_C_return(_Mtx_lock(_Mymtx()));
    }

    bool try_lock() 
    {
        const auto _Res = _Mtx_trylock(_Mymtx());
        switch (_Res) {
        case _Thrd_success:
            return true;
        case _Thrd_busy:
            return false;
        default:
            _Throw_C_error(_Res);
        }
    }

    void unlock() 
    {
        _Mtx_unlock(_Mymtx());
    }

    void* native_handle() 
    {
        return _Mtx_getconcrtcs(_Mymtx());
    }

private:
    friend condition_variable;
    friend condition_variable_any;

    aligned_storage_t<_Mtx_internal_imp_size, _Mtx_internal_imp_alignment> _Mtx_storage;

};

class mutex : public _Mutex_base 
{ 
public:
    mutex() noexcept : _Mutex_base() {}

    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;
};

class recursive_mutex : public _Mutex_base 
{ 
public:
    recursive_mutex() : _Mutex_base(_Mtx_recursive) {}

    bool try_lock() noexcept 
    {
        return _Mutex_base::try_lock();
    }

    recursive_mutex(const recursive_mutex&) = delete;
    recursive_mutex& operator=(const recursive_mutex&) = delete;
};