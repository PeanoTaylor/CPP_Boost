/**
 * Project 66th
 */


#include "Consumer.h"

/**
 * Consumer implementation
 */


/**
 * @param taskQue
 * @return void
 */
mutex coutMtx;
void Consumer::consume(TaskQueue & taskQue) {
    int cnt = 20;
    while(cnt--)
    {
        int num = taskQue.pop();
        {
            lock_guard<mutex> lg(coutMtx);
            cout << "consume number = "
            << num << endl;
        }
    }

}