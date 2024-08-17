#include <iostream>
#include <mutex>

using namespace std;

int main()
{
    std::recursive_mutex m;
    m.lock();
    m.lock();

    cout << "test" << endl;

    m.unlock();
    m.unlock();
}