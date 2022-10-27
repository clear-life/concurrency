#include <mutex>
#include <memory>

std::shared_ptr<T> p;
std::mutex m;

void fun()
{
    if(!p)      // 保证了只会进行一次初始化
    {
        std::unique_lock<std::mutex> l(m);
        if(!p)
        {
            p.reset(new T);
        }
        l.unlock();
    }

    p->do_something();      // 但可能会对初始化数据进行两次操作
} 