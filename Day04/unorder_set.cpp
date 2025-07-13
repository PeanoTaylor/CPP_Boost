#include <iostream>
#include <cmath>
#include <unordered_set>
using namespace std;

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}

    float getDistance() const
    {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    bool operator==(const Point &other) const
    {
        return m_x == other.m_x && m_y == other.m_y;
    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }

private:
    int m_x;
    int m_y;
};

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point &rhs) const
        {
            cout << "hash 特化" << endl;
            return ((rhs.getX()) ^ (rhs.getY()) << 1);
        }
    };

    template <>
    struct hash<pair<int, int>>
    {
        size_t operator()(const pair<int, int> &p) const
        {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
    template <>
    struct equal_to<Point>
    {
        bool operator()(const Point &lhs, const Point &rhs) const
        {
            cout << "equal特化" << endl;
            return (lhs.getX() == rhs.getX()) &&
                   (lhs.getY() == rhs.getY());
        }
    };
}

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs.getX() << "," << rhs.getY() << ")";
    return os;
}

void method1()
{
    unordered_set<Point> s = {{1, 2}, {1, 2}, {3, 4}};
    cout << "方式1：std::hash<Point> 特化" << endl;
    for (const auto &p : s)
        cout << p << " ";
    cout << "\n\n";
}

void method2()
{
    unordered_set<Point, std::hash<Point>, std::equal_to<Point>> s = {{2, 3}, {2, 3}, {5, 5}};
    cout << "方式2：自定义 Hash + Equal 类" << endl;
    for (const auto &p : s)
        cout << p << " ";
    cout << "\n\n";
}

void method3()
{
    unordered_set<pair<int, int>> s = {{1, 1}, {1, 1}, {2, 2}};
    cout << "方式3：pair<int,int> 替代 Point" << endl;
    for (const auto &p : s)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n\n";
}

int main()
{
    method1();
    method2();
    method3();
    return 0;
}
