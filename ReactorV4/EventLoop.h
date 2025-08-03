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
#include <mutex>
#include <sys/eventfd.h>
#include <functional>
using std::function;
using std::make_shared;
using std::map;
using std::lock_guard;
using std::mutex;
using std::shared_ptr;
using std::vector;
class TcpConnection;
#define OPEN_MAX 1024
class EventLoop
{
public:
    /**
     * @param acc
     */
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallBack = function<void(const TcpConnectionPtr &)>;
    EventLoop(Acceptor &acc);

    ~EventLoop();

    void loop();

    void unloop();

    /**
     * @param cb
     */
    void setNewConnectionCallBack(const TcpConnectionCallBack &&cb);

    /**
     * @param cb
     */
    void setMessageCallBack(const TcpConnectionCallBack &&cb);

    /**
     * @param cb
     */
    void setCloseCallBack(const TcpConnectionCallBack &&cb);

    int createEventFd();

    void handleRead();

    void wakeup();

    void doPendingFunctors();

    void runInLoop(function<void()> cb);

private:
    int _epfd;
    int _evtfd;
    vector<struct epoll_event> _evlist;
    bool _isLooping;
    Acceptor &_acceptor;
    map<int, shared_ptr<TcpConnection>> _conns;

    TcpConnectionCallBack _onNewConnection;
    TcpConnectionCallBack _onMessage;
    TcpConnectionCallBack _onClose;

    std::vector<function<void()>> _pendingFunctors;
    mutex _mutex;

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