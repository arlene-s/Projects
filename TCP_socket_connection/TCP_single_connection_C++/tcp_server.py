from socket import *

serverPort=12000
address = ('localhost', serverPort)
# address = ('127.0.0.1', serverPort)
max_size = 1000

# create server socket with TCP --> SOCK_STREAM
server = socket(AF_INET, SOCK_STREAM)

# assign server port number to server socket
server.bind(address)

# wait and listen to client knock on door
# param 5 --> max number of queued connections
server.listen(5)

# seve prints message to screen
print('The server is ready to receive.')

# accept() creates a new socket in the server --> client
# different from server socket "welcoming door", "listening",
# establish connection to any client requesting
# addr --> address of client
# TCP connection establised between client socket and server's socket
client, addr = server.accept()

# recieves data from client
data = client.recv(max_size).decode()


# change to uppercase
while data != 'QUIT':
    capitalizedData = data.upper()

# print data and capitalizedData
    print('[',data,'] to [',capitalizedData,']')
# server sends message to client
# b --> .encode()
    client.sendall(capitalizedData.encode())

    data = client.recv(max_size).decode()

#data = client.recv(max_size).decode()
# close client socket to prevent memory leaks
client.close()

#close server socket
server.close()

