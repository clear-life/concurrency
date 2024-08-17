#include <memory>
template<typename T>
class threadsafe_queue
{
public:
    threadsafe_queue();
    threadsafe_queue(const threadsafe_queue&);
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;  // 简化代码

    void push(T val);
    
    // 传引用与返回指针
    bool try_pop(T& val);           
    std::shared_ptr<T> try_pop();   

    void wait_and_pop(T& val);
    std::shared_ptr<T> wait_and_pop();

    bool empty() const;
};