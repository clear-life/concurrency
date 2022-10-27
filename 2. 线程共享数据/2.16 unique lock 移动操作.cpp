#include <mutex>

std::unique_lock<std::mutex> get_lock()
{
    extern std::mutex m;
    std::unique_lock<std::mutex> l(m);

    // prepare

    return l;
}

void fun()
{
    std::unique_lock<std::mutex> l(get_lock());
    
    // do something, 持有互斥
}