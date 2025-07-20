#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using std::bind;

using std::cout;
using std::endl;
using std::for_each;
using std::remove_if;

struct Point {
    int x, y;
};

int main() {
    using namespace std::placeholders;
    Point pt{10, 20};

    // 获取 Point::x
    auto get_x = std::bind(&Point::x, _1); // _1 是 Point 对象
    cout << get_x(pt) << endl; // 输出10

    // 绑定对象，生成零参数对象
    auto get_y = std::bind(&Point::y, pt);
    cout << get_y() << endl; // 输出20
}
