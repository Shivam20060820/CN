import socket

# 1. START
# 2. Create UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 3. Bind socket to IP address and port number
server_socket.bind(('127.0.0.1', 8080))
print("Server is waiting for client message...")

# 4 & 5. Wait to receive message / Receive message and client address
data, addr = server_socket.recvfrom(1024)
received_msg = data.decode('utf-8')

# 6. Display received message
print(f"Received from client: {received_msg}")

# Convert UpperCase to LowerCase
reply_msg = received_msg.lower()

# 7. Send reply to client address
server_socket.sendto(reply_msg.encode('utf-8'), addr)

# 8. Close server socket
server_socket.close()
# 9. STOP

#for reversal:
# Replace this:
# reply_msg = received_msg.lower()

# With this:
# reply_msg = received_msg[::-1]