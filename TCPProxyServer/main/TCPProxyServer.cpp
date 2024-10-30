
#include "TCPProxyServer.h"
#include <iostream>
#include <thread>
#include <mutex>

// Constructor: Initializes the server with a specified port and number of threads
TCPProxyServer::TCPProxyServer(int port, int threadCount)
    : port(port), threadCount(threadCount), serverSocket(INVALID_SOCKET), threads(threadCount), logger("server_log.txt") {
    initializeWinsock(); // Initialize Winsock
    createServerSocket(); // Create a server socket
    bindAndListen(); // Bind the socket and start listening for connections
}

// Destructor: Cleans up the server socket and Winsock
TCPProxyServer::~TCPProxyServer() {
    closesocket(serverSocket); // Close the server socket
    WSACleanup(); // Cleanup Winsock
}

// Initialize Winsock for network communication
void TCPProxyServer::initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(EXIT_FAILURE); // Exit if initialization fails
    }
}

// Create a TCP socket for the server
void TCPProxyServer::createServerSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup(); // Cleanup Winsock
        exit(EXIT_FAILURE); // Exit if socket creation fails
    }
}

// Bind the socket and start listening for incoming connections
void TCPProxyServer::bindAndListen() {
    serverAddr.sin_family = AF_INET; // Set address family
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any address
    serverAddr.sin_port = htons(port); // Set the port number

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(serverSocket); // Close socket on failure
        WSACleanup(); // Cleanup Winsock
        exit(EXIT_FAILURE); // Exit if bind fails
    }

    // Start listening for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(serverSocket); // Close socket on failure
        WSACleanup(); // Cleanup Winsock
        exit(EXIT_FAILURE); // Exit if listen fails
    }

    std::cout << "Server is listening on port " << port << "..." << std::endl; // Notify server is ready
}

// Main loop to accept incoming client connections
void TCPProxyServer::start() {
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL); // Accept a new client connection
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed." << std::endl; // Handle accept failure
            continue; // Continue accepting new connections
        }

        // Enqueue the client handling task to the thread pool
        threads.enqueue([this, clientSocket] {
            handleClient(clientSocket); // Handle the connected client
            });
    }
}

// Mutex for thread-safe access to the active thread count
std::mutex mtx;
int activeThreads = 0; // Count of currently active threads

// Function to handle communication with the connected client
void TCPProxyServer::handleClient(SOCKET clientSocket) {
    char buffer[1024]; // Buffer for incoming data
    int bytesReceived;

    // Get the ID of the current thread
    std::thread::id this_id = std::this_thread::get_id();
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock for thread-safe access
        activeThreads++; // Increment active thread count

        // Format log message and log it
        std::string logMessage = "Thread ID: " + std::to_string(reinterpret_cast<uintptr_t>(&this_id)) +
            " is handling client. Active threads: " + std::to_string(activeThreads);
        logger.log(logMessage);
        std::cout << logMessage << std::endl; // Output log message to console
    }

    // Read data from the client
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // Null-terminate the buffer

        // Log the received request
        std::string requestLog = "Received request: " + std::string(buffer);
        logger.log(requestLog);
        std::cout << requestLog << std::endl; // Output received request to console

        // Basic HTTP response
        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, client!";
        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0); // Send response to client

        // Log the outgoing response
        std::string responseLog = "Sent response: " + httpResponse;
        logger.log(responseLog);
        std::cout << responseLog << std::endl; // Output sent response to console
    }
    else {
        std::cerr << "Recv failed." << std::endl; // Handle receive failure
    }

    closesocket(clientSocket); // Close the client socket

    {
        std::lock_guard<std::mutex> lock(mtx); // Lock for thread-safe access
        activeThreads--; // Decrement active thread count

        // Log thread completion info
        std::string completionLog = "Thread ID: " + std::to_string(reinterpret_cast<uintptr_t>(&this_id)) +
            " finished handling client. Active threads: " + std::to_string(activeThreads);
        logger.log(completionLog);
        std::cout << completionLog << std::endl; // Output completion info to console
    }
}

