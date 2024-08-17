#include <future>
template<typename F,typename A>
std::future<result_type> spawn_task(F&& f,A&& a)        // 返回与 packaged_task 关联的 future
{
    std::packaged_task<result_type> task(std::move(f)); // packaged_task 关联函数 f , 函数 f 的返回值类型是 result_type
    std::future<result_type> res(task.get_future());    // packaged_task 关联 future

    std::thread t(std::move(task),std::move(a));        // 新开线程异步运行 packaged_task
    t.detach();

    return res;
}