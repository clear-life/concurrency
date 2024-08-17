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
        
        // 相当于 std::lock 和 std::lock_guard 结合
    	std::scoped_lock guard(l.m, r.m);

        swap(l.x, r.x);
    }
};