#include <mutex>
#include <list>

std::list<int> l;
std::mutex m;		// 使 add 和 find 操作互斥 

void add(int x)
{
    std::lock_guard<std::mutex> guard(m);

    l.push_back(x);
}

bool find(int x)
{
    std::lock_guard<std::mutex> guard(m);
    
    return std::find(l.begin(), l.end(), x) != l.end();
}