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

    list<char *> list = {"hello","world","!"};

    vector<string> vec;

    for(char *s : list){
        vec.emplace_back(s);// 容器尾部构造对象
    }

    display(vec);

    return 0;
}

