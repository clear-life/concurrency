class condition_variable 
{ 
public:
    condition_variable() 
    {
        _Cnd_init_in_situ(mycnd());
    }

    ~condition_variable() 
    {
        _Cnd_destroy_in_situ(mycnd());
    }

    condition_variable(const condition_variable&) = delete;
    condition_variable& operator=(const condition_variable&) = delete;

    // V 操作
    void notify_one() 
    {   
        _Cnd_signal(mycnd());
    }

    void notify_all() 
    {   
        _Cnd_broadcast(mycnd());
    }

    // P 操作
    void wait(unique_lock<mutex>& lck) 
    {   
        _Cnd_wait(mycnd(), lck.mutex()->mymtx());
    }

    template <class Func>
    void wait(unique_lock<mutex>& lck, Func func) 
    {   // 除了要有 V 操作(signal), 对应的条件也得满足
        while (!func()) 
        {
            wait(lck);
        }
    }


    // 时间段
    template <class _Rep, class _Period>
    int wait_for(unique_lock<mutex>& lck, const chrono::duration<_Rep, _Period>& rel_time) {}

    template <class _Rep, class _Period, class Func>
    bool wait_for(unique_lock<mutex>& lck, const chrono::duration<_Rep, _Period>& rel_time, Func func) {}


    // 时间点
    template <class _Clock, class _Duration>
    int wait_until(unique_lock<mutex>& lck, const chrono::time_point<_Clock, _Duration>& abs_time) {}

    template <class _Clock, class _Duration, class Func>
    bool wait_until(unique_lock<mutex>& lck, const chrono::time_point<_Clock, _Duration>& abs_time, Func func) {}

private:
    struct cnd_storage;

    void* mycnd() 
    {  
        return reinterpret_cast<void*>(&cnd_storage);
    }
};