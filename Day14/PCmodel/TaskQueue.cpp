/**
 * Project 66th
 */


#include "TaskQueue.h"
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

/**
 * TaskQueue implementation
 */


/**
 * @param capa
 */
TaskQueue::TaskQueue(size_t capa) 
        : m_capacity(capa)
        , m_mutex()
        , m_queue()
        , m_notEmpty()
        , m_notFull() {}


TaskQueue::~TaskQueue(){}        
/**
 * @param value
 * @return void
 */
void TaskQueue::push(const int & value) {
     // 1.上锁避免产生竞争
    unique_lock<mutex> ul_mtx(m_mutex);
    // 2.判断队列是否已满

    // if(full()) 虚假唤醒
    while(full()){
        // 如果队列满，生产者线程
        m_notFull.wait(ul_mtx);//阻塞当前线程，直到不满的条件变量被唤醒
    }
    m_queue.push_back(value);
    m_notEmpty.notify_one();//唤醒等待的消费者线程
}

/**
 * @return int
 */
int TaskQueue::pop(){
    // 1.上锁避免产生竞争
    unique_lock<mutex> ul_mtx(m_mutex);
    while(empty()){
        // 如果队列空，消费者线程等待
        m_notEmpty.wait(ul_mtx);
    }
    int tmp = m_queue.front();
    m_queue.pop_front();
    m_notFull.notify_one();// 唤醒等待的生产者线程
    return tmp;
}

/**
 * @return bool
 */
bool TaskQueue::empty() {
    return m_queue.size() == 0;
}

/**
 * @return bool
 */
bool TaskQueue::full() {
    return m_queue.size() == m_capacity;
}

