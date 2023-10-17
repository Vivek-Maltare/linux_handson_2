/*
============================================================================
Name : 33a.c
Author : Vivek Maltare
Description : Write a program to communicate between two machines using socket.
Date:7th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    addr_size = sizeof(new_addr);
    new_socket = accept(server_fd, (struct sockaddr*)&new_addr, &addr_size);

    // Receive data from the client
    while (1) {
        int bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Connection closed by client.\n");
            break;
        }

        printf("Received: %s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
