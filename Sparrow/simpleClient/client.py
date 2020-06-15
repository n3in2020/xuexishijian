import socket
import sys
s = socket.socket()
host = socket.gethostname()
port = 50000
s.connect((host, port))
data = "CPU\t11\n"
s.send(data.encode('utf-8'))
print(s.recv(1024))
s.close()