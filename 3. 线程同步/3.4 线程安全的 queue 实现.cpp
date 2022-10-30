#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex m;
    std::queue<T> q;
    std::condition_variable cond;

public:
    // 默认构造与拷贝构造
    threadsafe_queue() {}
    threadsafe_queue(threadsafe_queue const& other)
    {
        std::lock_guard<std::mutex> l(other.m);
        q=other.q;
    }

    void push(T val)
    {
        std::lock_guard<std::mutex> l(m);
        q.push(val);
        cond.notify_one();
    }

    // 引用和指针
    void wait_and_pop(T& val)
    {
        std::unique_lock<std::mutex> l(m);
        cond.wait(l,[this]{return !q.empty();});

        val = q.front();
        q.pop();
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> l(m);
        cond.wait(l,[this]{return !q.empty();});

        std::shared_ptr<T> res(std::make_shared<T>(q.front()));
        q.pop();

        return res;
    }

    bool try_pop(T& val)
    {
        std::lock_guard<std::mutex> l(m);
        if(q.empty())
            return false;

        val = q.front();
        q.pop();

        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> l(m);
        if(q.empty())
            return std::shared_ptr<T>();

        std::shared_ptr<T> res(std::make_shared<T>(q.front()));
        q.pop();
        
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> l(m);
        return q.empty();
    }
};
