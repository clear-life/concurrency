#include <iostream>
#include <thread>

using namespace std;

void fun()
{
	cout << "Hello Concurrent World" << endl;
}

int main()
{
	std::thread t(fun);		
	t.join();
}
