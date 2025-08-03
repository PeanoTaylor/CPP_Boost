/**
 * Project 66th
 */

#ifndef _TASK_H
#define _TASK_H

class Task
{
public:
    virtual void process() = 0;
    virtual ~Task() {}
};

#endif //_TASK_H