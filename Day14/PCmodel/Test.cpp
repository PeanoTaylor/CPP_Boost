#include "Producer.h"
#include "Consumer.h"
#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

void test0(){
    TaskQueue taq(10);

    Producer pro;
    Consumer con;

    //给生产者线程注册的入口函数
    //就是Producer的produce函数
    //
    //thread的构造函数接收参数与bind类似
    //默认都是值传递效果
    thread thpro(&Producer::produce,&pro,std::ref(taq));
    thread thcon(&Consumer::consume,&con,std::ref(taq));
    
    thpro.join();
    thcon.join();
}

int main(void){
    test0();
    return 0;
}

