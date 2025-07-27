/**
 * Project 66th
 * 线程池实现，自动管理多个worker线程和任务队列
 */
#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include "TaskQueue.h"

using std::vector;

class ThreadPool {
public:
    // 构造，threadNum线程数，queSize队列大小
    ThreadPool(size_t threadNum, size_t queSize);

    // 启动线程池，创建所有worker线程
    void start();

    // 停止线程池，等待任务全部处理完成后退出
    void stop();

    // 添加任务到线程池
    void addTask(ElemType ptask);

    ~ThreadPool();

private:
    size_t m_threadsNum;           // 线程数
    vector<thread> m_threads;      // worker线程容器
    size_t m_queSize;              // 队列容量
    TaskQueue m_taskQue;           // 任务队列
    bool m_isExit;                 // 线程池退出标志

    // 从队列取任务
    ElemType getTask();

    // worker线程主函数
    void doTask();
};

#endif //_THREADPOOL_H
