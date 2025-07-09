#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    vector<vector<string>> multiTable(9);
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            // 生成乘法表达式
            string res = to_string(j) + "×" + to_string(i) + "=" + to_string(i * j);
            multiTable[i - 1].push_back(res);
        }
    }

    for (const auto &row : multiTable) {
        for (const auto &col : row) {
            cout << setw(10) << col;
        }
        cout << endl;
    }
    return 0;
}
