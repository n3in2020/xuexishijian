#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <iostream>
#include <limits>

class CommandManager
{
public:
    bool DoREPL();
    bool RunCommand(const std::string &command, std::ostream &cout);
};

bool CommandManager::DoREPL()
{
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

bool CommandManager::RunCommand(const std::string &command, std::ostream &cout)
{
    if (command == "quit")
    {
        return false;
    }
    return true;
}
#endif