/*
============================================================================
Name : 16.c
Author : Vivek Maltare
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date:18th Sep,2023.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_parent_to_child[2]; // Pipe for communication from parent to child
    int fd_child_to_parent[2]; // Pipe for communication from child to parent

    if (pipe(fd_parent_to_child) == -1 || pipe(fd_child_to_parent) == -1) {
        perror("Pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) { // Child Process
        close(fd_parent_to_child[1]); // Close write end of parent to child pipe
        close(fd_child_to_parent[0]); // Close read end of child to parent pipe

        char message_to_child[100];
        read(fd_parent_to_child[0], message_to_child, sizeof(message_to_child));
        printf("Child received: %s\n", message_to_child);

        char message_to_parent[] = "Hello from child!";
        write(fd_child_to_parent[1], message_to_parent, strlen(message_to_parent) + 1);//+1 done to include the null terminator

        close(fd_parent_to_child[0]);
        close(fd_child_to_parent[1]);
    } else { // Parent Process
        close(fd_parent_to_child[0]); // Close read end of parent to child pipe
        close(fd_child_to_parent[1]); // Close write end of child to parent pipe

        char message_to_parent[] = "Hello from parent!";
        write(fd_parent_to_child[1], message_to_parent, strlen(message_to_parent) + 1);

        char message_to_child[100];
        read(fd_child_to_parent[0], message_to_child, sizeof(message_to_child));
        printf("Parent received: %s\n", message_to_child);

        close(fd_parent_to_child[1]);
        close(fd_child_to_parent[0]);
    }

    return 0;
}
