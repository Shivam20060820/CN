import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 8080))
    server_socket.listen(1)
    print("Server is listening on port 8080...")

    conn, addr = server_socket.accept()
    print(f"Connected to {addr}")

    while True:
        data = conn.recv(1024).decode('utf-8')
        if not data or data.lower() == 'exit':
            print("Client disconnected.")
            break
        print(f"Client: {data}")
        
        reply = input("Server: ")
        conn.send(reply.encode('utf-8'))
        if reply.lower() == 'exit':
            break

    conn.close()
    server_socket.close()

if __name__ == '__main__':
    start_server()