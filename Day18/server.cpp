#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
    // 1.socket套接字
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        return -1;
    }

    // 2.设置ip和port可复用(必须设置在bind前，否则无意义)
    int flag = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag));


    // 3.bind服务器ip和port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr((argv[1]));

    int ret = bind(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    // 4.listen
    listen(socketfd, 128);
    cout << "Server listening on " << argv[1] << ":" << argv[2] << endl;
    
    // 5.等待客户端连接
    int netfd = accept(socketfd, nullptr, nullptr);

    while (true)
    {
        // 接收消息
        char buf[4096] = {0};
        int recvLen = recv(netfd, buf, sizeof(buf), 0);
        if (recvLen < 0)
        {
            cout << "服务器接收失败" << endl;
        }
        else if (recvLen == 0)
        {
            cout << "客户端已关闭连接" << endl;
        }
        else
        {
            cout << "收到客户端消息：" << buf << endl;
        }

        string line;
        getline(std::cin, line);
        int sendLen = send(netfd, line.data(), line.size(), 0);
        if (sendLen < 0)
        {
            cout << "服务器发送失败" << endl;
        }
        else if (sendLen == 0)
        {
            cout << "服务器未发送" << endl;
        }
        else
        {
            cout << "服务器已发送信息" << endl;
        }
    }

    close(netfd);
    close(socketfd);

    return 0;
}
