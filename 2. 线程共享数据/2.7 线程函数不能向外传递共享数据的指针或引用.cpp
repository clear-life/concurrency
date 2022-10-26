void protect(函数指针 fun)
{
    std::lock_guard<std::mutex> l(m);	// 进入临界区
    fun(data);	// 传入保护的数据 data 的引用给外界函数 fun
}