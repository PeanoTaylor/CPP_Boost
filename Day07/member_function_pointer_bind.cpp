#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using std::bind;

using std::cout;
using std::endl;
using std::for_each;
using std::remove_if;


// 成员函数指针 + bind
struct Add
{
    int multi(int x, int y, int z)
    {
        return x * y * z;
    }
};

int main()
{
    Add add;
    using namespace std::placeholders;

    auto f = bind(&Add::multi, &add, 2, _1, _2);
    cout << f(3,4) << endl;
    return 0;
}
