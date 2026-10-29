import socket

HOST = "127.0.0.1"
PORT = 5000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # SOCK_DGRAM = UDP
server_socket.bind((HOST, PORT))
print(f"UDP server listening on {HOST}:{PORT} ...")

data, addr = server_socket.recvfrom(1024)   # returns data AND sender's address
print(f"Message received from {addr}:", data.decode())

server_socket.sendto(b"Message received successfully", addr)  # reply to that address

server_socket.close()