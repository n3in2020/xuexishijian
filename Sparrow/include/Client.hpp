#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstddef>
#include <string>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct client_info
{
    int id;
    struct sockaddr_in cin;
    socklen_t size;
    std::string IP_address;
    size_t in_bytes;
    size_t out_bytes;
};

static int client_index = 1;
struct client
{
    client(int fd_)
    {
        fd = fd_;
        info.id = client_index++;
        getpeername(fd, (struct sockaddr *)&info.cin, &info.size);
        info.IP_address = inet_ntoa(info.cin.sin_addr);
        info.in_bytes = 0;
        info.out_bytes = 0;
    }
    ~client()
    {
    }
    void setBuffers(bufferevent *bev)
    {
        output_buffer = bufferevent_get_output(bev);
        input_buffer = bufferevent_get_input(bev);
    }
    int send(const std::string &str)
    {
        int temp = evbuffer_add(output_buffer, str.c_str(), str.size());
        info.out_bytes += str.size();
        return temp;
    }
    char *readln(size_t *read_out, evbuffer_eol_style eol_style=EVBUFFER_EOL_CRLF)
    {
        char *temp = evbuffer_readln(input_buffer, read_out, EVBUFFER_EOL_CRLF);
        info.in_bytes += *read_out;
        return temp;
    }
    int fd;
    client_info info;
    evbuffer *output_buffer = nullptr;
    evbuffer *input_buffer = nullptr;
};
#endif