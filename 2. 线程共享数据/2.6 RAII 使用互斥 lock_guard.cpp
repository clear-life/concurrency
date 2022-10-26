#include <iostream>
#include <mutex>

using namespace std;

int main()
{
    std::mutex m;
    std::lock_guard<std::mutex> l(m);
    
    cout << "test" << endl;

    return 0;
}