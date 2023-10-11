//Name:21.c
//Author:Shivam Jaiswal
//Description:Write a program, call fork and print the parent and child process id.


#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t child_pid=fork();

	if(child_pid==-1){
		perror("Fork not happened");
		return -1;
	}

	if(child_pid==0){
		printf("Child process PID is %d\n",getpid());
	}
	else{
		printf("Parent Process PID is %d , Child PID is %d\n",getpid(),child_pid);
	}
	return 0;
}
