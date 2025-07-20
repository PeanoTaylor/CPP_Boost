#include <iostream>
#include <string>
#include <functional>  // 用于std::function和std::bind
using std::cout;
using std::endl;
using std::string;
using std::bind;

class Figure
{
public:
    // 定义两个回调函数类型：一个用于获取图形名称，另一个用于计算图形面积
    using DisplayCallback = std::function<string()>;
    using AreaCallback = std::function<double()>;

    // 设置显示回调函数
    void setDisplayCallback(DisplayCallback &&dcb)
    {
        m_displayCallback = std::move(dcb);  // 将回调函数传递给成员变量
    }

    // 设置面积回调函数
    void setAreaCallback(AreaCallback &&acb)
    {
        m_areaCallback = std::move(acb);  // 将回调函数传递给成员变量
    }

    // 执行显示回调函数
    string handleDisplayCallback()
    {
        if (m_displayCallback)  // 如果回调函数存在，执行它
        {
            return m_displayCallback();
        }
        return string();  // 如果没有设置回调函数，返回空字符串
    }

    // 执行面积回调函数
    double handleAreaCallback()
    {
        if (m_areaCallback)  // 如果回调函数存在，执行它
        {
            return m_areaCallback();
        }
        return 0;  // 如果没有设置回调函数，返回0
    }

private:
    // 存储回调函数的成员变量
    DisplayCallback m_displayCallback;
    AreaCallback m_areaCallback;
};


class Rectangle
{
public:

    Rectangle(double len, double wid)
        : _length(len), _width(wid)
    {}

    string getRecName() const 
    {
        return "矩形";
    }


    double getRecArea() const 
    {
        return _length * _width; 
    }

private:
    double _length;  
    double _width;   
};


void display(Figure &fi)
{

    cout << fi.handleDisplayCallback() 
         << "的面积为 " 
         << fi.handleAreaCallback() << endl;
}


int main(void)
{

    Rectangle rec(10, 20);

    Figure fig;

    // 使用std::bind绑定Rectangle的成员函数到Figure对象
    // 将矩形的名称获取函数绑定到displayCallback
    fig.setDisplayCallback(bind(&Rectangle::getRecName, rec));

    // 将矩形的面积计算函数绑定到areaCallback
    fig.setAreaCallback(bind(&Rectangle::getRecArea, rec));


    display(fig);

    return 0;
}
