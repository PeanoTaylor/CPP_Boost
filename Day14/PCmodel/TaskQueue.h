/**
 * Project 66th
 */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
using std::condition_variable;
using std::cout;
using std::endl;
using std::mutex;
using std::deque;
using std::unique_lock;
using std::lock_guard;
extern mutex coutMtx;
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
void push(const int & value);
    
int pop();
    
bool empty();
    
bool full();

private: 
    size_t m_capacity;
    mutex m_mutex;
    deque<int> m_queue;
    condition_variable m_notFull;
    condition_variable m_notEmpty;
};

#endif //_TASKQUEUE_H