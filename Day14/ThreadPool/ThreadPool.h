/**
 * Project 66th
 */


#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include "TaskQueue.h"
#include <vector>
using std::vector;

class ThreadPool {
public: 
    
/**
 * @param threadNum
 * @param queSize
 */
// 构造函数的两个参数代表子线程的个数和任务队列的容量
ThreadPool(size_t threadNum, size_t queSize);

~ThreadPool();
    
void start();
    
void stop();
    
/**
 * @param ptask
 */
void addTask(Task * ptask);
protected: 
    

private: 
    size_t m_threadsNum;
    vector<thread> m_threads;
    size_t m_queSize;
    TaskQueue m_taskQue;
    bool m_isExit;
    
Task * getTask();
    
void doTask();
};

#endif //_THREADPOOL_H
