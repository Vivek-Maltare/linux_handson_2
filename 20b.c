/*
============================================================================
Name : 20b.c
Author : Vivek Maltare
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date:25th Sep,2023.
============================================================================
*/

//reader
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
    int fd = open("20fifo", O_RDONLY);
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    printf("Reader process received: %.*s\n", (int)bytesRead, buffer);
    close(fd);
    unlink("20fifo");
    return 0;
}

