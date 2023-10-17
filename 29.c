/*
============================================================================
Name : 26.c
Author : Vivek Maltare
Description : Write a program to remove the message queue.
Date:5th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a structure for the message
struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Sender Process
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello from sender!");

    // Send a message
    if (msgsnd(msgid, &msg, sizeof(struct message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", msg.msg_text);

    // Receiver Process
    if (msgrcv(msgid, &msg, sizeof(struct message), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Message received: %s\n", msg.msg_text);

    // Remove the message queue,we pass null because no additional information is needed to remove a message queue  
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
