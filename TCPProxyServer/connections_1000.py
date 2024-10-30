import socket
import threading

def connect_to_server(port):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(('127.0.0.1', port))
            s.sendall(b'GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n')
            response = s.recv(1024)
            print(f'Response: {response.decode()}')
    except Exception as e:
        print(f"Connection error: {e}")

def main():
    port = 8080
    threads = []
    
    # Create 1000 threads to connect to the server
    for _ in range(1000):
        thread = threading.Thread(target=connect_to_server, args=(port,))
        threads.append(thread)
        thread.start()
    
    # Wait for all threads to complete
    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()
