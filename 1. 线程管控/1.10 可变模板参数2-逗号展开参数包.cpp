#include <iostream>

using namespace std;

template<typename T>
void print(T t)         // 处理参数包的参数
{
    cout << t << endl;
}

template<typename ...Args>
void fun(Args... args)  // 访问参数包的每个参数
{
    int arr[] = {(print(args), 0)...};  // 利用逗号和初始化列表的特性
}

int main()
{
	fun(4, 3, 2, 1);
	return 0;
}