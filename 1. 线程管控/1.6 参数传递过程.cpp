#include<iostream>
#include <thread>

using namespace std;

void fun(int& x)
{
    x = 2;
}

int main(void)
{
    int x = 1;
    std::thread t(fun, x);  
    // 编译不通过, 因为 x 会通过 值传递 方式传入 std::thread 构造函数
    // 值传递的副本临时对象(右值)再传递给线程函数, 而非 const 引用类型不能接收右值

    // 解决办法: std::ref 封装一下(猜测是传入指针)
    std::thread t(fun, std::ref(x));

    t.join();
    return 0;
}