#include <iostream>
#include <thread>
#include <mutex>
using std::mutex;
using std::cout;
using std::endl;
using std::thread;

int cnt = 0;
mutex mtx;


void threadFunc()
{
    for (int i = 0; i < 1000000; ++i)
    {
        mtx.lock();
        ++cnt;
        mtx.unlock();
    }
}

int main()
{ 
    thread th1(threadFunc);
    thread th2(threadFunc);
    th1.join();
    th2.join();
    cout << "cnt = " << cnt << endl;
    return 0;
}
