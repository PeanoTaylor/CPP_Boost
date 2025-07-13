#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    map<string, map<string, int>> sales; // origin -> (fruit -> count)

    int n;
    cin >> n;
    while (n--)
    {
        string fruit, origin;
        int count;
        cin >> fruit >> origin >> count;
        sales[origin][fruit] += count;
    }

    for (const auto &origin_pair : sales)
    {
        cout << origin_pair.first << endl;
        for (const auto &fruit_pair : origin_pair.second)
        {
            cout << "    |----" << fruit_pair.first << "(" << fruit_pair.second << ")" << endl;
        }
    }

    return 0;
}
