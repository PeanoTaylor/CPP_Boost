#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "ThreadPool.h"
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallBack = function<void(const TcpConnectionPtr &)>;

ThreadPool pool(4,10);

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con) : _msg(msg), _con(con)
    {
    }

    void process()
    {
        _msg = "msg: " + _msg;

        _con->sendInLoop(_msg);
    }

private:
    string _msg;
    TcpConnectionPtr _con; // 保证是同一个连接
};

// 连接建立
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!! " << endl;
}

// 消息到达
void onMessage(const TcpConnectionPtr &con)
{
    // 基于这条连接接收客户端发来的数据
    string msg = con->receive();
    cout << ">> recv msg from client: " << msg << endl;
    // 还可以处理一下读到的msg
    // 将处理过后的数据发回客户端
    MyTask task(msg, con);
    pool.addTask(std::bind(&MyTask::process, task));
}

// 连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!! " << endl;
}

#if 0
void test0(){
    Acceptor acceptor("127.0.0.1",22222);
    acceptor.ready();

    EventLoop eloop(acceptor);
    
    eloop.setNewConnectionCallback(onNewConnection);
    eloop.setMessageCallback(onMessage);
    eloop.setCloseCallback(onClose);

    eloop.loop();
}
#endif

void test1()
{
    pool.start();
    TcpServer server("127.0.0.1", 22222);
    server.setAllCallback(onNewConnection,
                          onMessage,
                          onClose);

    server.start();
    pool.stop();
}

int main(void)
{
    test1();
    return 0;
}
