#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

void print(vector<int> &vec)
{
    for (auto &e : vec)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> vec = {10, 20, 30};
    print(vec);
    vec.insert(vec.begin() + 1, 15);// 指定位置插入元素
    print(vec);
    vec.push_back(40);// 末尾插入元素
    print(vec);
    vec.pop_back();// 删除末尾元素
    print(vec);
    vec.erase(vec.begin() + 1);// 删除指定位置元素
    print(vec);
    vec.push_back(20);
    print(vec);
    vec.erase(remove(vec.begin(), vec.end(), 20), vec.end());
    print(vec);
    return 0;
}
