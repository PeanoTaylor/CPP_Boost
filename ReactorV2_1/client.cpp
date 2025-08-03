#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(22222);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (ret < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    char buf[1024];
    while (true)
    {
        // send
        cin.getline(buf, sizeof(buf));
        if (strlen(buf) == 0)
            break;
        strcat(buf, "\n");
        write(sockfd, buf, strlen(buf));

        // recv
        char buf[1024];
        int n = recv(sockfd, buf, sizeof(buf), 0);
        if (n == -1)
        {
            perror("recv");
        }
        else if (n == 0)
        {
            printf("peer closed\n");
        }
        else
        {
            buf[n] = '\n'; // 如果是字符串
            cout << ">>recv msg from server: " << buf << endl;
        }
    }

    close(sockfd);
    return 0;
}
