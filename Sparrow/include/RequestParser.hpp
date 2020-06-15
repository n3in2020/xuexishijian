#ifndef REQUESTPARSER_HPP
#define REQUESTPARSER_HPP
#include <vector>
#include <string>
struct request
{
    std::vector<std::string> cmd;
};

class RequestParser
{
public:
    static struct request parse(const std::string &reqstr);
};

struct request RequestParser::parse( const std::string &reqstr)
{
    struct request req;
    char word[1024];
    int index = 0;
    for (int i = 0; i < reqstr.size(); ++i)
    {
        char c = reqstr[i];
        if (c == '\t' || c == '\n')
        {
            word[index] = '\0';
            req.cmd.push_back(word);
            index = 0;
        }
        else
        {
            word[index++] = c;
        }
    }
    if(index)
    {
        word[index] = '\0';
        req.cmd.push_back(word);
    }
    return req;
}
#endif