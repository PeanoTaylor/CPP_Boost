#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>  // For std::mem_fn
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::mem_fn;

class Point
{
public:
    Point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    void print()
    {
        cout << "(" << m_x << "," << m_y << ")" << endl;
    }

private:
    int m_x;
    int m_y;
};

int main(int argc, char *argv[])
{
    
    vector<Point> points = {
        Point(1, 2),
        Point(3, 4),
        Point(5, 6)
    };

    for_each(points.begin(),points.end(),mem_fn(&Point::print));
    return 0;
}
