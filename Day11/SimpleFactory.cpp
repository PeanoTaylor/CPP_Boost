#include <iostream>
#include <memory>
using namespace std;

class Figure{
public:
    virtual string getName()=0;
    virtual double getArea()=0;
    virtual ~Figure(){};
};

// 具体产品：矩形
class Rectangle : public Figure {
public:
    Rectangle(int x, int y) : m_x(x), m_y(y) {}
    string getName() override { return "矩形"; }
    double getArea() override { return m_x * m_y; }
private:
    int m_x, m_y;
};

// 具体产品：圆形
class Circle : public Figure {
public:
    Circle(int r) : m_r(r) {}
    string getName() override { return "圆"; }
    double getArea() override { return 3.14 * m_r * m_r; }
private:
    int m_r;
};

class SimpleFactory{
public:
    static Figure *create(const string &name){
        if(name == "rectangle"){
            return new Rectangle(3,20);
        }
        else if(name == "circle"){
            return new Circle(5);
        }
        else{
            return nullptr;
        }
    }
};

void display(Figure * fig) {
    cout << fig->getName() 
        << "的面积是:" 
        << fig->getArea() << endl ;
}

int main()
{
    unique_ptr<Figure> prec(SimpleFactory::create("rectangle"));
    unique_ptr<Figure> crec(SimpleFactory::create("circle"));

    display(prec.get());
    display(crec.get());
    return 0;
}

