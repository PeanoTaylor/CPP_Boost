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
extern mutex coutMtx;
void Consumer::consume(TaskQueue & taskQue) {
    srand(clock());
    int cnt = 20;
    while(cnt--){
        int num = taskQue.pop();
        {
            unique_lock<mutex> ul(coutMtx);
            cout << "consumeNum = " << num << endl; 
        }
    }
}
