#!bin/bash
for ((i = 0; i < $1; i++));
do
    ./client 127.0.0.1 &
done
wait