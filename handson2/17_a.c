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
		close(1);
		close(fd[0]);
		dup(fd[1]);
		execlp("ls","ls","-l",NULL);
	}
	else{
		close(0);
		close(fd[1]);
		dup(fd[0]);
		execlp("wc","wc",NULL);
	}

}
