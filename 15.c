/*
============================================================================
Name : 15.c
Author : Vivek Maltare
Description : Write a simple program to send some data from parent to the child process.
Date:18th Sep,2023.
============================================================================
*/
# include <stdio.h>
# include <unistd.h>
# include <string.h>
int main()
{
	int fd[2];
	char *message = "writing from parent process";
	// creating a pipe
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("ERROR:");
	}
    // creating a child process
    pid_t pid = fork();
    if(pid == -1)
    {
    	perror("ERROR:");
    }
    // if child is executing
    if(pid == 0)
    {
      //close write end because child only reads
      close(fd[1]);
      char buff[100];
      // read
      read(fd[0],buff,sizeof(buff));
      printf("Received message from parent: %s\n", buff);
      close(fd[0]);
    }
    else
    {
    	// if parent close write end because parent only writes
    	close(fd[0]);
    	write(fd[1],message,strlen(message));
      close(fd[1]);
    }
}