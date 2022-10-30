#include <iostream>
#include <future>

using namespace std;

int fun()
{
    return 1;
}

int main()
{
    std::future<int> f = std::async(fun);

    cout << f.get() << endl;
}