#include "Acceptor.h"
#include "EventLoop.h"
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallBack = function<void(const TcpConnectionPtr &)>;

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
    con->send(msg);
}

// 连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!! " << endl;
}

int main()
{

    Acceptor acceptor("127.0.0.1", 22222);
    acceptor.ready();

    EventLoop loop(acceptor);

    loop.setNewConnectionCallBack(onNewConnection);
    loop.setMessageCallBack(onMessage);
    loop.setCloseCallBack(onClose);
    loop.loop(); // 支持多客户端并发交互

    return 0;
}
