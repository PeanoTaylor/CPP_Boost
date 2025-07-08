#include <iostream>
#include <list>
#include <deque>
using namespace std;

// 通用打印模板
template <typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << " ";
    cout << endl;
}

int main()
{
    list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    deque<int> d1, d2;

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if (*it % 2 == 0)
        {
            d1.push_back(*it);
        }
        else
        {
            d2.push_back(*it);
        }
    }

    cout << "d1 elements:" << endl;
    display(d1);
    cout << "d2 elements:" << endl;
    display(d2);
    return 0;
}
