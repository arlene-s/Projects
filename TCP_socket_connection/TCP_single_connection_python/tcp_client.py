from socket import *
from datetime import datetime

serverPort = 12000
address = ('localhost', serverPort)
max_size = 1000

# create client socket
# SOCK_STREAM is TCP
client = socket(AF_INET, SOCK_STREAM)

# initiate TCP connection between client and server
# set up connection with server
client.connect(address)

# client side doesnt need binding, doesnt care what NIC taking care of
# server has multiple NIC inside

# message from client
message = input('Input lowercase sentence: ')
client.sendall(message.encode())

while message != 'QUIT':
# sends message through client socket and into TCP connection
    # client.sendall(message.encode())

# client waits to receive data from server with max buffer size 1000 = max_size
# executes when server responds with message to client
    data = client.recv(max_size).decode()

# print data from server
    print('Data: ', data)

    message = input('Input lowercase sentence: ')
    client.sendall(message.encode())

# close client socket
client.close()
