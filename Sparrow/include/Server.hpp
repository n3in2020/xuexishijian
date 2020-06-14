#ifndef SERVER_HPP
#define SERVER_HPP
#include <arpa/inet.h>
#include <memory.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include "Threadsafe_Queue.hpp"
#include "Threadpool.hpp"
#include "Client.hpp"

void accept_conn_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
void read_cb(struct bufferevent *bev, void *ctx);
void event_cb(struct bufferevent *bev, short what, void *ctx);

const int BACKLOG = 5;
class Server
{
public:
    Server(short port_ = 50000) : port(port_), tp{}
    {
        base = event_base_new();
    };
    ~Server()
    {
        evconnlistener_free(listener);
        event_base_free(base);
    }
    void setupListener();
    void run();

private:
    event_base *base;
    evconnlistener *listener;
    short port;
    ThreadPool tp;
    TSQueue<int> q;
    bool done;
};

void Server::setupListener()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    listener = evconnlistener_new_bind(base, accept_conn, &q, LEV_OPT_CLOSE_ON_FREE & LEV_OPT_REUSEABLE, 5, (struct sockaddr *)&sin, sizeof(sin));
}

void Server::run()
{
    for (int i = 0; i < tp.size(); ++i)
    {
        tp.submit([&] {
            int fd;
            event_base *base = event_base_new();
            while (!done)
            {
                q.wait_and_pop(fd);
                client cli(fd);
                bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
                cli.setBuffers(bev);
                bufferevent_setcb(bev, read_cb, NULL, event_cb, &cli);
                bufferevent_enable(bev, EV_READ | EV_WRITE);
                bufferevent_free(bev);
            }
            event_base_free(base);
        });
    }
}

void accept_conn(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sin, int socklen, void *arg)
{
    TSQueue<int> *q = (TSQueue<int>*)arg;
    q->push(fd);
}

#endif