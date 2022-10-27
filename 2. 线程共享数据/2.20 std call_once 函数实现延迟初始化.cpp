#include <mutex>

std::once_flag flag;

void init();    // 初始化函数

void fun()
{
    std::call_once(flag, init); // 当成线程安全且只调用一次的初始化语句
    
    // 正常访问
}