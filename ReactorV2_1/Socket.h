/**
 * Project 66th
 */

#ifndef _SOCKET_H
#define _SOCKET_H

#include "NonCopyable.h"
#include <sys/types.h> 
#include <sys/socket.h>
#include <iostream>

class Socket : public NonCopyable
{
public:
    Socket();

    /**
     * @param fd
     */
    explicit Socket(int fd);// 避免隐式转换

    ~Socket();

    int getFd();

private:
    int _fd;
};

#endif //_SOCKET_H