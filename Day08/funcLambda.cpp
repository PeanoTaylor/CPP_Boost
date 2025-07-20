#include <iostream>
#include <functional>
using std::cout;
using std::endl;

std::function<int(int, int)> createAdd()
{
    return [](int x, int y)
    {
        return x + y;
    };
}

int main()
{
    std::function<int(int, int)> add = createAdd();
    cout << add(1, 2) << endl;
    return 0;
}
