/*
============================================================================
Name : 14.c
Author : Vivek Maltare
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date:18th Sep,2023.
============================================================================
*/
# include <stdio.h>
# include <unistd.h>
# include <string.h>
int main()
{
	char* message1 = "writing from parent  ";
	char* message2 = "writing from child   ";
	//creating pipe
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("ERROR:");
	}
	pid_t pid1 = fork();
	pid_t pid2 = fork();
	//child1
	if(pid1 == 0 && pid2!=0)
	{
      //close write end because child1 only reads
      close(fd[1]);
      char buff[100];
      // read
      read(fd[0],buff,sizeof(buff));
      printf("Received message from producer by child1: %s\n", buff);
      close(fd[0]);
	}
	// child2
	else if(pid2 == 0 && pid1!=0)
	{
      //close read end because child2 only writes
		  close(fd[0]);
    	write(fd[1],message2,strlen(message2));
      close(fd[1]);
	}
	else
	{
      // if parent close read end because parent only writes
    	close(fd[0]);
    	write(fd[1],message1,strlen(message1));
      close(fd[1]);
	}
}