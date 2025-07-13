#include <iostream>
#include <vector>
#include <functional> // for std::less
using namespace std;

template <typename T, typename Compare = std::less<T>>
class MyQsort
{
public:
    MyQsort(T *arr, size_t size, Compare com = Compare())
        : m_vec(arr, arr + size)
    {
        if (size > 0)
        {
            quick(0, size - 1, com);
        }
    }
    void quick(int left, int right, Compare &com)
    {
        if (left >= right)
        {
            return;
        }
        int pivotIdx = partition(left, right, com);
        quick(left, pivotIdx - 1, com);
        quick(pivotIdx + 1, right, com);
    }
    int partition(int left, int right, Compare &com)
    {
        T pivot = m_vec[left];
        int i = left + 1;
        for (int j = left + 1; j <= right; ++j)
        {
            if (com(m_vec[j], pivot))
            {
                swap(m_vec[i], m_vec[j]);
                ++i;
            }
        }
        swap(m_vec[left], m_vec[i - 1]); // 把 pivot 放到中间
        return i - 1;
    }
    void print()
    {
        for (const auto &e : m_vec)
        {
            cout << e << " ";
        }
        cout << endl;
    }

private:
    vector<T> m_vec;
};
int main()
{
    int arr[] = {5, 2, 9, 1, 7};
    MyQsort<int> sorter(arr, 5);  // 使用默认的 std::less
    sorter.print();  // 输出：1 2 5 7 9
    return 0;
}
