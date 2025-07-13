#include <iostream>
#include <map>
#include <string>
using namespace std;

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

namespace std
{
    template <>
    struct less<Point>
    {
        bool operator()(const Point &lhs, const Point &rhs) const
        {
            if (lhs.getX() != rhs.getX())
                return lhs.getX() < rhs.getX();
            else
                return lhs.getY() < rhs.getY();
        }
    };
}

int main()
{
    map<Point, string> mp;
    mp[Point(1, 2)] = "Hello";
    mp[Point(3, 4)] = "World";
    mp[Point(5, 6)] = "NiHao";
    mp[Point(1, 5)] = "Test";

    for (const auto &p : mp)
    {
        cout << "{(" << p.first.getX() << "," << p.first.getY() << "),"
             << p.second << "}" << endl;
    }
    return 0;
}
