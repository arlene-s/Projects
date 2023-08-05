import sys

# Import socket module
import socket

if len(sys.argv) == 3:
	port = int(sys.argv[2])
	host = sys.argv[1]

	s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

	# connect to server on local computer
	s.connect((host,port))

	# message you send to server
	while True:

		message = input('\nInput Sentence: ')

		if message == 'QUIT':
			break

		# message sent to server
		s.send(message.encode('ascii'))

		# message received from server
		data = s.recv(1024)

		# print the received message
		# here it would be uppercase of sent message
		print('Received from the server :',str(data.decode('ascii')))

	# close the connection
	s.close()
else:
	print(f'Usage: python3 {sys.argv[0]} ip_address port_number')
