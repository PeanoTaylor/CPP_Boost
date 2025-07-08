#include <iostream>
using namespace std;

class Data
{
public:
    Data(int data) : m_data(data)
    {
        cout << "Data()" << endl;
    }
    ~Data()
    {
        cout << "~Data()" << endl;
    }
    int getData() const
    {
        return m_data;
    }

private:
    int m_data;
};

class MiddleLayer
{
public:
    MiddleLayer(Data *pdata) : m_pdata(pdata)
    {
        cout << "MiddleLayer()" << endl;
    }
    ~MiddleLayer()
    {
        delete m_pdata;
        m_pdata = nullptr;
        cout << "~MiddleLayer()" << endl;
    }
    Data *operator->()
    {
        return m_pdata;
    }

private:
    Data *m_pdata;
};

class ThirdLayer
{
public:
    ThirdLayer(MiddleLayer *pdata) : t_pdata(pdata)
    {
        cout << "ThirdLayer()" << endl;
    }
    ~ThirdLayer()
    {
        delete t_pdata;
        t_pdata = nullptr;
        cout << "~ThirdLayer()" << endl;
    }
    Data *operator->()
    {
        return t_pdata->operator->();
    }

private:
    MiddleLayer *t_pdata;
};
int main()
{
    ThirdLayer *p = new ThirdLayer(new MiddleLayer(new Data(100)));
    cout << p->operator->()->getData() << endl;
    delete p;
    return 0;
}
