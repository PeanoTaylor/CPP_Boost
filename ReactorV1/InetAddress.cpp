/**
 * Project 66th
 */

#include "InetAddress.h"

/**
 * InetAddress implementation
 */

/**
 * @param ip
 * @param port
 */
InetAddress::InetAddress(const string &ip, unsigned short port)
{
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

/**
 * @param addr
 */
InetAddress::InetAddress(const struct sockaddr_in &addr)
{
    _addr = addr;
}

InetAddress::~InetAddress()
{
}

/**
 * @return string
 */
string InetAddress::getIp()
{
    return string(inet_ntoa(_addr.sin_addr));//网络字节序转为x.x.x.x
}

/**
 * @return unsigned short
 */
unsigned short InetAddress::getPort()
{
    return ntohs(_addr.sin_port);//网络字节序转为主机字节序
}

/**
 * @return struct sockaddr_in *
 */
struct sockaddr_in *InetAddress::getInetAddressPtr()
{
    return &_addr;
}