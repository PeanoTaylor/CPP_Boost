#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>
using namespace std;

class Person
{
public:
    Person(const char *name, float score = 0.0) : m_score(score)
    {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }
    // 拷贝构造函数（深拷贝）
    Person(const Person &rhs)
    {
        m_name = new char[strlen(rhs.m_name) + 1];
        strcpy(m_name, rhs.m_name);
        m_score = rhs.m_score;
    }

    // 拷贝赋值运算符（深拷贝）
    Person &operator=(const Person &rhs)
    {
        if (this != &rhs)
        {
            delete[] m_name;
            m_name = new char[strlen(rhs.m_name) + 1];
            strcpy(m_name, rhs.m_name);
            m_score = rhs.m_score;
        }
        return *this;
    }
    ~Person()
    {
        if (m_name)
        {
            delete[] m_name;
            m_name = nullptr;
        }
    }

    void print()
    {
        cout << "name:" << m_name << ",score:" << m_score << endl;
    }

    void setScore(float score)
    {
        m_score = score;
    }

    float getScore() const
    {
        return m_score;
    }
    friend ostream &operator<<(ostream &os, const Person &p);

private:
    char *m_name;
    float m_score;
};

// 重载 operator<<
ostream &operator<<(ostream &os, const Person &p)
{
    os << "Name: " << p.m_name
       << ", Score: " << p.m_score;
    return os;
}

void setScore(Person &p)
{
    deque<float> ds;

    for (int i = 0; i < 10; ++i)
    {
        int score = rand() % 41 + 60; // [60,100]
        cout << score << " ";
        ds.push_back(score);
    }
    cout << endl;

    // 对deque数据排序
    sort(ds.begin(), ds.end());
    // 去掉最高分与最低分
    ds.pop_front();
    ds.pop_back();

    double total = 0;
    for (auto it = ds.begin(); it != ds.end(); ++it)
    {
        total += (*it);
    }

    float avg = total / ds.size();
    p.setScore(avg);
}

// 打印模板
template <typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << endl;
}

int main()
{
    vector<Person> p;
    p.emplace_back("A");
    p.emplace_back("B");
    p.emplace_back("C");
    p.emplace_back("D");
    p.emplace_back("E");

    // 打分
    for (auto &e : p)
        setScore(e);

    display(p);
    return 0;
}
