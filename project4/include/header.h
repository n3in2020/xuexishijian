#ifndef HEADER_H
#define HEADER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#define PORT_NUM 50000
#define STR_LEN 1024

void errExit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

ssize_t readLine(int fd, void *buffer, size_t n)
{
    ssize_t numRead;
    size_t totRead;
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    buf = (char *)buffer;

    totRead = 0;

    for (;;)
    {
        numRead = read(fd, &ch, 1);
        if (numRead == -1)
        {
            if (errno == EINTR)
                continue;
            else
                return -1;
        }
        else if (numRead == 0)
        {
            if (totRead == 0)
            {
                return 0;
            }
            else
                break;
        }
        else
        {
            if (totRead < n - 1)
            {
                totRead++;
                *buf++ = ch;
            }
            if (ch == '\n')
                break;
        }
    }
    *buf = '\0';
    return totRead;
}


#endif