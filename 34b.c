/*
============================================================================
Name : 34b.c
Author : Vivek Maltare
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
Date:7th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void* handle_client(void* client_socket_ptr) {
    int client_socket = *((int*)client_socket_ptr);
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }
        printf("Received: %s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    pthread_t thread_id;

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

    while (1) {
        // Accept incoming connection
        client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle the client
        pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket);

        // Detach the thread
        pthread_detach(thread_id);
    }

    return 0;
}
