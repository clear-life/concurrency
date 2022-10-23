#include<iostream>
#include <thread>

using namespace std;

void fun();

int main(void)
{
    std::thread t1 = std::thread(fun);  // 移动
    std::thread t2 = std::move(t1);	    // 移动
    t2 = std::thread(fun);              // 移动, 但左边是 joinable, 出错!

    return 0;
}

// std::thread 返回值
std::thread f()
{
	void fun();
	return std::thread(fun);    // 右值, 移动
}

std::thread f()
{
	void fun();
	std::thread t(fun);
	return t;                   // 右值, 移动
}

// std::thread 参数
void f(std::thread t);

void fun();
f(std::thread(fun));

std::thread t(fun);
f(std::move(t));		// t 为移后源对象