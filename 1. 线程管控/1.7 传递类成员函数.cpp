#include<iostream>
#include <thread>

using namespace std;

class A
{
public:
    void fun()
    {
        cout << "test" << endl;
    }
};

int main(void)
{
    A a;
    std::thread t(&A::fun, &a);

    t.join();
    return 0;
}