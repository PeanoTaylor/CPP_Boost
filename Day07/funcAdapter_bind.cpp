#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;
using std::bind1st;
using std::bind2nd;

void bind_1st(){
    vector<int> vec = {9,4,5,3,1,6,2,8,7};
    for_each(vec.begin(),vec.end(),[](int &value){
        cout << value << " ";
    });
    cout << endl;
    //remove_if不会删除元素
    vec.erase(remove_if(vec.begin(),vec.end(),bind1st(std::less<int>(),5)),vec.end());// std::less代表"<"

    for_each(vec.begin(),vec.end(),[](int &value){
        cout << value << " ";
    });
    cout << endl;
}

void bind_2nd(){
    vector<int> vec = {9,4,5,3,1,6,2,8,7};
    for_each(vec.begin(),vec.end(),[](int &value){
        cout << value << " ";
    });
    cout << endl;

    vec.erase(remove_if(vec.begin(),vec.end(),bind2nd(std::less<int>(),5)),vec.end());

    for_each(vec.begin(),vec.end(),[](int &value){
        cout << value << " ";
    });
    cout << endl;
}
int main()
{
    bind_2nd();
    return 0;
}

