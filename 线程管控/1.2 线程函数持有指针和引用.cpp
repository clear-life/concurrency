#include <iostream>
#include <thread>

using namespace std;

void fun(int& x);	// 线程函数有指针和引用参数, 隐患: 线程内可能会访问已经销毁的局部变量

int main()
{
	int x;
	std::thread t(fun, std::ref(x));	
	t.detach();
}
