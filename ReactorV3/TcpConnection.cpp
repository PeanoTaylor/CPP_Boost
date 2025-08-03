/**
 * Project 66th
 */

#include "TcpConnection.h"

/**
 * TcpConnection implementation
 */

/**
 * @param fd
 */
TcpConnection::TcpConnection(int fd)
    : _sock(fd), _sockIO(fd), _localAddr(getLocalAddr()), _peerAddr(getPeerAddr())
{
}

TcpConnection::~TcpConnection() {}

// 进行一次复制式的预读取
// 如果读到的字符数为0，代表连接已经断开了
bool TcpConnection::isClosed()
{
    char buf[5] = {0};
    int ret = ::recv(_sock.getFd(), buf, sizeof(buf), MSG_PEEK);
    return 0 == ret;
}
/**
 * @return string
 */
string TcpConnection::receive()
{
    char buf[65535] = {0};
    int ret = _sockIO.readLine(buf, sizeof(buf));
    if (ret > 0)
    {
        return string(buf);
    }
    else
    {
        // 读到0表示对端关闭，<0表示出错
        return string();
    }
}

/**
 * @param msg
 * @return void
 */
void TcpConnection::send(const string &msg)
{
    _sockIO.writen(const_cast<char *>(msg.c_str()), msg.size());
}

/**
 * @return string
 */
string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.getIp() << ":" << _localAddr.getPort() << "->" << _peerAddr.getIp() << ":" << _peerAddr.getPort();
    return oss.str();
}

/**
 * @return InetAddress
 */
// 获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    // 获取本端地址的函数getsockname
    int ret = getsockname(_sock.getFd(), (struct sockaddr *)&localaddr, &addrlen);
    if (ret < 0)
    {
        perror("getsockname");
    }

    return InetAddress(localaddr);
}

/**
 * @return InetAddress
 */
// 获取对端地址的函数getsockname
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in peeraddr;
    socklen_t addrlen = sizeof(peeraddr);
    // 获取对端地址的函数getsockname
    int ret = getpeername(_sock.getFd(), (struct sockaddr *)&peeraddr, &addrlen);
    if (ret < 0)
    {
        perror("getpeername");
    }

    return InetAddress(peeraddr);
}

/**
 * @param cb
 * @return void
 */
void TcpConnection::setNewConnectionCallBack(const TcpConnectionCallBack &cb)
{
    _onNewConnection = cb;
}

/**
 * @param cb
 * @return void
 */
void TcpConnection::setMessageCallBack(const TcpConnectionCallBack &cb)
{
    _onMessage = cb;
}

/**
 * @param cb
 * @return void
 */
void TcpConnection::setCloseCallBack(const TcpConnectionCallBack &cb)
{
    _onClose = cb;
}

/**
 * @return void
 */
void TcpConnection::handleNewConnectionCallBack()
{
    if (_onNewConnection)
        // 触发新连接处理时，传递自己（智能指针）给回调
        _onNewConnection(shared_from_this());
}

/**
 * @return void
 */
void TcpConnection::handleMessageCallBack()
{
    if (_onMessage)
        _onMessage(shared_from_this());
}

/**
 * @return void
 */
void TcpConnection::handleCloseCallBack()
{
    if (_onClose)
        _onClose(shared_from_this());
}