#include <iostream>
#include <mutex>

using namespace std;

int main()
{
    std::mutex m;
    
    m.lock();
    cout << "test" << endl;
    m.unlock();
}