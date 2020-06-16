#ifndef JOB_FACTORY_HPP
#define JOB_FACTORY_HPP
#include <memory>
#include <fstream>
#include <errno.h>
#include "Client.hpp"
#include "RequestParser.hpp"
class Job
{
public:
    Job(client &cli_, const request &req_) : cli(cli_), req(req_) {}
    virtual void work() = 0;

    client &cli;
    request req;
};

class IO_bound_job : public Job
{
public:
    IO_bound_job(client &cli, const request &req) : Job(cli, req) {}
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

class CPU_bound_job : public Job
{
public:
    CPU_bound_job(client &cli, const request &req) : Job(cli, req) {}
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

class Unknown_job : public Job
{
public:
    Unknown_job(client &cli, const request &req) : Job(cli, req) {}
    void work()
    {
        cli.send("Unknown command\n");
    }
};

class JobFactory
{
public:
    static std::unique_ptr<Job> createJob(client &cli)
    {
        size_t read_out;
        request req = RequestParser::parse(cli.readln(&read_out));
        if (req.cmd[0] == "CPU")
        {
            return std::make_unique<CPU_bound_job>(cli, req);
        }
        else if (req.cmd[0] == "IO")
        {
            return std::make_unique<IO_bound_job>(cli, req);
        }
        else
        {
            return std::make_unique<Unknown_job>(cli, req);
        }
    }
};

#endif