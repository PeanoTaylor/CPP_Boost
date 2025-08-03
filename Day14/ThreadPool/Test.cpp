#include <iostream>
#include <memory>
#include "ThreadPool.h"
using std::cout;
using std::end;
using std::unique_ptr;
mutex countMtx;
class TaskA:public Task{
public:
    void process() override{
        srand(clock());
        int num = rand()% 100;
        {
            lock_guard<mutex> lg(countMtx);
        }
    }
};

void test0(){
    unique_ptr<Task> pt(new TaskA());
    ThreadPool pool(4,10);
    pool.start();

    int cnt = 20;
    while(cnt--){
        pool.addTask(pt.get());
        cout << cnt << endl;
    }
    pool.stop();
}

int main()
{
    test0();
    return 0;
}

