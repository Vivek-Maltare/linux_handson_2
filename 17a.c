/*
============================================================================
Name : 17a.c
Author : Vivek Maltare
Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
Date:21th Sep,2023.
============================================================================
*/
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
int main(char* args,char* argv[])
{
	int pipe_fd[2];
	pid_t pid;
	if(pipe(pipe_fd)==-1)
	{
		perror("ERROR:");
	}
	else if((pid=fork())==-1)
	{
		perror("ERROR:");
	}
    // parent process
	if(pid == 0)
	{
	  // redirecting our standard output to write end of file 
      dup2(pipe_fd[1],STDOUT_FILENO);
      // closing read end 
      close(pipe_fd[0]);
      // executing ls -l
      execlp("ls","ls","-l",NULL);
	}
    // child process
	else
	{
	  int output;
    if((output=open("pipe.txt",O_RDWR|O_CREAT,0644))==-1)
    {
      perror("ERROR:");
    } 
    else
    {
      // redirecting standard input to read end i.e.take input from read end of file 
      dup2(pipe_fd[0],STDIN_FILENO);
      // close write end
      close(pipe_fd[1]);
      // redirecting output from write end to file
      dup2(output,STDOUT_FILENO);
      // executing wc
      execlp("wc","wc",NULL);
    }
	}
  return 0;
}