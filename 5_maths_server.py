import socket

HOST = "127.0.0.1"   # use "0.0.0.0" to accept connections from other computers
PORT = 5000

def calculate(num1, op, num2):
    if op == "+":
        return num1 + num2
    elif op in ("-", "−"):
        return num1 - num2
    elif op in ("*", "×", "x"):
        return num1 * num2
    elif op in ("/", "÷"):
        if num2 == 0:
            raise ZeroDivisionError
        return num1 / num2
    else:
        raise ValueError("Invalid operator")

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST, PORT))
server_socket.listen(5)
print(f"Calculator server listening on {HOST}:{PORT} ...")

while True:
    conn, addr = server_socket.accept()
    print(f"Connected by {addr}")

    data = conn.recv(1024).decode()
    print("Request received:", data)

    try:
        num1, op, num2 = data.split()
        result = calculate(float(num1), op, float(num2))
        reply = f"Result: {num1} {op} {num2} = {result}"
    except ZeroDivisionError:
        reply = "Error: Division by zero is not allowed"
    except ValueError as e:
        reply = f"Error: {e}" if str(e) == "Invalid operator" else "Error: Invalid input"

    conn.sendall(reply.encode())
    conn.close()