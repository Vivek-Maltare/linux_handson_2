/*
============================================================================
Name : 30a.c
Author : Vivek Maltare
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
Date:5th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key;
    int shmid;
    char *shared_memory;

    //Generate a unique key for the shared memory segment
    key = ftok("/tmp",'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment of 100 bytes
    shmid = shmget(key, 100, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment.NULL means let the system choose where to attach it.
    shared_memory = (char*)shmat(shmid,NULL,0);
    if (shared_memory == (char*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write to shared memory
    strcpy(shared_memory, "Hello, shared memory!");

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

//attaching to shared memory means including that shared memory to a process address space so that it can be accessed by that process 