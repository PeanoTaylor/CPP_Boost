#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class Student
{
public:
    Student(const char *name, int age, float chinese, float math, float english)
        : m_age(age), m_chinese(chinese), m_math(math), m_english(english)
    {
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }
    // 拷贝构造
    Student(const Student &rhs)
        : m_age(rhs.m_age), m_chinese(rhs.m_chinese), m_math(rhs.m_math), m_english(rhs.m_english)
    {
        m_name = new char[strlen(rhs.m_name) + 1];
        strcpy(m_name, rhs.m_name);
    }
    // 拷贝构造赋值运算符
    Student &operator=(const Student &rhs)
    {
        if (this != &rhs)
        {
            delete[] m_name;
            m_name = new char[strlen(rhs.m_name) + 1];
            strcpy(m_name, rhs.m_name);
            m_age = rhs.m_age;
            m_chinese = rhs.m_chinese;
            m_math = rhs.m_math;
            m_english = rhs.m_english;
        }
        return *this;
    }

    ~Student()
    {
        delete[] m_name;
    }

    void print() const
    {
        cout << "Name: " << m_name << ", Age: " << m_age
             << ", Chinese: " << m_chinese
             << ", Math: " << m_math
             << ", English: " << m_english << endl;
    }

    float calScore() const
    {
        return m_chinese + m_math + m_english;
    }

    float getChinese() const { return m_chinese; }

    // 声明 operator<< 为友元，方便访问私有成员
    friend ostream &operator<<(ostream &os, const Student &stu);

private:
    char *m_name;
    int m_age;
    float m_chinese;
    float m_math;
    float m_english;
};

// 重载 operator<<
ostream &operator<<(ostream &os, const Student &stu)
{
    os << "Name: " << stu.m_name
       << ", Age: " << stu.m_age
       << ", Chinese: " << stu.m_chinese
       << ", Math: " << stu.m_math
       << ", English: " << stu.m_english;
    return os;
}
// 打印模板
template <typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << endl;
}

bool compareStudent(const Student &a, const Student &b)
{
    if (a.calScore() != b.calScore())
        return a.calScore() > b.calScore();  // 总分降序
    else
        return a.getChinese() > b.getChinese();  // 语文降序
}

int main()
{
    Student stu1("zhangsan", 20, 100, 100, 100);
    Student stu2("lisi", 20, 70, 90, 100);
    Student stu3("wangwu", 20, 80, 90, 90);
    list<Student> list;
    list.push_back(stu1);
    list.push_back(stu2);
    list.push_back(stu3);

    list.sort(compareStudent);
    display(list);
    return 0;
}
