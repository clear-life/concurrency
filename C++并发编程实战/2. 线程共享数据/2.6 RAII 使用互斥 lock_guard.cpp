#include <iostream>
#include <mutex>

using namespace std;

int main()
{
    std::mutex m;
    std::lock_guard<std::mutex> l(m);	// 构造时加锁
    
    cout << "test" << endl;

    return 0;		// 析构时解锁
}