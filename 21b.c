/*
============================================================================
Name : 21b.c
Author : Vivek Maltare
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date:25th Sep,2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
    int fd  = open("myfifo_21" , O_RDWR);       
    if(fd == -1)
    {
        perror("Error in opening FIFO file");
    }
    
    char buff[100];

    int receive = read(fd, &buff, sizeof(buff));
    if(receive==-1)
    {
        perror("Error in read operation");
    }
    printf("Message received from other end is : %s \n",buff);
    
    
    printf("Enter the Message that you want send to other end : \n");
    scanf("%[^\n]" , buff);

    int send = write(fd , &buff , sizeof(buff));
    if(send == -1)
    {
        perror("Error in write operation"); 

    }
        return 0;
}