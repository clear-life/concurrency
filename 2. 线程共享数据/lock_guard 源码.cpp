template <class mutex>
class lock_guard 
{ 
public:
    lock_guard(mutex& mtx) : m(mtx)   
    {
        m.lock();
    }
    lock_guard(mutex& mtx, adopt_lock_t) : m(mtx) {}    // adopt_lock_t 是空 struct 类型

    ~lock_guard() 
    {
        m.unlock();
    }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;

private:
    mutex& m;
};