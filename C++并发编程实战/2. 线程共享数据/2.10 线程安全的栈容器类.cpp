#include <mutex>
#include <stack>
#include <exception>

using namespace std;

struct empty_stack : exception
{
    const char* what() const throw();
};


template<typename T>
class threadsafe_stack
{
private:
    stack<T> stk;
    mutable mutex m;
public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack& other)
    {
        lock_guard<mutex> l(other.m); 
        stk = other.stk;                            
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T x)
    {
        lock_guard<mutex> l(m);
        stk.push(move(x));
    }

    void pop(T& x)      	// 引用式返回
    {
        lock_guard<mutex> l(m);
        if (stk.empty())
            throw empty_stack();
        x = move(stk.top());
        stk.pop();
    }

    shared_ptr<T> pop()    // 指针式返回
    {
        lock_guard<mutex> l(m);
        if (stk.empty())
            throw empty_stack();
        shared_ptr<T> const res(make_shared<T>(stk.top()));
        stk.pop();
        return res;
    }

    bool empty() const
    {
        lock_guard<mutex> l(m);
        return stk.empty();
    }
};