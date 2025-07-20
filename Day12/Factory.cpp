#include <iostream>
#include <memory>
using namespace std;

class Figure
{
public:
    virtual string getName() = 0;
    virtual double getArea() = 0;
    ~Figure() {};
};

class Rectangle : public Figure
{
public:
    Rectangle(int x, int y) : m_x(x), m_y(y) {}
    string getName() override { return "矩形"; }
    double getArea() override { return m_x * m_y; }

private:
    int m_x;
    int m_y;
};

class Circle : public Figure
{
public:
    Circle(int r) : m_r(r) {}
    string getName() override { return "圆"; }
    double getArea() override { return 3.14 * m_r * m_r; }

private:
    int m_r;
};

class Factory
{
public:
    virtual Figure *create() = 0;
    virtual ~Factory() {}
};

class RectangleFactory : public Factory
{
public:
    Figure *create() override
    {
        return new Rectangle(2, 30);
    }
};

class CircleFactory : public Factory
{
public:
    Figure *create() override
    {
        return new Circle(5);
    }
};

void display(Figure *fig)
{
    cout << fig->getName() << "的面积为" << fig->getArea() << endl;
}
int main()
{
    unique_ptr<Factory> rec(new RectangleFactory());
    unique_ptr<Figure> prec(rec->create());
    display(prec.get());

    unique_ptr<Factory> cir(new CircleFactory());
    unique_ptr<Figure> pcir(cir->create());
    display(pcir.get());
    return 0;
}
