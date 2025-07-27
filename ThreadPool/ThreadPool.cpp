/**
 * Project 66th
 * ThreadPool实现
 */
#include "ThreadPool.h"
#include <unistd.h>   // for sleep
#include <iostream>

using std::cout;
using std::endl;

/**
 * 构造函数
 * @param threadNum 工作线程数
 * @param queSize   任务队列容量
 */
ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    :m_threadsNum(threadNum)
    ,m_threads()
    ,m_queSize(queSize)
    ,m_taskQue(m_queSize)
    ,m_isExit(false) {}

/**
 * 启动线程池，创建并启动所有worker线程
 */
void ThreadPool::start() {
    for(int idx = 0; idx < m_threadsNum; ++idx){
        // 每个线程都运行成员函数doTask
        m_threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

/**
 * 停止线程池
 * 等待任务队列清空，然后标记退出，唤醒所有阻塞线程，并等待它们结束
 */
void ThreadPool::stop() {
    // 1.等待所有任务执行完（队列清空）
    while(!m_taskQue.empty()){
        sleep(1);
    }
    // 2.设置线程池退出标志
    m_isExit = true;
    // 3.唤醒所有等待中的线程
    m_taskQue.wakeup();
    // 4.等待所有子线程结束
    for(auto &th : m_threads){
        th.join();
    }
}

/**
 * 添加任务到线程池
 * @param ptask 任务指针
 */
void ThreadPool::addTask(ElemType ptask) {
    if(ptask){
        m_taskQue.push(ptask);
    }else{
        cout << "add nullptr" << endl;
    }
}

ThreadPool::~ThreadPool() {}

/**
 * 获取任务
 * @return 下一个待执行的任务指针
 */
ElemType ThreadPool::getTask() {
    return m_taskQue.pop();
}

/**
 * worker线程主循环
 * 不断从队列取任务并执行
 */
void ThreadPool::doTask() {
    while(!m_isExit || !m_taskQue.empty()){ // 优化：确保所有任务都执行完才退出
        ElemType ptask = getTask();
        if(ptask){
            ptask->process();
            // 注意：此处未释放任务内存，建议用unique_ptr或外部管理
        }else{
            // 若线程池关闭且无任务，返回nullptr，线程退出
        }
    }
}
