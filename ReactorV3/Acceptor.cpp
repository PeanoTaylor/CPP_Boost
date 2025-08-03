/**
 * Project 66th
 */

#include "Acceptor.h"

/**
 * Acceptor implementation
 */

/**
 * @param ip
 * @param port
 */
Acceptor::Acceptor(const string &ip, unsigned short port)
    : _sock(), _addr(ip, port) {}

Acceptor::~Acceptor()
{
}

/**
 * @return void
 */
void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

/**
 * @return int
 */
int Acceptor::accept()
{
    int connfd = ::accept(_sock.getFd(), nullptr, nullptr);
    if (connfd < 0)
    {
        perror("accept");
    }
    return connfd;
}

/**
 * @return void
 */
void Acceptor::setReuseAddr()
{
    int flag = 1;
    setsockopt(_sock.getFd(), SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
}

/**
 * @return void
 */
void Acceptor::setReusePort()
{
    int flag = 1;
    setsockopt(_sock.getFd(), SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag));
}

/**
 * @return void
 */
void Acceptor::bind()
{
    if (::bind(_sock.getFd(), (struct sockaddr *)_addr.getInetAddressPtr(), sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

/**
 * @return void
 */
void Acceptor::listen()
{
    if (::listen(_sock.getFd(), 128) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}