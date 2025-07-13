#include <iostream>
#include <vector>
#include <queue>
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

class Point
{
public:
    Point(int x, int y)
        : m_x(x), m_y(y) {}

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

    friend std::ostream &operator<<(std::ostream &os, const Point &pt);

private:
    int m_x;
    int m_y;
};

std::ostream &operator<<(std::ostream &os, const Point &pt)
{
    os << "(" << pt.m_x << "," << pt.m_y << ")";
    return os;
}

int main()
{
    vector<Point> vec = {Point(1, 2), Point(3, 4), Point(1, 2), Point(5, 6)};
    priority_queue pq(vec.begin(), vec.end());
    while (!pq.empty())
    {
        cout << pq.top() << " " << endl;
        pq.pop();
    }
    return 0;
}
