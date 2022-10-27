void fun()
{
    std::mutex m;
    std::unique_lock<std::mutex> l(m);  // 构造时 lock
    // 访问共享数据
    l.unlock();     // 手动解锁
    // 不访问共享数据
    l.lock();       // 手动加锁
    // 访问共享数据
}   // 析构解锁