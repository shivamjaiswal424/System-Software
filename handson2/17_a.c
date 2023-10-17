// Name : 17_a.c
// Author : Shivam Jaiswal
// Description :  Write a program to execute ls -l | wc.
 //a. use dup
 

#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd[2];
	pipe(fd);

	if(fork()==0){
		close(1);//closes the standard output (stdout) in the child process, 
				//effectively disconnecting it from the terminal.
		close(fd[0]);
		dup(fd[1]);//duplicates the file descriptor for the write end of the pipe and associates it with stdout, 
					//effectively redirecting the output of the ls command to the pipe.
		execlp("ls","ls","-l",NULL);
	}
	else{
		close(0);//closes the standard input (stdin) in the parent process, 
				//disconnecting it from the terminal.
		close(fd[1]);
		dup(fd[0]);//duplicates the file descriptor for the read end of the pipe and associates it with stdin,
				// effectively redirecting the input of the wc command from the pipe.
		execlp("wc","wc",NULL);
	}

}
