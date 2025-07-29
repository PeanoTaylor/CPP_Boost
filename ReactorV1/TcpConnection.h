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
using std::string;
using std::ostringstream;
class TcpConnection
{
public:
    /**
     * @param fd
     */
    explicit TcpConnection(int fd);

    ~TcpConnection();

    string receive();

    /**
     * @param msg
     */
    void send(const string &msg);

    string toString();

private:
    SocketIO _sockIO;
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    InetAddress getLocalAddr();

    InetAddress getPeerAddr();
};

#endif //_TCPCONNECTION_H