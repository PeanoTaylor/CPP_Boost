#include <iostream>
#include <list>
using namespace std;

template <typename Container>
void display(const Container &container)
{
    for (const auto &e : container)
        cout << e << " ";
    cout << endl;
}

struct Compare
{
    bool operator()(const int &lhs, const int &rhs) const
    {
        cout << "Compare" << endl;
        return lhs < rhs;
    }
};

int main()
{
    list<int> list = {8, 7, 5, 9, 0, 1, 3, 2, 6, 4};

    list.sort();
    display(list);
    list.sort(Compare());
    display(list);

    return 0;
}
