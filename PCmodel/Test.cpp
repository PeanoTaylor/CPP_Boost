#include "Producer.h"
#include "Consumer.h"
#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;
mutex coutMtx;
int main()
{
    TaskQueue taskQue(10);

    Producer producer;
    Consumer consumer;

    thread pro(&Producer::produce,&producer,std::ref(taskQue));
    thread con(&Consumer::consume,&consumer,std::ref(taskQue));

    pro.join();
    con.join();
    return 0;
}

