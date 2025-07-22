#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

// 抽象观察者
class Observer{
public:
    virtual void update(int status)=0;
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
    void notify(int status){
        for(int i = 0; i<observers.size();++i){
            observers[i]->update(status);
        }
    }

private:
    vector<Observer*> observers;
};

class ConcreteSubject:public Subject{
public:
    void setStatus(int s){
        m_status = s;
        notify(m_status);
    }

private:
    int m_status = 0;
};

class ObserverA:public Observer{
public:
    void update(int status) override{
        cout << "update A status:" << status << endl;
    }
};

class ObserverB:public Observer{
public:
    void update(int status) override{
        cout << "update B status:" << status << endl;
    }
};

int main()
{
    shared_ptr<ConcreteSubject> sub (new ConcreteSubject);
    ObserverA Oba;
    ObserverB Obb;

    sub->attach(&Oba);
    sub->attach(&Obb);

    sub->setStatus(10);

    sub->detach(&Oba);

    sub->setStatus(20);

    sub->detach(&Obb);

    return 0;
}

