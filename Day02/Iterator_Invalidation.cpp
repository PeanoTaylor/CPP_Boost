#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};
    auto it = v.begin();  // it 指向第一个元素

    v.push_back(4);       // 可能触发扩容，导致迭代器失效

    cout << *it << endl;  //  迭代器 it 可能已失效，使用它是未定义行为
    return 0;
}
