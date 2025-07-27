/**
 * Project 66th
 * TaskQueue实现
 */
#include "TaskQueue.h"

// 构造函数，初始化容量和同步变量
TaskQueue::TaskQueue(size_t capa)
    :m_capacity(capa), m_mutex(), m_queue(), m_notFull(), m_notEmpty(), m_flag(true) {}

TaskQueue::~TaskQueue() {}

/**
 * 生产者调用push将任务放入队列
 * 若队列已满，阻塞等待，直到有空位
 */
void TaskQueue::push(ElemType value) {
    // 1.对任务队列上锁避免竞争
    unique_lock<mutex> ul(m_mutex);
    // 2.判断队列是否已满，满则等待notFull条件
    while(full()){
        m_notFull.wait(ul);
    }
    // 3.队列未满，将任务入队
    m_queue.push(value);
    // 4.通知等待中的消费者队列非空
    m_notEmpty.notify_one();
}

/**
 * 消费者/线程池线程调用pop获取任务
 * 若队列为空且未关闭，阻塞等待，直到有新任务或收到关闭信号
 */
ElemType TaskQueue::pop() {
    unique_lock<mutex> ul(m_mutex);
    // 当队列为空且线程池还未关闭时，等待notEmpty条件
    while(empty() && m_flag){
        m_notEmpty.wait(ul);
    }
    // m_flag控制线程池是否退出
    if(m_flag && !empty()){
        ElemType temp = m_queue.front();
        m_queue.pop();
        // 通知等待中的生产者队列有空位
        m_notFull.notify_one();
        return temp;
    }else{
        // 若线程池准备关闭，返回nullptr
        return nullptr;
    }
}

bool TaskQueue::empty() {
    return m_queue.size() == 0;
}

bool TaskQueue::full() {
    return m_queue.size() == m_capacity;
}

/**
 * 唤醒所有等待中的消费者线程，让其能够及时退出
 * 线程池关闭时调用
 */
void TaskQueue::wakeup(){
    m_flag = false;
    m_notEmpty.notify_all(); // 唤醒所有等待notEmpty的线程
}
