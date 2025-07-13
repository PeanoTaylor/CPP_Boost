#include <iostream>
#include <map>
using namespace std;

class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    // operator<（运算符重载）
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
int main()
{

    map<Point, string> mp = {
        {Point{1, 2}, "HELLO"},
        {Point{3, 4}, "WORLD"},
        {Point{5, 6}, "TEST"}};

    for (const auto &p : mp)
    {
        cout << "{(" << p.first.getX() << "," << p.first.getY() << ")," << p.second << "}" << endl;
    }

    return 0;
};
