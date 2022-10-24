#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout << std::this_thread::get_id() << endl;             // 当前线程的 ID
    cout << std::thread::hardware_concurrency() << endl;    // 硬件支持的最大线程数
}