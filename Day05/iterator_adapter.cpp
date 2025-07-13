#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <list>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::set;
using std::list;
using std::front_insert_iterator;
using std::back_insert_iterator;
using std::inserter;

template<typename Container>
void display(const Container &container){
    for(auto &e : container){
        cout << e << " ";
    }
    cout << endl;
}

void list_deque(){
    list<int> list = {1,2,3};
    deque<int> deq = {4,5,6,7,8,9};
    copy(list.rbegin(), list.rend(),front_insert_iterator<deque<int>>(deq));
    display(deq);
}

void deque_vector(){
    vector<int> vec = {1,2,3};
    deque<int> deq = {4,5,6,7,8,9};
    copy(deq.begin(), deq.end(),back_insert_iterator<vector<int>>(vec));
    display(vec);
}

//set是一个有序关联容器，它没有push_back成员函数。
void vector_set(){
    vector<int> vec = {1,2,3};
    set<int> s = {4,5,6,7,8,9};
    copy(vec.begin(), vec.end(),inserter(s,s.begin()));
    display(s);
}
int main()
{
    list_deque();
    deque_vector();
    vector_set();
    return 0;
}

