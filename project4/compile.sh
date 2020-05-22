#!bin/bash
clang ./src/client.c -I include -o ./bin/client 
clang ./src/select-server.c -I include -o ./bin/select-server 
clang ./src/poll-server.c -I include -o ./bin/poll-server
clang ./src/epoll-server.c -I include -o ./bin/epoll-server 