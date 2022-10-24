#include <iostream>

using namespace std;

// 递归终止函数 1
void fun()
{
}

// 递归终止函数 2
template<typename T>
void fun(T t)
{
	cout << t << endl;
}

// 展开函数
template<typename T, typename ...Args>
void fun(T head, Args... rest)
{
	cout << head << endl;
	fun(rest...);
}

int main()
{
	fun(4, 3, 2, 1);
	return 0;
}