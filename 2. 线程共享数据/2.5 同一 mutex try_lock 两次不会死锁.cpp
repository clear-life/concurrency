#include <iostream>
#include <mutex>

using namespace std;

int main()
{
    std::mutex m;

    if (m.try_lock())        // 加锁成功
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    if (m.try_lock())        // 加锁失败
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    cout << "test" << endl;

    m.unlock();
}