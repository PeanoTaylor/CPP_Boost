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
extern mutex coutMtx;
void Producer::produce(TaskQueue & taskQue) {
    srand(clock());
    int cnt = 20;
    while(cnt--){
        int num = rand() % 100;
        taskQue.push(num);
        {
            unique_lock<mutex> ul(coutMtx);
            cout << "produceNum = " << num << endl;
        }
    }
}
