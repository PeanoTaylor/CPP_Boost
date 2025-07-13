#include <math.h>
#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

template <class Container>
void display(const Container &con)
{
    for (auto &ele : con)
    {
        cout << ele << " ";
    }
    cout << endl;
}

// 模板特化 + 自定义比较器(函数对象)
class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    int getX() const { return m_x; }
    int getY() const { return m_y; }

private:
    int m_x;
    int m_y;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs.getX() << "," << rhs.getY() << ")";
    return os;
}

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point &rhs) const
        {
            cout << "hash特化" << endl;
            return (rhs.getX() << 1) ^ (rhs.getY() << 2);
        }
    };
}

struct Compare
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        cout << "自定义比较器(函数对象)" << endl;
        return (lhs.getX() == rhs.getX()) &&
               (lhs.getY() == rhs.getY());
    }
};

int main()
{
    unordered_set<Point, std::hash<Point>, Compare> nums = {{1, 2},
                                                            {3, 4},
                                                            {-1, 2},
                                                            {4, 3},
                                                            {3, 4},
                                                            {1, 2}};
    display(nums);
    return 0;
}
