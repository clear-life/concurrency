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
	queue<T> q;

public:
	threadsafe_queue(){}

	void push(T x)
	{
		lock_guard<mutex> l(m);
		q.push(move(x));
		cnd.notify_one();
	}

	void wait_and_pop(T& x)
	{
		unique_lock<mutex> l(m);
		cnd.wait(l, [this] {return !q.empty(); });
		x = move(q.front());
		q.pop();
	}

	shared_ptr<T> wait_and_pop()
	{
		unique_lock<mutex> l(m);
		cnd.wait(l, [this] {return !q.empty(); });

		shared_ptr<T> res(make_shared<T>(move(q.front())));
		q.pop();

		return res;
	}

	bool try_pop(T& x)
	{
		lock_guard<mutex> l(m);
		if (q.empty())
			return false;

		x = move(q.front());
		q.pop();
		return true;
	}

	shared_ptr<T> try_pop()
	{
		lock_guard<mutex> l(m);
		if (q.empty())
			return shared_ptr<T>();

		shared_ptr<T> res(make_shared(move(q.front())));
		q.pop();
		return res;
	}

	bool empty() const
	{
		lock_guard<mutex> l(m);
		return q.empty();
	}
};