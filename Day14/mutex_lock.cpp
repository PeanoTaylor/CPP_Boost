#include <iostream>
#include <mutex>
#include <thread>
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::thread;
using std::unique_lock;

int cnt = 0;
mutex mtx;

void threadFunc()
{
    for (int i = 0; i < 1000000; i++)
    {
        //lock_guard<mutex> lg(mtx);
        unique_lock<mutex> ul(mtx);
        ++cnt;
        ul.unlock();
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
