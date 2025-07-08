#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

// 通用打印模板
template<typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << " ";
    cout << endl;
}

int main()
{
    list<int> list = {1, 2, 3, 4, 5};
    display(list);
    auto it = list.begin();
    ++it;
    ++it;
    list.insert(it,80);
    display(list);
    cout << *it << endl;

    list.insert(it,3,100);
    display(list);
    cout << *it << endl;

    int arr[5] = {11,12,13,14,15};
    list.insert(it,arr,arr+5);
    display(list);
    cout << *it << endl;

    list.insert(it,{200,200,200});
    display(list);

    vector<string> vec = {"hello","world"};
    display(vec);
    return 0;
}
