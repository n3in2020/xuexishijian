#include "Server.hpp"

void usage(const char * pName)
{
    printf("%s [port default=50000]\n", pName);
    exit(1);
}

int main(int argc, char *argv[])
{
    short port = 50000;
    if(argc>2)
    {
        usage(argv[0]);
    }    
    else if(argc==2)
    {
        port = atoi(argv[1]);
    }
    Server server(port);
    server.setupListener();
    server.run();
}