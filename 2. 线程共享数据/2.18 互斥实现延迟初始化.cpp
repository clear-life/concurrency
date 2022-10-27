#include <mutex>
#include <memory>

std::shared_ptr<T> p;
std::mutex m;

void fun()
{
    std::unique_lock<std::mutex> l(m);
    if(!p)      // 仅在第一次使用时初始化
    {
        p.reset(new T);
    }
    l.unlock();

    p->do_something();
} 