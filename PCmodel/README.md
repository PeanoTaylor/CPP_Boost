# C++生产者-消费者模型完整工程代码（带详细注释）

---

## TaskQueue.h

```cpp
/**
 * Project 66th
 * 线程安全的任务队列（带容量限制）
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
using std::queue;
using std::unique_lock;
using std::lock_guard;

// 声明全局互斥锁，防止多线程 cout 输出乱序
extern mutex coutMtx;

class TaskQueue {
public:
    // 构造函数，指定容量
    TaskQueue(size_t capa);

    // 析构函数
    ~TaskQueue();

    // 入队，队满则阻塞等待
    void push(const int & value);

    // 出队，队空则阻塞等待
    int pop();

    // 判断队列是否为空
    bool empty();

    // 判断队列是否已满
    bool full();

private:
    size_t m_capacity;              // 队列容量上限
    mutex m_mutex;                  // 互斥锁
    queue<int> m_queue;             // 缓冲区
    condition_variable m_notFull;   // 队列未满条件变量
    condition_variable m_notEmpty;  // 队列非空条件变量
};

#endif //_TASKQUEUE_H
```

---

## TaskQueue.cpp

```cpp
/**
 * Project 66th
 * TaskQueue 线程安全队列实现
 */
#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t capa)
    : m_capacity(capa),
      m_mutex(),
      m_queue(),
      m_notFull(),
      m_notEmpty() {}

TaskQueue::~TaskQueue() {}

// 入队操作，若队列已满则阻塞
void TaskQueue::push(const int & value) {
    unique_lock<mutex> ul(m_mutex);
    while (full()) {
        m_notFull.wait(ul); // 等待队列有空位
    }
    m_queue.push(value);
    m_notEmpty.notify_one(); // 通知等待中的消费者
}

// 出队操作，若队列为空则阻塞
int TaskQueue::pop() {
    unique_lock<mutex> ul(m_mutex);
    while (empty()) {
        m_notEmpty.wait(ul); // 等待队列有元素
    }
    int temp = m_queue.front();
    m_queue.pop();
    m_notFull.notify_one(); // 通知等待中的生产者
    return temp;
}

bool TaskQueue::empty() {
    return m_queue.size() == 0;
}

bool TaskQueue::full() {
    return m_queue.size() == m_capacity;
}
```

---

## Producer.h

```cpp
/**
 * Project 66th
 * 生产者类声明
 */

#ifndef _PRODUCER_H
#define _PRODUCER_H

#include "TaskQueue.h"

class Producer {
public:
    // 生产指定数量任务
    void produce(TaskQueue & taskQue);
};

#endif //_PRODUCER_H
```

---

## Producer.cpp

```cpp
/**
 * Project 66th
 * 生产者类实现
 */
#include "Producer.h"
#include <cstdlib>
#include <ctime>

extern mutex coutMtx; // 全局输出锁

void Producer::produce(TaskQueue & taskQue) {
    srand(static_cast<unsigned int>(time(nullptr))); // 初始化随机数种子
    int cnt = 20; // 生产 20 个任务
    while (cnt--) {
        int num = rand() % 100;
        taskQue.push(num);
        {
            unique_lock<mutex> ul(coutMtx);
            cout << "produceNum = " << num << endl;
        }
    }
}
```

---

## Consumer.h

```cpp
/**
 * Project 66th
 * 消费者类声明
 */

#ifndef _CONSUMER_H
#define _CONSUMER_H

#include "TaskQueue.h"

class Consumer {
public:
    // 消费指定数量任务
    void consume(TaskQueue & taskQue);
};

#endif //_CONSUMER_H
```

---

## Consumer.cpp

```cpp
/**
 * Project 66th
 * 消费者类实现
 */
#include "Consumer.h"
#include <cstdlib>
#include <ctime>

extern mutex coutMtx; // 全局输出锁

void Consumer::consume(TaskQueue & taskQue) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int cnt = 20; // 消费 20 个任务
    while (cnt--) {
        int num = taskQue.pop();
        {
            unique_lock<mutex> ul(coutMtx);
            cout << "consumeNum = " << num << endl;
        }
    }
}
```

---

## Test.cpp

```cpp
/**
 * Project 66th
 * 主程序，测试生产者-消费者模型
 */

#include "Producer.h"
#include "Consumer.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

// 定义全局输出锁
mutex coutMtx;

int main() {
    TaskQueue taskQue(10); // 容量为10的队列

    Producer producer;
    Consumer consumer;

    // 启动生产者和消费者线程
    thread pro(&Producer::produce, &producer, std::ref(taskQue));
    thread con(&Consumer::consume, &consumer, std::ref(taskQue));

    pro.join();
    con.join();

    return 0;
}
```

---

## 编译&运行

```sh
g++ Test.cpp Producer.cpp Consumer.cpp TaskQueue.cpp -o prod_consume -std=c++11 -pthread
./prod_consume
```



