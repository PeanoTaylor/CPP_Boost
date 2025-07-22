#include <iostream>
#include <vector>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;

class Handle
{
public:
    virtual void handleRequest(int res) = 0;
    void setNextHandle(const shared_ptr<Handle> &ph)//智能指针，指向下一个处理者对象,实现责任链的“链式”连接，每个节点都能转发请求到下一个
    {
        m_pNextHandle = ph;
    }
    ~Handle() {}

protected:
    shared_ptr<Handle> m_pNextHandle;
};

class CHandle1 : public Handle
{
public:
    CHandle1() {}//默认构造
    CHandle1(const shared_ptr<Handle> &ph)//指定下一个处理者，链式创建
    {
        m_pNextHandle = ph;
    }
    void handleRequest(int req) override
    {
        if (req > 0 && req < 10)
        {
            cout << "节点1处理请求" << req << endl;
        }
        else if (m_pNextHandle)
        {
            cout << "节点1无法处理该请求" << endl;
            m_pNextHandle->handleRequest(req);
        }
        else
        {
            cout << "节点1没有请求需要处理" << endl;
        }
    }
};

class CHandle2 : public Handle
{
public:
    CHandle2() {}
    CHandle2(const shared_ptr<Handle> &ph)
    {
        m_pNextHandle = ph;
    }
    void handleRequest(int req) override
    {
        if (req > 10 && req < 20)
        {
            cout << "节点2处理请求" << req << endl;
        }
        else if (m_pNextHandle)
        {
            cout << "节点2无法处理该请求" << endl;
            m_pNextHandle->handleRequest(req);
        }
        else
        {
            cout << "节点2没有请求需要处理" << endl;
        }
    }
};

class CHandle3 : public Handle
{
public:
    CHandle3() {}
    CHandle3(const shared_ptr<Handle> &ph)
    {
        m_pNextHandle = ph;
    }
    void handleRequest(int req) override
    {
        if (req > 20 && req < 30)
        {
            cout << "节点3处理请求" << req << endl;
        }
        else if (m_pNextHandle)
        {
            cout << "节点3无法处理该请求" << endl;
            m_pNextHandle->handleRequest(req);
        }
        else
        {
            cout << "节点3没有请求需要处理" << endl;
        }
    }
};

class Client
{
public:
    void handle(const vector<int> &req)//构建责任链：ph1 → ph2 → ph3
    {
        shared_ptr<Handle> ph3(new CHandle3());//next 指向 nullptr
        shared_ptr<Handle> ph2(new CHandle2(ph3));//next 指向 ph3
        shared_ptr<Handle> ph1(new CHandle1(ph2));//next 指向 ph2

        for (auto ele : req)
        {
            ph1->handleRequest(ele);
            cout << "-------------------" << endl;
        }
    }
};

int main()
{
    vector<int> vec = {5, 15, 25, 100};
    Client client;
    client.handle(vec);
    return 0;
}
