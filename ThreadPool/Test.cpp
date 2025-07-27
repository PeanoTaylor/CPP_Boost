#include <memory>
#include <iostream>
#include "ThreadPool.h"

using std::cout;
using std::endl;
using std::unique_ptr;
mutex coutMtx; // 用于cout输出时多线程同步

// 一个简单的自定义任务类，实现process方法
class TaskA: public Task{
public:
    void process() override{
        srand(clock());
        int num = rand() % 100;
        {
            lock_guard<mutex> lg(coutMtx); // 避免输出交叉
            cout << "TaskA number = " 
                << num << endl;
        }
    }
};

void test(){
    ThreadPool pool(4,10); // 4个线程，队列最多10个任务
    pool.start();

    int cnt = 20;
    while(cnt--){
        // 生产20个任务，投递到线程池
        pool.addTask(new TaskA());
    }

    pool.stop(); // 等待所有任务执行完后安全退出
}

int main()
{
    test();
    return 0;
}
