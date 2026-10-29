import socket

SERVER_IP = "127.0.0.1"
PORT = 5000

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = input("Enter message to send: ")
client_socket.sendto(message.encode(), (SERVER_IP, PORT))

reply, _ = client_socket.recvfrom(1024)
print("Server reply:", reply.decode())

client_socket.close()