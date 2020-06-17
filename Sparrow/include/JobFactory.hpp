#ifndef JOB_FACTORY_HPP
#define JOB_FACTORY_HPP
#include <memory>
#include <fstream>
#include <errno.h>
#include "Client.hpp"
#include "RequestParser.hpp"
#include "Metrics.hpp"
#include "MemoryPool.hpp"
template <typename T>
class Metrics : public Counter<T>, public Timer<T>
{
};

class Job
{
public:
    Job(client &cli_, const request &req_) : cli(cli_), req(req_) {}
    virtual ~Job() = 0;
    virtual void work() = 0;

    void *operator new(size_t size)
    {
        return mp.malloc(size);
    }

    void operator delete(void *, size_t size)
    {

    }
    client &cli;
    request req;
    static MemoryPool mp;
};

MemoryPool Job::mp = MemoryPool(1024, true);

Job::~Job() {}

class IO_bound_job : public Job, public Metrics<IO_bound_job>
{
public:
    IO_bound_job(client &cli, const request &req) : Job(cli, req) {}
    ~IO_bound_job() {}
    void work()
    {
        if (req.cmd.size() != 2)
        {
            cli.send("Unknown arguments\n");
            return;
        }
        std::fstream ifs;
        ifs.open(req.cmd[1], std::ios_base::in);
        if (ifs.is_open())
        {
            char buffer[1024];
            while (!ifs.eof())
            {
                ifs.getline(buffer, 1024);
                cli.send(buffer);
                cli.send("\n");
            }
        }
        else
        {
            cli.send("Cannot open file " + req.cmd[1] + ": " + strerror(errno));
        }
    }

private:
};

class CPU_bound_job : public Job, public Metrics<CPU_bound_job>
{
public:
    CPU_bound_job(client &cli, const request &req) : Job(cli, req) {}
    ~CPU_bound_job() {}
    void work()
    {
        if (req.cmd.size() != 2)
        {
            cli.send("Unknown arguments\n");
            return;
        }
        int n = atoi(req.cmd[1].c_str());
        if (!n)
        {
            cli.send("Expect an integer\n");
        }
        else
        {
            cli.send(std::to_string(func(n)));
        }
    }

    int func(int n)
    {
        if (n < 0)
            return -1;
        else if (n == 1 || n == 2)
        {
            return n;
        }
        else
        {
            return func(n - 1) + func(n - 2);
        }
    }
};

class Unknown_job : public Job, public Metrics<Unknown_job>
{
public:
    Unknown_job(client &cli, const request &req) : Job(cli, req) {}
    ~Unknown_job() {}
    void work()
    {
        cli.send("Unknown command\n");
    }
};

class JobFactory
{
public:
    static Job* createJob(client &cli)
    {
        size_t read_out;
        request req = RequestParser::parse(cli.readln(&read_out));
        if (req.cmd[0] == "CPU")
        {
            return new CPU_bound_job(cli, req);
        }
        else if (req.cmd[0] == "IO")
        {
            return new IO_bound_job(cli, req);
        }
        else
        {
            return new Unknown_job(cli, req);
        }
    }
};

#endif