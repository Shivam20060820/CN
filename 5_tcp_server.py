import socket

host = "127.0.0.1"
port = 5000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
server_socket.bind((host,port))
server_socket.listen(1)

conn, addr = server_socket.accept()
data = conn.recv(1024)
print(data.decode())

conn.close()
server_socket.close()