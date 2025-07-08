#include <iostream>
#include <deque>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string word;
    deque<string> deq;
    cout << "input word:" << endl;
    while (cin >> word)
    {
        deq.push_back(word);
    }

    cout << "deque elements:" << endl;
    for (auto it = deq.begin(); it != deq.end(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}
