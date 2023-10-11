//Name 27.c
//Author:Shivam Jaiswal
//Description:Write a program to execute ls -Rl by the following system calls
// a. execl
// b. execlp
// c. execle
// d. execv
// e. execvp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Using execl:\n");
	pid_t child=fork();

	if(child==0){
		execl("/bin/ls","ls","-Rl",NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	}
	wait(NULL);//parent will wait

	printf("using execlp\n");
	child=fork();
	if(child==0){
		execlp("ls","ls","-Rl",NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}

	wait(NULL);

	printf("using execle\n");

	char *envp[] = {NULL}; //No environment variables
	child=fork();
	if(child==0){
		execle("/bin/ls","ls","-Rl",NULL , envp);
		perror("execle");
		exit(EXIT_FAILURE);
	}

	wait(NULL);

	printf("using execv\n");
	char *args[]={"ls","-Rl",NULL};
	child=fork();
	if(child==0){
		execv("/bin/ls",args);
		perror("execv");
		exit(EXIT_FAILURE);
	}
	wait(NULL);

	printf("Using execvp\n");
	child=fork();
	if(child==0){
		execvp("ls",args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	return 0;
}
