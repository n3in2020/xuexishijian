#include "header.h"
#include <sys/poll.h>
#define BACKLOG 10
#define MAXEVENTS 1024

int main(int argc, char *argv[])
{
    int sfd, cfd;
    ssize_t num_read, num_write;
    char buf[STR_LEN];
    struct sockaddr_in saddr;
    int enable;
    struct pollfd readfds[1024];
    int maxfd, currentfd = 0;
    int ready;
    int i;
    int running, close_connection;
    // 创建socket sfd
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        close(sfd);
        errExit("socket");
    }
    // 创建socket sfd
    enable = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
    {
        close(sfd);
        errExit("setsockopt REUSEADDR");
    }
    // 将sfd设置为非阻塞
    if (ioctl(sfd, FIONBIO, &enable) == -1)
    {
        close(sfd);
        errExit("ioctl");
    }
    // 绑定地址和端口
    memset(&saddr, 0, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT_NUM);
    saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) == -1)
    {
        close(sfd);
        errExit("bind");
    }
    // 监听sfd
    if (listen(sfd, BACKLOG) == -1)
    {
        close(sfd);
        errExit("listen");
    }
    // 将sfd添加到测试可读的集合里
    readfds[currentfd].fd = sfd;
    readfds[currentfd].events = POLLIN;
    // 运行服务器
    running = 1;
    while (running)
    {
        maxfd = currentfd;
        // 执行poll获得可读的文件描述符数目
        ready = poll(readfds, maxfd + 1, 600);
        if (ready == -1)
        {
            running = 0;
            perror("poll");
            break;
        }
        // 遍历文件描述符
        for (i = 0; i < maxfd + 1 && ready; i++)
        {
            // 如果当前描述符已关闭那么跳过
            if (readfds[i].fd == -1)
                continue;
            // 如果该文件描述符可读，执行操作
            if (readfds[i].revents & POLLIN)
            {
                cfd = readfds[i].fd;
                close_connection = 0;
                ready--;
                // 如果该文件描述符是用于监听新连接的，那么接受新连接
                if (cfd == sfd)
                {
                    // 如果文件描述符大于支持的最大的数目，那么拒绝接受
                    if (maxfd >= MAXEVENTS)
                    {
                        printf("can't hanle more connections\n");
                        continue;
                    }
                    // 接受客户端请求并用cfd表示这个socket的文件描述符
                    cfd = accept(sfd, NULL, NULL);
                    if (cfd == -1)
                    {
                        perror("accept");
                        // sfd目前不可读下次再读
                        if (errno == EINTR || errno == EAGAIN)
                            continue;
                        // 出现错误，停止执行
                        else
                        {
                            running = 0;
                            break;
                        }
                    }  
                    // 将cfd设置成非阻塞
                    if (ioctl(cfd, FIONBIO, &enable) == -1)
                    {
                        close(sfd);
                        errExit("ioctl");
                    }
                    // 将cfd添加到测试可读的集合里 
                    currentfd++;
                    readfds[currentfd].fd = cfd;
                    readfds[currentfd].events = POLLIN;
                } 
                // 否则是客户端请求
                else
                {
                    // 获得客户端发来的信息并原封不动的重新发给客户端
                    while (1)
                    {
                        num_read = readLine(cfd, buf, STR_LEN);
                        if (num_read == 0)
                        {
                            close_connection = 1;
                            break;
                        }
                        else if (num_read == -1)
                        {
                            perror("read");
                            if (errno == EWOULDBLOCK || errno == EAGAIN)
                            {
                                break;
                            }
                            else
                            {
                                close_connection = 1;
                                break;
                            }
                        }
                        else
                        {
                            printf("[%zd bytes received]\n", num_read);
                            if (write(cfd, buf, num_read) != num_read)
                            {
                                perror("write");
                                close_connection = 1;
                                break;
                            }
                        }
                    }
                }
                // 如果客户端断开连接，执行清理操作
                if (close_connection)
                {
                    readfds[i].fd = -1;
                    close(cfd);
                    if (i == currentfd)
                    {
                        while (readfds[currentfd].fd == -1)
                        {
                            currentfd--;
                        }
                    }
                }
            }
        }
    }
    close(sfd);
}