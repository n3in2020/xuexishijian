#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <iostream>
#include <limits>
#include <Metrics.hpp>

class CommandManager
{
public:
    bool DoREPL();
    bool RunCommand(const std::string &command, std::ostream &cout);
};

bool CommandManager::DoREPL()
{
    static bool first_time = true;
    if (first_time)
    {
        first_time = false;
        return RunCommand("help", std::cout);
    }
    std::string command;
    while (command.empty())
    {
        std::cout << ">>>";
        std::getline(std::cin, command, '\n');
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl;
            continue;
        }
    }
    return RunCommand(command, std::cout);
}

bool CommandManager::RunCommand(const std::string &command, std::ostream &out)
{
    if (command == "quit")
    {
        return false;
    }
    else if (command == "help")
    {
        out << "HELP MENU" << std::endl;
        out << "help    - show help menu" << std::endl;
        out << "metrics - show metrics" << std::endl;
        out << "quit    - quit" << std::endl;
    }
    else if (command == "metrics")
    {
        Metrics::GetInstance()->Report(out);
    }
    return true;
}
#endif