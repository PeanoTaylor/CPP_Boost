#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 抽象观察者
class Observer{
public:
    virtual void update(int value)=0;
    virtual ~Observer(){}
};

// 抽象被观察者
class Subject{
public:
    void attach(Observer *obs){
        observers.push_back(obs);
    }
    void detach(Observer *obs){
        observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());

    }
    // 通知所有观察者
    void notify(int value){
        for(size_t i = 0; i < observers.size(); ++i){
            observers[i]->update(value);
        }
    }
protected:
    vector<Observer*> observers; // 保存原始指针
};

class ConcreteSubject:public Subject{
public:
    void setValue(int v){
        value = v;
        notify(value);
    }
private:
    int value = 0;
};

class ObserverA:public Observer{
public:
    void update(int value) override{
        cout << "ObserverA 收到新值: " << value << endl;
    }
};

class ObserverB:public Observer{
public:
    void update(int value) override{
        cout << "ObserverB 收到新值: " << value << endl;
    }
};
int main()
{
    // 手动管理内存，创建对象
    ConcreteSubject* subject = new ConcreteSubject;
    Observer* obsA = new ObserverA;
    Observer* obsB = new ObserverB;

    subject->attach(obsA);
    subject->attach(obsB);

    subject->setValue(10); // 通知两个观察者
    subject->setValue(20); // 再次通知

    subject->detach(obsA); // 可以动态移除
    subject->setValue(30);

    // 释放内存，防止泄漏
    delete obsA;
    delete obsB;
    delete subject;
    return 0;
}

