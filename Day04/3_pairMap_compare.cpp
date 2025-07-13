#include <iostream>
#include <map>
using namespace std;

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}

    bool operator<(const Point &rhs) const
    {
        if (this != &rhs)
        {
            return m_x < rhs.m_x;
        }
        return m_y < rhs.m_y;
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }

private:
    int m_x;
    int m_y;
};

// 自定义比较器(函数对象)
struct Compare
{
    bool operator()(const Point &lhs, const Point &rhs) const
    {
        if (lhs.getX() != rhs.getX())
        {
            return lhs.getX() < rhs.getX();
        }
        return lhs.getY() < rhs.getY();
    }
};

int main()
{

    map<Point, string, Compare> mp;
    mp[Point(1, 2)] = "Hello";
    mp[Point(3, 4)] = "World";
    mp[Point(5, 6)] = "NiHao";

    for (const auto &p : mp)
    {
        cout << "{(" << p.first.getX() << "," << p.first.getY() << ")," << p.second << "}" << endl;
    }

    return 0;
};
