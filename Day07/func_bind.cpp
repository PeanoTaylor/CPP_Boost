#include <functional>
#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }

int main() {
    std::function<int(int, int)> f = add;
    cout << f(2, 3) << endl; // 输出5
}
