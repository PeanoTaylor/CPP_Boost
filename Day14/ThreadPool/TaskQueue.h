/**
 * Project 66th
 */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include "Task.h"
using std::condition_variable;
using std::thread;
using std::cout;
using std::endl;
using std::mutex;
using std::queue;
using std::unique_lock;
using std::lock_guard;
using ElemType = Task *;
extern mutex countMtx;
class TaskQueue {
public: 
    
/**
 * @param capa
 */
TaskQueue(size_t capa);
~TaskQueue();
/**
 * @param value
 */
void push(ElemType ptask);
    
ElemType pop();
    
bool empty();
    
bool full();

// 唤醒阻塞队列
//线程池退出时唤醒所有阻塞在m_notEmpty上的子线程
void wakeup();

private: 
    size_t m_capacity;
    mutex m_mutex;
    queue<ElemType> m_queue;
    condition_variable m_notFull;
    condition_variable m_notEmpty;

    //添加一个标志位，参与到pop的判断中
    //为了让线程池退出时，子线程能够不再阻塞
    bool m_flag = true; 
};

#endif //_TASKQUEUE_H
