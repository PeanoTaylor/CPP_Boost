/**
 * Project 66th
 */


#include "TaskQueue.h"

/**
 * TaskQueue implementation
 */


/**
 * @param capa
 */
TaskQueue::TaskQueue(size_t capa)
    :m_capacity(capa)
    ,m_mutex()
    ,m_queue()
    ,m_notFull()
    ,m_notEmpty(){}

TaskQueue::~TaskQueue() {}

/**
 * @param value
 * @return void
 */
void TaskQueue::push(const int & value) {
    // 1.对任务队列上锁避免产生竞争
    unique_lock<mutex> ul(m_mutex);
    // 2.判断队列是否已满
    while(full()){// 可能被虚假唤醒,所以用while
        // 队列已满，则通知生产者线程等待
        m_notFull.wait(ul);//用于阻塞当前线程并自动释放互斥锁,直到其他线程调用notify_one()或notify_all()唤醒它
    }
    m_queue.push(value);
    m_notEmpty.notify_one();//通知消费者队列非空
}

/**
 * @return int
 */
int TaskQueue::pop() {
    unique_lock<mutex> ul(m_mutex);
    while(empty()){
        m_notEmpty.wait(ul);//队列为空，消费者进入等待队列，释放互斥锁，直到有新元素被生产者加入
    }
    int temp = m_queue.front();
    m_queue.pop();
    m_notFull.notify_one();
    return temp;
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
