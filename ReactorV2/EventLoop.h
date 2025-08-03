/**
 * Project 66th
 */


#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include "Acceptor.h"
#include "TcpConnection.h"
#include <vector>
#include <memory>
#include <map>
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::map;
#define OPEN_MAX 1024
class EventLoop {
public: 
    
/**
 * @param acc
 */
EventLoop(Acceptor & acc);
    
~EventLoop();
    
void loop();
    
void unloop();
private: 
    int _epfd;
    vector<struct epoll_event> _evlist;
    bool _isLooping;
    Acceptor & _acceptor;
    map<int,shared_ptr<TcpConnection>> _conns;
    
int createEpollFd();
    
void addEpollReadFd(int fd);
    
void delEpollReadFd(int fd);
    
void waitEpollFd();
    
void handleNewConnection();
    
/**
 * @param fd
 */
void handleMessage(int fd);
};

#endif //_EVENTLOOP_H