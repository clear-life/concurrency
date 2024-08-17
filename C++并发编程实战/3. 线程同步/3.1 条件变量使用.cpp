#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

std::mutex m;
std::queue<int> q;
std::condition_variable flag;

void data_prepare()
{
    for(int i = 0; i < 10; i++)
    {
        {
            std::lock_guard<std::mutex> l(m);
            q.push(i);
        }
        flag.notify_one();
    }
}

void data_process()
{
    while(true)
    {
        std::unique_lock<std::mutex> l(m);

        flag.wait(l, []{ return !q.empty(); });

        int t = q.front();
        q.pop();

        l.unlock();

        cout << t << endl;

        if(q.empty())
            break;
    }
}

int main()
{
    std::thread t1(data_prepare);
    std::thread t2(data_process);

    t1.join();
    t2.join();
}