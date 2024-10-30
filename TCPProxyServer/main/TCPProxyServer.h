
#ifndef TCPPROXYSERVER_H
#define TCPPROXYSERVER_H

#include <winsock2.h> // Include Windows Sockets 2 header for socket programming
#include <ws2tcpip.h> // Include header for TCP/IP protocol family
#include <string> // Include string library for string manipulation
#include <thread> // Include thread library for multithreading
#include <vector> // Include vector library for dynamic arrays
#include <iostream> // Include iostream for input/output operations
#include "Logger.h" // Include custom Logger class for logging functionality
#include "ThreadPool.h" // Include custom ThreadPool class for managing threads

// TCPProxyServer class definition
class TCPProxyServer {
public:
    // Constructor: Initializes the server with a specified port and number of threads
    TCPProxyServer(int port, int threadCount);

    // Destructor: Cleans up resources used by the server
    ~TCPProxyServer();

    // Starts the server and begins accepting client connections
    void start();

private:
    // Handles communication with a connected client
    void handleClient(SOCKET clientSocket);

    // Initializes Winsock for network communication
    void initializeWinsock();

    // Creates a TCP socket for the server
    void createServerSocket();

    // Binds the socket to the specified address and port, then listens for incoming connections
    void bindAndListen();

    SOCKET serverSocket; // Socket for the server
    sockaddr_in serverAddr; // Structure to hold server address information
    int port; // Port number for the server
    int threadCount; // Number of threads in the thread pool
    ThreadPool threads; // ThreadPool instance for managing client handling threads
    Logger logger; // Logger instance for logging server activities
};

#endif // TCPPROXYSERVER_H
