#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int sockfd;
    char buffer[1024] = {0};

    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // Receive message from server
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // Send a message to the server
    char message[] = "Hello from Client!";
    send(sockfd, message, strlen(message), 0);

    // Close the connection
    close(sockfd);

    return 0;
}
