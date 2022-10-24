#include <iostream>
#include <thread>

using namespace std;

void fun()
{
	cout << "test" << endl;
}

class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread &_t) : t(_t) {}
	~thread_guard()
	{
		if (t.joinable());
			t.join();
	}

	/*
	删除拷贝构造和赋值运算符, 因为必须与线程绑定才能达到 RAII 的要求: 构造时初始化, 析构时 join
	所以不能有多个对象关联同一线程
	*/
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

int main()
{
	std::thread t(fun);	
	thread_guard g(t);
}
