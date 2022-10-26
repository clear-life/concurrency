struct _identifier
{ 
    void* _HANDLE;     // Win32 HANDLE
    unsigned int _Id;
};

class thread
{
private:
    _identifier _Thr;

public:
    thread() noexcept : _Thr{} {}                   // 默认构造

    template<class _Fn, class... _Args>
    explicit thread(_Fn&& _Fx, _Args&&... _Ax)      // fun 与 args 构造 thread
    {
        _Start(std::forward<_Fn>(_Fx), std::forward<_Args>(_Ax)...);
    }

    ~thread() noexcept  // 析构
    {
        if (joinable()) {
            std::terminate();
        }
    }

    // 移动构造
    // 移动线程标识(句柄和线程 id)(原来的转移给自己, 原来变为空)
    thread(thread&& _Other) noexcept : _Thr(std::exchange(_Other._Thr, {})) {}  

    // 移动赋值
    thread& operator=(thread&& _Other) noexcept 
    {
        if (joinable()) 
        {
            std::terminate();
        }

        _Thr = std::exchange(_Other._Thr, {});
        return *this;
    }

    // 删除拷贝构造和赋值函数
    thread(const thread&) = delete;
    thread& operator=(const thread&) = delete;

    // 交换 thread 标识
    void swap(thread& _Other) noexcept {
        std::swap(_Thr, _Other._Thr);
    }

    // joinable, join 和 detach
    bool joinable() const noexcept 
    {
        return _Thr._Id != 0;
    }

    void join() 
    {
        if (!joinable())                                        // 1. 是否为 joinable
        {
            _Throw_Cpp_error(_INVALID_ARGUMENT);
        }

        if (_Thr._Id == _Thrd_id())                             // 2. 是否是当前线程执行 join
        {
            _Throw_Cpp_error(_RESOURCE_DEADLOCK_WOULD_OCCUR);   // 会发生资源死锁
        }

        if (_Thrd_join(_Thr, nullptr) != _Thrd_success)         // 3. 是否执行成功     
        {       
            _Throw_Cpp_error(_NO_SUCH_PROCESS);                 // 没有该线程
        }

        _Thr = {};      // 不再关联线程
    }

    void detach() 
    {
        if (!joinable()) 
        {
            _Throw_Cpp_error(_INVALID_ARGUMENT);
        }

        _Check_C_return(_Thrd_detach(_Thr));
        
        _Thr = {};
    }

    unsigned int get_id() const noexcept
    {
        return _Thr._Id;
    }

    // 返回句柄
    void* native_handle() noexcept  // return Win32 HANDLE as void *
    { 
        return _Thr._HANDLE;
    }

    // 硬件支持的线程数
    static unsigned int hardware_concurrency() noexcept;
};
