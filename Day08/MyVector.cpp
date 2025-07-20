#include <iostream>
#include <memory>
using namespace std;

template <class T>
class MyVector
{
public:
    using iterator = T *;
    MyVector();
    ~MyVector();

    void push_back(const T &);
    void pop_back();
    int size() const;
    int capacity() const;
    iterator begin() const;
    iterator end() const;

private:
    void rellocate();
    // 构建对象与申请空间分开
    static std::allocator<T> _alloc;

    T *_start;
    T *_finish;
    T *_end_of_storage;
};

// 申请空间
template <class T>
std::allocator<T> MyVector<T>::_alloc;

template <class T>
int MyVector<T>::size() const
{
    return _finish - _start;
}

template <class T>
int MyVector<T>::capacity() const
{
    return _end_of_storage - _start;
}

template <class T>
MyVector<T>::MyVector()
: _start(nullptr)
, _finish(nullptr)
, _end_of_storage(nullptr)
{}

template <class T>
MyVector<T>::~MyVector()
{
    if (_start)
    {
        while (_start != _finish)
        {
            _alloc.destroy(--_finish);
        }
    }
    _alloc.deallocate(_start, capacity());

    _start = nullptr;
    _finish = nullptr;
    _end_of_storage = nullptr;
}

template <class T>
void MyVector<T>::push_back(const T &value){
   if(size() == capacity()){
        rellocate();
   }

   _alloc.construct(++_finish,value);
}

template <class T>
void MyVector<T>::pop_back(){
    _alloc.destroy(--_finish);
}

template <class T>
void MyVector<T>::rellocate(){
    //1.申请两倍的新空间
    int old_size = size();
    int new_capacity = old_size != 0 ? 2 * old_size : 1;

    T *new_start = _alloc.allocate(new_capacity);
    T *new_finish = new_start;

    new_finish = std::uninitialized_copy(_start,_finish,new_start);
    // 依次将旧空间元素进行析构
    while(_start != _finish){
        _alloc.destroy(--_finish);
    }
    _alloc.deallocate(_start,old_size);

    // 更新指针
    _start = new_start;
    _finish = new_finish;
    _end_of_storage = new_start + new_capacity;

}

template <class T>   
typename MyVector<T>::iterator MyVector<T>::begin() const
{
    return _start;
}

template <class T>   
typename MyVector<T>::iterator MyVector<T>::end() const
{
    return _finish;
}

template <class T>
void printCapacity(const MyVector<T> & vec)
{
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec.capacity() << endl;
}

int main()
{
    MyVector<int> vec;
    printCapacity(vec);
    cout << endl;

    vec.push_back(1);
    printCapacity(vec);
    cout << endl;
    vec.push_back(1);
    printCapacity(vec);
    cout << endl;
    vec.push_back(1);
    printCapacity(vec);
    cout << endl;
    vec.push_back(1);
    printCapacity(vec);
    cout << endl;
    vec.push_back(1);
    printCapacity(vec);
    cout << endl;

    for(auto & ele : vec)
    {
        cout << ele << " ";
    }
    cout << endl;
    return 0;
}
