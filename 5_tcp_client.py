import socket

Host = "127.0.0.1"
Port = 5000

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((Host, Port))

message = input("Enter a message to send to the server: ")
client_socket.send(message.encode())

client_socket.close()