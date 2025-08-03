/**
 * Project 66th
 */

#include "EventLoop.h"

/**
 * EventLoop implementation
 */

/**
 * @param acc
 */
EventLoop::EventLoop(Acceptor &acc) : _epfd(createEpollFd()), _isLooping(false), _acceptor(acc), _evlist(OPEN_MAX)
{
    addEpollReadFd(_acceptor.getFd());
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

/**
 * @return void
 */
void EventLoop::loop()
{
    _isLooping = true;
    while (_isLooping)
    {
        waitEpollFd();
    }
}

/**
 * @return void
 */
void EventLoop::unloop()
{
    _isLooping = false;
}

/**
 * @return int
 */
int EventLoop::createEpollFd()
{
    _epfd = epoll_create(OPEN_MAX);
    if (_epfd < 0)
    {
        perror("epoll create");
        exit(EXIT_FAILURE);
    }
    return _epfd;
}

/**
 * @return void
 */
void EventLoop::addEpollReadFd(int fd) // 注册新会话连接
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
    cout << ret << endl;
    if (ret < 0)
    {
        perror("epoll_ctl ADD");
        exit(EXIT_FAILURE);
    }
}

/**
 * @return void
 */
void EventLoop::delEpollReadFd(int fd)
{
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, nullptr);
    if (ret < 0)
    {
        perror("epoll_ctl DEL");
        exit(EXIT_FAILURE);
    }
}

/**
 * @return void
 */
void EventLoop::waitEpollFd()
{
    struct epoll_event ep[OPEN_MAX];
    int nready = epoll_wait(_epfd, ep, OPEN_MAX, -1);
    if (nready < 0)
    {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nready; ++i)
    {
        // 异常处理
        if (!(ep[i].events & EPOLLIN))
        {
            continue;
        }

        if (ep[i].data.fd == _acceptor.getFd())
        { // 新的连接
            handleNewConnection();
        }
        else
        {
            handleMessage(ep[i].data.fd);
        }
    }
}

/**
 * @return void
 */
void EventLoop::handleNewConnection()
{
    int connfd = _acceptor.accept();
    if (connfd < 0) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    addEpollReadFd(connfd);
    _conns[connfd] = make_shared<TcpConnection>(connfd);
    cout << "new client: " << _conns[connfd]->toString() << endl;
}

/**
 * @param fd
 * @return void
 */
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if (it != _conns.end())
    {
        string msg = it->second->receive();
        if (msg.empty())
        {
            delEpollReadFd(fd);
            _conns.erase(it);
            close(fd);
            cout << "client " << fd << " has disconnect " << endl;
        }
        else
        {
            cout << "recv from client " << fd << ": " << msg << endl;
            it->second->send(msg);
        }
    }
}