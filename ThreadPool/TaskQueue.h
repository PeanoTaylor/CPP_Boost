/**
 * Project 66th
 * 线程安全的任务队列，支持多生产多消费
 */
#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include "Task.h"

using std::thread;
using std::condition_variable;
using std::cout;
using std::endl;
using std::mutex;
using std::queue;
using std::unique_lock;
using std::lock_guard;

extern mutex coutMtx;          // 用于打印输出时同步
using ElemType = Task *;       // 队列元素类型，指向Task的指针

class TaskQueue {
public:
    // 构造，指定最大容量
    TaskQueue(size_t capa);

    ~TaskQueue();

    // 任务入队（生产者调用）
    void push(ElemType value);

    // 任务出队（消费者/线程池线程调用）
    ElemType pop();

    // 判断队列是否为空
    bool empty();

    // 判断队列是否已满
    bool full();

    // 唤醒所有等待线程，让其退出
    void wakeup();

private:
    size_t m_capacity;                 // 队列最大容量
    mutex m_mutex;                     // 互斥锁，保护队列
    queue<ElemType> m_queue;           // STL队列存储任务
    condition_variable m_notFull;      // 用于控制队列未满条件
    condition_variable m_notEmpty;     // 用于控制队列非空条件
    bool m_flag = true;                // 控制线程池退出标记
};

#endif //_TASKQUEUE_H
