/*
============================================================================
Name : 30b.c
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

    // Generate the same unique key
    key = ftok("/tmp", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the existing shared memory segment
    shmid = shmget(key, 100, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment as read-only
    shared_memory = (char*)shmat(shmid, NULL, SHM_RDONLY);
    if (shared_memory == (char*)-1) {
        perror("shmat (O_RDONLY)");
        exit(EXIT_FAILURE);
    }

    // Try to write to shared memory (will fail if attached as O_RDONLY) gives segmentation fault
    strncpy(shared_memory, "This will fail.", 15);

    // Detach from shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
