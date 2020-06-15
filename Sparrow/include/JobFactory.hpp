#ifndef JOB_FACTORY_HPP
#define JOB_FACTORY_HPP
#include <memory>
#include "Client.hpp"
#include "RequestParser.hpp"
class Job
{
public:
    Job(client &cli_) : cli(cli_) {}
    virtual void work() = 0;

    client &cli;
};

class IO_bound_job : public Job
{
public:
    IO_bound_job(client &cli) : Job(cli) {}
    void work()
    {
        cli.send("IO_bound_job\n");
    }

private:
};

class CPU_bound_job : public Job
{
public:
    CPU_bound_job(client &cli) : Job(cli) {}
    void work()
    {
        cli.send("CPU_bound_job");
    }
};

class Unknown_job : public Job
{
public:
    Unknown_job(client &cli) : Job(cli) {}
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
            return std::make_unique<CPU_bound_job>(cli);
        }
        else if (req.cmd[0] == "IO")
        {
            return std::make_unique<CPU_bound_job>(cli);
        }
        else
        {
            return std::make_unique<Unknown_job>(cli);
        }
    }
};

#endif