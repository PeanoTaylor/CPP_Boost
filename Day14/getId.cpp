#include <iostream>
#include <thread>
#include <functional>
using std::cout;
using std::endl;
using std::thread;
using std::function;
using std::bind;

void threadFunc()
{
    cout << "child thread end" << endl;
}

// 普通函数
/* int main()
{
    thread th(threadFunc);
    cout << "child thread id = " << th.get_id() << endl;
    cout << "Main thread id = " << std::this_thread::get_id() << endl;//主线程的线程id，可以在main函数中调用this_thread::get_id函数
    th.join();
    return 0;
} */

// 函数指针
/* int main()
{
    typedef void (*pFunc)();
    pFunc f = &threadFunc;
    thread th(f);
    cout << "child thread id = " << th.get_id() << endl;
    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
}
 */
// 函数引用
/* int main()
{
    typedef void (&pFunc)();
    pFunc f = threadFunc;
    thread th(f);
    cout << "child thread id = " << th.get_id() << endl;
    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
} */

// 函数对象
/* class Example{
public:
    void operator()(){
        cout << "child thread end" << endl;
    }
};


int main()
{
    Example ex;
    thread th(ex);
    cout << "child thread id = " << th.get_id() << endl;
    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
} */

// Lambda表达式
/* int main()
{
    
    thread th([](){
        cout << "child thread id = " << std::this_thread::get_id() << endl;
    });

    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
} */

// function对象
/* int main()
{
    
    function<void()> f = ([](){
        cout << "child thread id = " << std::this_thread::get_id() << endl;
    });
    thread th(f);
    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
} */

// bind
/* int main()
{
    thread th(bind(threadFunc));
    cout << "child thread id = " << th.get_id() << endl;
    cout << "Main thread id = " << std::this_thread::get_id() << endl;
    th.join();
    return 0;
} */


