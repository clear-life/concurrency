#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

// std::mutex m;               // 会死锁
std::recursive_mutex m;     // 不会死锁

void fun(int u)
{
    // std::lock_guard<std::mutex > l(m);
    std::lock_guard<std::recursive_mutex > l(m);

    cout << u << endl;
    if (u == 0)
        return;
    fun(u - 1);
}

int main()
{
    std::thread t(fun, 3);
    t.join();
}