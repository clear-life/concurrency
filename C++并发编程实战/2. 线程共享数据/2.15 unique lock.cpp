#include <mutex>

void swap(int& l, int& r);

class A
{
public:
    int x;
    std::mutex m;

public:
    A(int const &_x) : x(_x) {}

    friend void swap(A& l, A& r)
    {
        if(&l == &r)
            return;
        
        // 用法 1: adopt_lock 假定已 lock
        std::lock(l.m, r.m);
        std::unique_lock<std::mutex> u1(l.m, std::adopt_lock);  
        std::unique_lock<std::mutex> u2(r.m, std::adopt_lock);

        // 用法 2: defer_lock 构造时不 lock
        std::unique_lock<std::mutex> u1(l.m, std::defer_lock);  
        std::unique_lock<std::mutex> u2(r.m, std::defer_lock);
        std::lock(u1, u2);

        // 用法 3: try_to_lock 构造时 try_lock
        std::unique_lock<std::mutex> u1(l.m, std::try_to_lock);  
        std::unique_lock<std::mutex> u2(r.m, std::try_to_lock);

        // 用法 4: 构造时 lock, 相当于 std::lock_guard
        std::unique_lock<std::mutex> u1(l.m);  
        std::unique_lock<std::mutex> u2(r.m);

        swap(l.x, r.x);
    }
};