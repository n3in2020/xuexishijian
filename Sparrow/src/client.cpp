#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

void usage(char *pName)
{
    printf("%s [-p port] CPU num|IO filename\n", pName);
    printf("\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argv[0]);
    }
    short port = 50000;
    char request[1024];
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            usage(argv[0]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            if (i + 1 == argc)
            {
                usage(argv[0]);
            }
            ++i;
            port = atoi(argv[i]);
            if (!port)
            {
                usage(argv[0]);
            }
        }
        else if (strcmp(argv[i], "CPU") == 0 || strcmp(argv[i], "cpu") == 0)
        {
            if (i + 1 == argc)
            {
                usage(argv[0]);
            }
            ++i;
            int num = atoi(argv[i]);
            if (!num)
            {
                usage(argv[0]);
            }
            snprintf(request, sizeof(request), "%s\t%d\n", "CPU", num);
        }
        else if (strcmp(argv[i], "IO") == 0 || strcmp(argv[i], "io") == 0)
        {
            if (i + 1 == argc)
            {
                usage(argv[0]);
            }
            ++i;
            snprintf(request, sizeof(request), "%s\t%s\n", "IO", argv[i]);
        }
        else
        {
            usage(argv[0]);
        }
    }

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    send(sfd, request, strlen(request), 0);
    const int BUFSIZE = 1024;
    char buffer[BUFSIZE];
    int num_read;
    while (true)
    {
        num_read = recv(sfd, buffer, BUFSIZE - 1, 0);
        if (num_read == 0)
            break;
        else if (num_read == -1)
        {
            perror("recv");
            close(sfd);
            exit(EXIT_FAILURE);
        }
        buffer[num_read] = '\0';
        printf("%s", buffer);
        if (num_read < BUFSIZE - 1)
            break;
    }
    printf("\n");
    close(sfd);
    return 0;
}
