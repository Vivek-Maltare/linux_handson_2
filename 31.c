/*
============================================================================
Name : 31.c
Author : Vivek Maltare
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date:5th oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int main() {
    sem_t *sem;

    // Create a binary semaphore with initial value 1
    sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process trying to lock the semaphore...\n");

        // Attempt to lock the semaphore
        if (sem_wait(sem) == 0) {
            printf("Child process locked the semaphore.\n");

            // perform task
            sleep(2);

            // Release the semaphore
            sem_post(sem);
            printf("Child process released the semaphore.\n");
        } else {
            perror("sem_wait");
        }

        // Close and unlink the semaphore
        sem_close(sem);
        sem_unlink("/my_semaphore");

    } else {
        // Parent process
        printf("Parent process trying to lock the semaphore...\n");

        // Attempt to lock the semaphore
        if (sem_wait(sem) == 0) {
            printf("Parent process locked the semaphore.\n");

            // perform task
            sleep(2);

            // Release the semaphore
            sem_post(sem);
            printf("Parent process released the semaphore.\n");
        } else {
            perror("sem_wait");
        }

        // Close and unlink the semaphore
        sem_close(sem);
        sem_unlink("/my_semaphore");
    }

    return 0;
}
