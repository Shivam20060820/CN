import socket

# 1. START
# 2. Create UDP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('127.0.0.1', 8080)

# 3. Input message from user
msg = input("Enter an uppercase string: ")

# 4. Send message to server IP address and port number
client_socket.sendto(msg.encode('utf-8'), server_address)

# 5. Receive reply from server
data, server = client_socket.recvfrom(1024)

# 6. Display server reply
print(f"Server reply (Lowercase): {data.decode('utf-8')}")

# 7. Close client socket
client_socket.close()
# 8. STOP