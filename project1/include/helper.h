#ifndef HELPER_H
#define HELPER_H
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> readFile(const std::string &filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    if (ifs.is_open() == false)
    {
        printf("No such file %s!\n", filename.c_str());
        exit(1);
    }
    char c;
    char buffer[1024];
    int index = 0;
    std::vector<std::string> words;
    while ((c = ifs.get()) != EOF)
    {
        if (iswspace(c))
        {
            if (index > 0)
            {
                buffer[index] = '\0';
                index = 0;
                words.push_back(buffer);
            }
        }
        else if (isalpha(c) || isdigit(c))
        {
            buffer[index++] = c;
        }
        else{
            printf("Unsupported character!\n");
            exit(1);
        }
    }
    return words;
}
bool isNum(const std::string &str)
{
    bool isNum = false;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
            return false;
    }
    return true;
}

void errExit(const char *msg)
{
    printf("[ERROR] %s\n");
    exit(1);
}
#endif