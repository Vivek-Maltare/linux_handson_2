/*
============================================================================
Name : 21a.c
Author : Vivek Maltare
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date:25th Sep,2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
int main()
{
    int myfifo = mknod("myfifo_21" , S_IFIFO | 0666,0);
    if(myfifo == -1)
    {
        perror("Error in  creating FIFO file");
        return -1;
    }

    int fd  = open("myfifo_21" , O_RDWR);       
    if(fd == -1)
    {
        perror("Error");
        return -1;
    }
    
    char buff[100];
    printf("please enter message that you want to send : \n");
    scanf("%[^\n]" , buff);

    int send = write(fd , &buff , sizeof(buff));
    if(send == -1)
    {
        perror("Error in write operation");
        return -1;
    }

    int receive = read(fd, &buff, sizeof(buff));
    if(receive ==-1)
    {
        perror("Error in read operation");
        return -1;
    }
    printf("Message received from other end is : %s \n",buff);
    
    

}

