#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using std::bind;
using std::cout;
using std::endl;
using std::for_each;
using std::remove_if;
using std::vector;

// 函数对象 + bind
struct Add
{
    int operator()(int x, int y) const
    {
        return x + y;
    }
};

int main()
{
    using namespace std::placeholders;

    auto f = bind(Add(), 100, _1);
    cout << f(23) << endl;
    return 0;
}
