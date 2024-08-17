#include <mutex>

class level_mutex
{
public:
    explicit level_mutex(unsigned level) {}
    
    void lock() {}
    void unlock() {}
};

level_mutex high(10);
level_mutex mid(6);
level_mutex low(5);

void low_func()
{
    std::lock_guard<level_mutex> l(low);
    // ...
}

void high_func()
{
    std::lock_guard<level_mutex> l(high);   
    low_func();
}

// 正确样例
void thread_a()
{
    high_func();    // 正确: 先对 10 互斥加锁, 再对 5 互斥加锁
}

// 错误样例
void thread_b()
{
    std::lock_guard<level_mutex> l(mid);    // 错误: 先对 6 互斥加锁, 再对 10 互斥加锁
    high_func();
}
