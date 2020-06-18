#ifndef SERVER_HPP
#define SERVER_HPP
#include <arpa/inet.h>
#include <memory.h>
#include <memory>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <glog/logging.h>
#include <atomic>
#include <event2/thread.h>
#include "Threadsafe_Queue.hpp"
#include "Threadpool.hpp"
#include "Client.hpp"
#include "JobFactory.hpp"
#include "CommandManager.hpp"
void accept_conn_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
void read_cb(struct bufferevent *bev, void *ctx);
void event_cb(struct bufferevent *bev, short what, void *ctx);

const int BACKLOG = 5;
class Server
{
public:
    Server(short port_ = 50000) : port(port_), tp{}, cm{}
    {
        evthread_use_pthreads();
        base = event_base_new();
        done = false;
    };
    ~Server()
    {
        done = true;
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
    std::atomic<bool> done;
    CommandManager cm;
};

void Server::setupListener()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    listener = evconnlistener_new_bind(base, accept_conn_cb, &q, LEV_OPT_CLOSE_ON_FREE & LEV_OPT_REUSEABLE, 5, (struct sockaddr *)&sin, sizeof(sin));
    if (!listener)
    {
        LOG(ERROR) << "when setup listener: " << strerror(errno);
    }
}

void Server::run()
{
    tp.submit([&] {
        while (cm.DoREPL())
            ;
        done = true;
        if (event_base_loopbreak(base) == -1)
        {
            perror("event_base_loopbreak");
        }
        std::cout << "wait for finish\n";
    });
    for (int i = 1; i < tp.size(); ++i)
    {
        tp.submit([&] {
            int fd;
            event_base *base = event_base_new();
            while (!done.load())
            {
                if (q.try_pop(fd))
                {
                    client cli(fd);
                    bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
                    cli.setBuffers(bev);
                    bufferevent_setcb(bev, read_cb, NULL, event_cb, &cli);
                    if (bufferevent_enable(bev, EV_READ | EV_WRITE) == -1)
                    {
                        LOG(ERROR) << "bufferevent_enable: " << strerror(errno);
                    }
                    if (event_base_dispatch(base) == -1)
                    {
                        LOG(ERROR) << "event_base_dispatch: " << strerror(errno);
                    }
                    bufferevent_free(bev);
                }
                else
                {
                    std::this_thread::yield();
                }
            }
            event_base_free(base);
        });
    }

    event_base_dispatch(base);
}

void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sin, int socklen, void *arg)
{
    TSQueue<int> *q = (TSQueue<int> *)arg;
    q->push(fd);
}

void read_cb(struct bufferevent *bev, void *ctx)
{
    client *cli = (client *)ctx;
    auto job = JobFactory::createJob(*cli);
    job->work();
    delete (job);
}
void event_cb(struct bufferevent *bev, short what, void *ctx)
{
}
#endif