template <class T>
class lock_guard 
{ 
public:
    // 构造加锁
    explicit lock_guard(T& _Mtx) : m(_Mtx)   // 参数为 mutex 
    {
        m.lock();
    }

    // 不上锁
    lock_guard(T& _Mtx, adopt_lock_t) : m(_Mtx) {}   // std::adopt_lock 是 std::adopt_lock_t 类的实例

    // 析构解锁
    ~lock_guard() noexcept 
    {
        m.unlock();
    }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;

private:
    T& m;
};