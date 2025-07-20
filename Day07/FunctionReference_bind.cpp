#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using std::bind;
using std::bind1st;
using std::bind2nd;
using std::cout;
using std::endl;
using std::for_each;
using std::remove_if;
using std::vector;

// 普通函数指针 + bind
int add(int x, int y)
{
    return x + y;
}

int main()
{
    int (&ref)(int, int) = add;
    using namespace std::placeholders;

    auto f = bind(ref, 100, _1);
    cout << f(23) << endl;
    return 0;
}
