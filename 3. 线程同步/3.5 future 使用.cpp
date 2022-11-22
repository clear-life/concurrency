#include <iostream>
#include <future>

using namespace std;

int fun(int)
{
    return 1;
}

int main()
{
    std::future<int> f = std::async(fun, 1);

    cout << f.get() << endl;
}