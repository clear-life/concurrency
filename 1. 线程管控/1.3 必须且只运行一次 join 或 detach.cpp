#include <iostream>
#include <thread>

using namespace std;

void fun() {}

int main()
{
	std::thread t(fun);
	int x;
	cin >> x;

	switch (x)
	{
	case 1:
		t.join();
		t.join();
		break;
	case 2:
		t.join();
		t.detach();
		break;
	case 3:
		t.detach();
		t.join();
		break;
	case 4:
		t.detach();
		t.detach();
		break;
	case 5:
		t.join();
		break;
	case 6:
		t.detach();
		break;
	default:
		break;
	}
}
