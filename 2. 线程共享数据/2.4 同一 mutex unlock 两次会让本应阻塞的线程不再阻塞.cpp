#include <iostream>
#include <mutex>

using namespace std;

// unlock 两次对本身而言没有问题
// 但对别的线程而言, 其本应被阻塞, 却因为多 unlock 了一次而不被阻塞进入临界区
// 所以第二次 unlock 不会成功
int main()
{
    std::mutex m;

    m.lock();
    cout << "test" << endl;
    m.unlock();
    m.unlock();     // 不会成功

    m.lock();
    m.lock();       // 依旧会阻塞
    cout << "test" << endl;
    m.unlock();
}