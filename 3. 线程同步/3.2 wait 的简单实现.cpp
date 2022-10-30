template<typename Func>
void condition_variable::wait(unique_lock<mutex>& l, Func func)
{
    while(!func())
    {
        l.unlock();			// 必须使用 std::unique_lock 的原因: 灵活上锁解锁
    
        // 阻塞, 等待条件变量通知
        wait_for_cnd();

        l.lock();
    }
}