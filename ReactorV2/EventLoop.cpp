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
EventLoop::EventLoop(Acceptor &acc)
        : _epfd(createEpollFd())
        , _evlist(OPEN_MAX)
        , _isLooping(false)
        , _acceptor(acc){
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

    _epfd = epoll_create(OPEN_MAX); // 创建红黑树的根节点（使用数据结构：红黑树 + 就绪链表）
    if (_epfd == -1)
    {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }
    return _epfd;
}

/**
 * @return void
 */
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) < 0)
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
    if (epoll_ctl(_epfd, EPOLL_CTL_DEL, _acceptor.getFd(), nullptr) < 0)
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
    if (nready == -1)
    {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nready; ++i)
    {
        if (!(ep[i].events & EPOLLIN))
        {
            continue; // 信号中断可重试
        }

        if (ep[i].data.fd == _acceptor.getFd())
        {
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
        perror("accept error");
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
            _conns.erase(fd);
            close(fd);
            cout << "client " << fd << " closed." << endl;
        }
        else
        {
            cout << "recv from client " << fd << ": " << msg << endl;
            it->second->send(msg);
        }
    }
}
