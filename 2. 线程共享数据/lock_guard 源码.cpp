#include <mutex>

template <class T>
class lock_guard 
{ 
public:
    using mutex_type = T;

    // 构造加锁
    explicit lock_guard(T& _Mtx) : _MyMutex(_Mtx)   // 参数为 mutex 
    {
        _MyMutex.lock();
    }

    // 不上锁
    lock_guard(T& _Mtx, adopt_lock_t) : _MyMutex(_Mtx) {}   // std::adopt_lock 是 std::adopt_lock_t 类的实例

    // 析构解锁
    ~lock_guard() noexcept 
    {
        _MyMutex.unlock();
    }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;

private:
    T& _MyMutex;
};