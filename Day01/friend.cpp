#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass() {}
    MyClass(int data)
        : m_data(data)
    {
    }
    // 声明友元函数
    friend void friendFunc(const MyClass &cls);

private:
    int m_data;
    void privateFunc()
    {
        cout << "privateFunc" << endl;
    }
    // const函数由const对象访问
    void privateFunc() const
    {
        cout << "const privateFunc" << endl;
    }
};

// 使用了const
void friendFunc(const MyClass &cls)
{
    // 友元函数访问类中私有成员
    cout << cls.m_data << endl;
    cls.privateFunc();
}

void test1()
{
    const MyClass cls2{1};
    friendFunc(cls2);
}
int main()
{
    test1();
    return 0;
}
