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
        stk.push(move(x));	// 异常: stk 保证自身异常安全
    }

    void pop(T& x)      	// 引用式返回
    {
        lock_guard<mutex> l(m);
        if (stk.empty())	
            throw empty_stack();	// empty_stack 异常: stk 未改动, 异常安全
        x = move(stk.top());// 拷贝/移动异常: stk 未改动, 异常安全
        stk.pop();
    }

    shared_ptr<T> pop()    // 指针式返回
    {
        lock_guard<mutex> l(m);
        if (stk.empty())
            throw empty_stack();
        shared_ptr<T> const res(make_shared<T>(stk.top()));	// 异常: shared_ptr 保证不会内存泄漏
        stk.pop();			// stk.pop 保证不会异常
        return res;
    }

    bool empty() const		// 不改动数据, 异常安全
    {
        lock_guard<mutex> l(m);	
        return stk.empty();
    }
};