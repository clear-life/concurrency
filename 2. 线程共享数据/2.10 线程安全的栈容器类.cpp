#include <mutex>
#include <stack>

using namespace std;

struct empty_stack : std::exception
{
    const char* what() const throw();
};


template<typename T>
class threadsafe_stack
{
private:
    std::stack<T> stk;
    mutable std::mutex m;
public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> l(other.m);     // mutable 保证了 m 在任何情况下都能被修改
        stk = other.stk;                            // 函数体内复制在 mutex 的保护范围内
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T x)
    {
        std::lock_guard<std::mutex> l(m);
        stk.push(std::move(x));
    }

    void pop(T& x)      // 传入引用
    {
        std::lock_guard<std::mutex> l(m);
        if (stk.empty())
            throw empty_stack();
        x = stk.top();
        stk.pop();
    }

    std::shared_ptr<T> pop()    // 返回指针
    {
        std::lock_guard<std::mutex> l(m);
        if (stk.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(stk.top()));
        stk.pop();
        return res;
    }

    bool empty() const;
};