#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

// 抽象组件
class HotPot
{
public:
    virtual void Operation() = 0;
    ~HotPot() {}
};

class RedOil : public HotPot
{
public:
    void Operation() override
    {
        cout << "红汤锅" << endl;
    }
};

class Soup : public HotPot
{
public:
    void Operation() override
    {
        cout << "清汤锅" << endl;
    }
};

// 装饰器基类
class Decorator : public HotPot
{
public:
    Decorator(HotPot *hotpot) : m_hotpot(hotpot) {}
    void Operation() override
    {
        if (m_hotpot)
        {
            m_hotpot->Operation();
        }
    }

protected:
    HotPot *m_hotpot;
};

// 具体装饰器
class BeefDecorator : public Decorator
{
public:
    BeefDecorator(HotPot *hotpot) : Decorator(hotpot) {}

    void Operation() override
    {
        Decorator::Operation();   // 先调用原有功能
        cout << "加牛肉" << endl; // 添加新功能
    }
};

class CucumberDecorator : public Decorator
{
public:
    CucumberDecorator(HotPot *hotpot) : Decorator(hotpot) {}

    void Operation() override
    {
        Decorator::Operation();   
        cout << "加黄瓜" << endl; 
    }
};

int main()
{

    // 创建红汤锅
    shared_ptr<HotPot> redoil(new RedOil());
    cout << "锅底:" << endl;
    redoil->Operation();

    // 用装饰器给红汤锅加牛肉
    shared_ptr<HotPot> beefHotpot(new BeefDecorator(redoil.get()));
    cout << "\n加了牛肉的火锅:" << endl;
    beefHotpot->Operation();
    
    // 再给加了牛肉的火锅加黄瓜
    shared_ptr<HotPot> cucumberBeefHotpot(new CucumberDecorator(beefHotpot.get()));
    cout << "\n加了牛肉和黄瓜的火锅:" << endl;
    cucumberBeefHotpot->Operation();
    return 0;
}
