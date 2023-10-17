// Name : 17_b.c
// Author : Shivam Jaiswal
// Description :  Write a program to execute ls -l | wc.
 //b. use dup2
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int fd[2];
	pipe(fd);
	
	if(fork()==0){
		close(1);
		close(fd[0]);//close read end
		dup2(fd[1],STDOUT_FILENO);//redirect stdout to pipe write end
		close(fd[1]);//close pipe write end
		execlp("ls","ls","-l",NULL);

	}
	else{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);//redirect stdin to pipe read end
		close(fd[0]);//close pipe read end
		execlp("wc","wc",NULL);
	}
	return 0;

}
