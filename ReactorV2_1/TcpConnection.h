/**
 * Project 66th
 */

#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "SocketIO.h"
#include "Socket.h"
#include "InetAddress.h"
#include <string>
#include <sstream>
#include <memory>
#include <functional>
using std::function;
using std::ostringstream;
using std::shared_ptr;
using std::string;
class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    /**
     * @param fd
     */

    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallBack = function<void(const TcpConnectionPtr &)>;
    explicit TcpConnection(int fd);

    ~TcpConnection();

    bool isClosed();

    string receive();

    /**
     * @param msg
     */
    void send(const string &msg);

    string toString();
    /**
     * @param cb
     */
    void setNewConnectionCallBack(const TcpConnectionCallBack &cb);

    /**
     * @param cb
     */
    void setMessageCallBack(const TcpConnectionCallBack &cb);

    /**
     * @param cb
     */
    void setCloseCallBack(const TcpConnectionCallBack &cb);

    void handleNewConnectionCallBack();

    void handleMessageCallBack();

    void handleCloseCallBack();

private:
    SocketIO _sockIO;
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    TcpConnectionCallBack _onNewConnection;
    TcpConnectionCallBack _onMessage;
    TcpConnectionCallBack _onClose;

    InetAddress getLocalAddr();

    InetAddress getPeerAddr();
};

#endif //_TCPCONNECTION_H