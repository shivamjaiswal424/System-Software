//Name:25.c
//Author:Shivam Jaiswal
//Description:. Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t children[3];

	for(int i=0;i<3;i++){
		children[i]=fork();

		if(children[i]==-1){
			perror("Fork failed");
			return -1;
		}
		if(children[i]==0){
			printf("Child %d with PID (%d) is executing. \n",i+1,getpid());
			sleep(2);
			//printf("Child %d with PID (%d) is exiting. \n",i+1,getpid());
			exit(0);
		}
	}
	int status;
	pid_t waited_child=waitpid(children[0],&status,0);

	if(waited_child==-1){
		perror("Error while waiting");
		exit(EXIT_FAILURE);
	}
	if(WIFEXITED(status)){
		printf("Child %d with PID %d has exited with status %d.\n",1,waited_child,WEXITSTATUS(status));
	}
	return 0;

}

