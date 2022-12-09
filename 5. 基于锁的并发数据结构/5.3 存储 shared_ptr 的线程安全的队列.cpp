#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class threadsafe_queue
{
private:
	mutable mutex m;
	condition_variable cnd;
	queue<shared_ptr<T>> q;

public:
	threadsafe_queue() {}

	void push(T x)
	{
		shared_ptr<T> p(make_shared<T>(move(x)));	// 脱离锁的保护进行内存分配

		lock_guard<mutex> l(m);
		q.push(p);
		cnd.notify_one();
	}

	viod wait_and_pop(T& x)
	{
		unique_lock<mutex> l(m);
		cnd.wait(l, [this] {return !q.empty(); });
		
		x = move(*q.front());
		q.pop();
	}

	bool try_and_pop(T& x)
	{
		lock_guard<mutex> l(m);

		if (q.empty())
			return false;

		x = move(*q.front());
		q.pop();
		return true;
	}

	shared_ptr<T> wait_and_pop()
	{
		unique_lock<mutex> l(m);
		cnd.wait(l, [this] {return !q.empty(); });

		shared_ptr<T> res = q.front();
		q.pop();
		return res;
	}

	shared_ptr<T> try_pop()
	{
		lock_guard<mutex> l(m);
		if (q.empty())
			return shared_ptr<T>();

		shared_ptr<T> res = q.front();
		q.pop();
		return res;
	}

	bool empty() const
	{
		lock_guard<mutex> l(m);
		return q.empty();
	}
};