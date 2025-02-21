#include <sys/types.h>   // Data types
#include <sys/socket.h>  // Sockets API
#include <netinet/in.h>  // Internet address structures
#include <arpa/inet.h>   // Functions for IP address conversions
#include <unistd.h>      // Close function
#include <string.h>      // String operations
#include <stdio.h>       // Input/Output functions
#include <stdlib.h>      // Memory management

int main() {
    int client_socket;
    char buffer[1024] = {0};
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    server_addr.sin_port = htons(8080);       // Port 8080

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    } 
    printf("Socket successfully bound to IP\n");

    // Listen for incoming connections
    if (listen(sockfd, 10) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port 8080...\nPress Crrl+C inorder to stop program \n");

    while (1) {
        // Accept a new client connection
        client_socket = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Client connection failed");
            continue; // Don't exit; continue accepting other connections
        }
        printf("Client connected\n");

        // Send a message to the client
        send(client_socket, "Hello, Client!", 14, 0);

        // Close the client socket after communication
        close(client_socket);
        
        recv(client_socket, buffer, sizeof(buffer), 0);
        if (buffer != 0){ // must be fixed
        printf("Received: %s\n", buffer);
        }
    }

    // Close the server socket (never reached in this case)
    close(sockfd);
    return 0;
}
