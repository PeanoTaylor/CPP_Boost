#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::for_each;
using std::ostream_iterator;
using std::vector;

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5};

    //  for循环 + 下标访问
    for (size_t i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";
    cout << endl;

    // 增强for循环
    for (const auto &e : vec)
        cout << e << " ";
    cout << endl;

    // const_iterator 遍历（只读访问）
    for (auto it = vec.cbegin(); it != vec.cend(); ++it)
        cout << *it << " ";
    cout << endl;

    // std::for_each + lambda 表达式
    for_each(vec.begin(), vec.end(), [](int x)
             { cout << x << " "; });
    cout << endl;

    // std::copy + ostream_iterator 输出所有元素
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
