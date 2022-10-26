#include <mutex>

void swap(int& l, int& r);

class A
{
private:
    int x;
    std::mutex m;

public:
    A(int const &_x) : x(_x) {}

    friend void swap(A& l, A& r)
    {
        if(&l == &r)
            return;
        
        std::lock(l.m, r.m);
        std::lock_guard<std::mutex> lock_a(l.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(r.m, std::adopt_lock);

        swap(l.x, r.x);
    }
};