class thread
{
private:
    struct identifier
    { 
        void* handle;     
        unsigned int id;
    } thr;

public:
    thread() : thr{} {}                   

    template<class Fn, class... Args>
    explicit thread(Fn&& func, Args&&... args)      
    { 
        _Start(std::forward<Fn>(func), std::forward<Args>(args)...);
    }

    ~thread()  
    {
        if (joinable()) 
        {
            std::terminate();
        }
    }


    thread(thread&& other)  : thr(std::exchange(other.thr, {})) {}  
    thread& operator=(thread&& other)  
    {
        if (joinable()) 
        {
            std::terminate();
        }

        thr = std::exchange(other.thr, {});
        return *this;
    }


    thread(const thread&) = delete;
    thread& operator=(const thread&) = delete;


    bool joinable() const  
    {
        return thr.id != 0;
    }

    void join() 
    {
        if (!joinable())                                        // 1. 是否 joinable
        {
            _Throw_Cpp_error(_INVALID_ARGUMENT);
        }

        if (thr.id == _Thrd_id())                               // 2. 是否是当前线程
        {
            _Throw_Cpp_error(_RESOURCE_DEADLOCK_WOULD_OCCUR);   // 资源死锁
        }

        if (_Thrd_join(thr, nullptr) != _Thrd_success)          // 3. 是否执行成功     
        {       
            _Throw_Cpp_error(_NO_SUCH_PROCESS);                 // 没有该线程
        }

        thr = {};
    }

    void detach() 
    {
        if (!joinable()) 
        {
            _Throw_Cpp_error(_INVALID_ARGUMENT);
        }

        _Check_C_return(_Thrd_detach(thr));
        
        thr = {};
    }


    void swap(thread& other)  
    {
        std::swap(thr, other.thr);
    }

    unsigned int get_id() const 
    {
        return thr.id;
    }

    static unsigned int hardware_concurrency();
};
