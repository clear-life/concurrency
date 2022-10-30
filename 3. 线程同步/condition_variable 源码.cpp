class condition_variable 
{ // class for waiting for conditions
public:
    condition_variable();

    ~condition_variable();

    condition_variable(const condition_variable&) = delete;
    condition_variable& operator=(const condition_variable&) = delete;

    void notify_one();  // 唤醒一个阻塞线程

    void notify_all();  // 唤醒所有阻塞线程

    void wait(unique_lock<mutex>& _Lck);    // 等待信号

    template <class _Predicate>
    void wait(unique_lock<mutex>& _Lck, _Predicate _Pred)   // 等待信号 and 测试断言
    { 
        while (!_Pred()) 
        {
            wait(_Lck);
        }
    }
};