#include "Acceptor.h"
#include "EventLoop.h"

int main()
{
    Acceptor acceptor("127.0.0.1", 22222);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.loop();  // 支持多客户端并发交互

    return 0;
}
