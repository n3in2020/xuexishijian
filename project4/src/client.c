#include "header.h"
#define STR_LEN 1024
int main(int argc, char *argv[])
{
    int s_fd;
    ssize_t num_read;
    struct sockaddr_in s_addr;
    char buf[STR_LEN];
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == -1)
        errExit("socket");
    memset(&s_addr, 0, sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT_NUM);
    if (argc < 2)
    {
        printf("Usage: %s host\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    inet_aton(argv[1], &s_addr.sin_addr);

    if (connect(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in)) == -1)
        errExit("connect");

    sprintf(buf, "hello from client\n");
    if (write(s_fd, buf, strlen(buf)) != strlen(buf))
        errExit("send");
    
    if((num_read = recv(s_fd, buf, STR_LEN, 0))>0)
    {
        printf("%s", buf);
    }
    if (num_read == -1)
    {
        errExit("read");
    }
    close(s_fd);
    return 0;
}