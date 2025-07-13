#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::greater;
using std::less;
using std::swap;
using std::vector;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T *arr, size_t size) : _vec(arr, arr + size), _cmp() {}
    // 调整[parent,n)为堆
    void heapAdjust(size_t parent, size_t n)
    {
        T temp = _vec[parent];
        size_t child = 2 * parent + 1;
        while (child < n)
        {
            // 从左右孩子中选取最优
            if (child + 1 < n && _cmp(_vec[child], _vec[child + 1]))
            {
                ++child;
            }
            if (!_cmp(temp, _vec[child]))
            {
                break;
            }
            _vec[parent] = _vec[child];
            parent = child;
            child = 2 * parent + 1;
        }
        _vec[parent] = temp;
    }
    void sort()
    {
        size_t n = _vec.size();
        // 建堆：从最后一个非叶子节点到根节点
        for (size_t i = n / 2; i > 0; --i)
            heapAdjust(i, n);
        // 排序
        for (size_t i = n - 1; i > 0; --i)
        {
            swap(_vec[0], _vec[i]);
            heapAdjust(0, i);
        }
    }
    void print()
    {
        for (const auto &v : _vec)
            cout << v << " ";
        cout << endl;
    }

private:
    vector<T> _vec;
    Compare _cmp;
};

int main()
{
    int arr[] = {4, 2, 8, 1, 7, 5};
    HeapSort<int, std::less<int>> sorter1(arr, 6); // 升序排序（大根堆）
    sorter1.sort();
    sorter1.print();

    HeapSort<int, std::greater<int>> sorter2(arr, 6); // 降序排序（小根堆）
    sorter2.sort();
    sorter2.print();

    return 0;
}
