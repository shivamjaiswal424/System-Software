//Name:24.c
//Author:Shivam Jaiswal
//Description:Write a program to create an orphan process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	pid_t child_pid=fork();

	if(child_pid==-1){
		perror("Fork has failed");
		return -1;
	}
	if( child_pid==0){
		printf("Child process (PID %d) is here \n",getpid());
		sleep(3);
		printf("Child process (PID %d) is exiting \n",getpid());
	}
	else{
		printf("Parent process (PID %d) is exiting \n",getpid());
	}
	return 0;
}

