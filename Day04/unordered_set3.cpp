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

// 模板特化 + operator()==
class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}

    bool operator==(const Point &rhs) const
    {
        cout << "operator== 调用" << endl;
        return m_x == rhs.m_x && m_y == rhs.m_y;
    }
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

int main()
{
    unordered_set<Point, std::hash<Point>> nums = {{1, 2},
                                                   {3, 4},
                                                   {-1, 2},
                                                   {4, 3},
                                                   {3, 4},
                                                   {1, 2}};
    display(nums);
    return 0;
}
