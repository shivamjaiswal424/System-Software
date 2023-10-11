/*
 *Name:3.c
 *Author:Shivam Jaiswal
 *Description: Write a program to create a file and print the file descriptor value. Use creat ( ) system call
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
	if(argc!=2){
	perror("Wrong inputs\n");
	return -1;
	}
	int fd=creat(argv[1] , 0777);

	if(fd==-1){
		perror("Error Creating the file\n");
		close(fd);
		return -1;
	}
	printf("File named %s created successfully\n",argv[1]);

	if(close(fd)==-1){
		perror("Error closing file");
		return -1;
	}

	return 0;
}

