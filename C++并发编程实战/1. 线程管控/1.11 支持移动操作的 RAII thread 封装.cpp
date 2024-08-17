class j_thread      // j_thread 当作 thread 来用
{
    std::thread t;
public:
    // j_thread 与 thread 同生共死
    // j_thread 存在, 则 thread 存在, 否则就不存在
    j_thread() noexcept=default;    
    
    // 构造函数 RAII 获取资源
    j_thread(j_thread&& j) noexcept: t(std::move(j.t)) {}           // j_thread 移动构造
    
    explicit j_thread(std::thread &&_t) noexcept: t(std::move(_t)) {} // thread 移动构造
    
    template<typename Callable, typename Args>
    explicit j_thread(Callable&& fun, Args&& args) : 	            // 构造 thread
    	t(std::forward<Callable>(fun), std::forward<Args>(args)) {}
    
    // 移动赋值
    j_thread& operator=(j_thread&& j) noexcept
    {
        if(joinable())
            join();
        t = std::move(j.t);
        
        return *this;
    }
    
    j_thread& operator=(std::thread _t) noexcept
    {
        if(joinable())
            join();
        t = std::move(_t);
        
        return *this;
    }
    
    // 析构函数 RAII 释放资源
    ~j_thread()	noexcept							
    {
        if(joinable())
            join();
    }
    
    // 禁用拷贝构造和赋值操作
    j_thread(const j_thread &)=delete;
    j_thread& operator=(const j_thread &)=delete;
    
    // 常用操作
    void swap(j_thread& j) noexcept
    {
        t.swap(j.t);
    }
    
    std::thread::id get_id() const noexcept
    {
        return t.get_id();
	}
    
    // 模仿 thread 操作
    bool joinable() const noexcept
    {
        return t.joinable();
	}
    
    void join()
    {
        t.join();
	}
    
    void detach()
    {
        t.detach();
	}
    
    // 模仿 thread
    std::thread& as_thread() noexcept
    {
        return t;
    }
    
    const std::thread& as_thread() const noexcept
    {
        return t;
    }
}