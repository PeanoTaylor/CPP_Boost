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

TcpConnection::~TcpConnection(){}

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