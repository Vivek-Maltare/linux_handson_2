/*
============================================================================
Name : 22a.c
Author : Vivek Maltare
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date:30th Sep,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

//reader process
int main() {

    int myfifo = mknod("myfifo_22" , S_IFIFO | 0666,0);
    if(myfifo == -1)
    {
        perror("Error in  creating FIFO file");
        return -1;
    }

    int fd = open("myfifo_22", O_RDONLY);

    if (fd == -1) 
    {
        perror("Error in opening fifo");
        exit(EXIT_FAILURE);
    }

    // Set up the fd_set for select
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
   
    // Set the timeout for select (10 seconds)
    struct timeval timeout;
    timeout.tv_sec = 15;
    timeout.tv_usec = 0;

    // Wait for data to be written into the FIFO or timeout
    int p = select(fd+1, &readSet, NULL, NULL, &timeout);

    if (p == -1) 
    {
        perror("error");
        exit(EXIT_FAILURE);
    }
    else if (p) 
    {
        // Data is available to read from the FIFO
        char buffer[100];
        int bytesRead = read(fd, buffer, sizeof(buffer));

        if (bytesRead == -1)
        {
            perror("error in read");
        } 
        else 
        {
            printf("Data received from FIFO: %s\n", buffer);
        }
        
    }
    else
    {
        printf("Timeout: No data written to the FIFO within 10 seconds.\n");
    }
    close(fd);
    // unlink(myfifo);

    return 0;
}
