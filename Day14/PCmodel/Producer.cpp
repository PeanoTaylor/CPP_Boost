/**
 * Project 66th
 */


#include "Producer.h"

/**
 * Producer implementation
 */


/**
 * @param taskQue
 * @return void
 */
mutex coutMtx;
void Producer::produce(TaskQueue & taskQue) {
    srand(clock());
    int cnt = 20;
    while(cnt--)
    {
        int num = rand() % 100;
        taskQue.push(num);
        {
            lock_guard<mutex> lg(coutMtx);
            cout << "produce number = " 
                << num << endl;
        }
    }
}