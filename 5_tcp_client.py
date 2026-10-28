import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8080))
    print("Connected to the server. Type 'exit' to quit.")

    while True:
        msg = input("Client: ")
        client_socket.send(msg.encode('utf-8'))
        if msg.lower() == 'exit':
            break
            
        data = client_socket.recv(1024).decode('utf-8')
        if not data or data.lower() == 'exit':
            print("Server disconnected.")
            break
        print(f"Server: {data}")

    client_socket.close()

if __name__ == '__main__':
    start_client()