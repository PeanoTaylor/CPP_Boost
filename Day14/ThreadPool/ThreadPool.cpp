/**
 * Project 66th
 */

#include "ThreadPool.h"

/**
 * ThreadPool implementation
 */

/**
 * @param threadNum
 * @param queSize
 */
ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : m_threadsNum(threadNum), m_queSize(queSize), m_threads(), m_taskQue(m_queSize), m_isExit(false)
{
}

ThreadPool::~ThreadPool() {}

/**
 * @return void
 */
// 线程池启动
void ThreadPool::start()
{
    for (int idx = 0; idx < m_threadsNum; ++idx)
    {
        // 往vector中进行push_back时不能传左值thread
        // 因为这样会触发thread的拷贝构造，
        // 而thread拷贝构造被删除
        m_threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

/**
 * @return void
 */
void ThreadPool::stop()
{
    // 修改标志位，表示线程池要退出
    m_isExit = true;

    m_taskQue.wakeup();
    // 主线程等待子线程退出
    for (auto &th : m_threads)
    {
        th.join();
    }
    return;
}

/**
 * @param ptask
 * @return void
 */
void ThreadPool::addTask(ElemType ptask)
{
    // 空指针调用虚函数会出现段错误，检查
    if (ptask)
    {
        // 生产者将任务加到TaskQueue
        // 加锁
        // 判满
        // 满则阻塞
        // 不满则push，且唤醒等待的消费者线程
        m_taskQue.push(ptask);
    }
    return;
}

/**
 * @return Task *
 */
ElemType ThreadPool::getTask()
{
    return m_taskQue.pop();
}

/**
 * @return void
 */
void ThreadPool::doTask()
{
    // 不退出，则一直执行任务
    while (!m_isExit)
    {
        // 任务队列为空，阻塞线程（消费者）
        ElemType ptask = getTask();
        if (ptask)
        {
            ptask->process();
        }
        else
        {
            cout << "ptask == nullptr" << endl;
        }
    }
}


