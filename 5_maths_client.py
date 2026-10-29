import socket

SERVER_IP = "127.0.0.1"   # replace with the server computer's IP
PORT = 5000

num1 = input("Enter first number: ")
op = input("Enter operator (+, -, *, /): ")
num2 = input("Enter second number: ")

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((SERVER_IP, PORT))

client_socket.sendall(f"{num1} {op} {num2}".encode())

reply = client_socket.recv(1024).decode()
print(reply)

client_socket.close()