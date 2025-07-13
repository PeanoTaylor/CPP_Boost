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

// my_hash + operator()==
class Point
{
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    bool operator==(const Point &rhs) const
    {
        cout << "operator== 调用" << endl;
        return m_x == rhs.m_x && m_y == rhs.m_y;
    }

private:
    int m_x;
    int m_y;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs.getX() << "," << rhs.getY() << ")";
    return os;
}

struct my_hash
{
    size_t operator()(const Point &rhs) const
    {
        cout << "my_hash" << endl;
        return (rhs.getX() << 1) ^ (rhs.getY() << 2);
    }
};

int main()
{
    unordered_set<Point, my_hash> nums = {{1, 2},
                                          {3, 4},
                                          {-1, 2},
                                          {4, 3},
                                          {0, 5},
                                          {1, 2}};
    display(nums);
    return 0;
}
