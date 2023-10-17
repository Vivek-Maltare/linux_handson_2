/*
============================================================================
Name : 33b.c
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
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    while (1) {
        printf("Enter a message (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        send(client_socket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Connection closed by client.\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
    }

    close(client_socket);

    return 0;
}
