/**
 * Project 66th
 * 任务基类，所有任务需继承并实现process接口
 */
#ifndef _TASK_H
#define _TASK_H

class Task {
public:
    // 纯虚函数，任务处理入口，由子类实现
    virtual void process() = 0;

    // 虚析构，确保子类析构函数能被正确调用
    virtual ~Task(){}
};

#endif //_TASK_H
