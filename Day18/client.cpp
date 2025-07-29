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

int main(int argc, char **argv)
{
    // 1.创建套接字
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd < 0){
        perror("socket");
        return -1;
    }

    // 2.bind服务器ip和port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    // 3.connect
    int ret = connect(socketfd,(struct sockaddr *)&addr,sizeof(addr));
    if(ret < 0){
        perror("connect");
        close(socketfd);
        return -1;
    }
    cout << "connect success" << endl;

    while(true){
        string line;
        getline(std::cin,line);
        int sendLen = send(socketfd,line.data(),line.size(),0);
        if(sendLen < 0){
            cout << "客户端发送出错" << endl;
        }else if(sendLen == 0){
            cout << "客户端未发送任何信息" << endl;
        }else{
            cout << "客户端发送正常" << endl;
        }

        char buf[128] = {0};
        int recvLen = recv(socketfd,buf,sizeof(buf),0);
        if(recvLen < 0){
            cout << "客户端接收失败" << endl;
        }else if(recvLen == 0){
            cout << "客户端未接收任何消息" << endl;
        }else{
            cout << "收到服务端消息：" <<buf << endl;
            cout << "客户端接收成功" << endl;
        }
    }
    close(socketfd);
    return 0;
}

