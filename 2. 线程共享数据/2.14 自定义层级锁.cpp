#include <mutex>
#include <stdexcept>
#include <climits>
class hierarchical_mutex    
{
    std::mutex m;  // 内部锁
    unsigned long const level;  // 实例的层级
    unsigned long this_thread_pre_level;    // 记录 this_thread 的上一层级
    static thread_local unsigned long this_thread_level;  // 当前线程最新层级

    void check()
    {
        // 此次加锁的层级必须比当前线程的上一次加锁层级低, 即 level < this_thread_level
        if(level >= this_thread_level)      
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update()
    {
        this_thread_pre_level = this_thread_level;  // 恢复现场对应的步骤
        this_thread_level = level;
    }
public:
    explicit hierarchical_mutex(unsigned long value):
        level(value),
        this_thread_pre_level(0)
    {}

    void lock()
    {
        check();
        m.lock();          // m.lock() 之后, m.unlock() 之前, 拥有互斥, 不必担心破坏不变量
        update();
    }

    void unlock()
    {
        this_thread_level = this_thread_pre_level;  // 类似于恢复现场
        m.unlock();
    }

    bool try_lock()
    {
        check();
        if(!m.try_lock())
            return false;
        update();
        return true;
    }
};
thread_local unsigned long hierarchical_mutex::this_thread_level(ULONG_MAX);     // 初始化为 ULONG_MAX 

int main()
{
    hierarchical_mutex m1(42);
    hierarchical_mutex m2(2000);
}
