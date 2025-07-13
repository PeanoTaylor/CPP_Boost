#include <iostream>
#include <set>
using namespace std;

template <typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << " ";
    cout << endl;
}

template <typename T>
T add(T x, T y)
{
    return x + y;
}
// 函数模板特化：针对set<int>实现集合合并
template <>
set<int> add<set<int>>(set<int> s1, set<int> s2)
{
    set<int> result = s1;
    result.insert(s2.begin(), s2.end());
    return result;
}

int main()
{
    set<int> s1, s2;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        s1.insert(x);
    }

    for (int i = 0; i < m; ++i)
    {
        int x;
        cin >> x;
        s2.insert(x);
    }

    set<int> s3 = add(s1, s2);
    display(s3);

    return 0;
}
