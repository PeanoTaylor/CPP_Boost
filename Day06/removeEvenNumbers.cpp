#include <iostream>
#include <deque>
#include <algorithm>
using std::cout;
using std::deque;
using std::remove_if;
using std::endl;

template <typename Container>
void display(const Container &container)
{
    for (auto e : container)
    {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    deque<int> dq = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    dq.erase(
        std::remove_if(dq.begin(), dq.end(), [](int x)
                       { return x % 2 == 0; }),
        dq.end());
    
    display(dq);
    return 0;
}
