/*
 *Name:4.c
 *Author:Shivam Jaiswal
 *Description:. Write a program to open an existing file with read write mode. Try O_EXCL flag also
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
	char* file="exm.txt";

	int fd=open(file,O_RDWR);

	if(fd==-1){
		perror("Error while opening the file");
		return -1;
	}

	printf("File %s is opened with RDWD mode",file);

	int fd_excl=open(file ,O_CREAT |O_EXCL | O_RDWR, 0644);

	if(fd_excl==-1){
		perror("File already opened");
		close(fd);
	}
	else{
		printf("File opened with O_EXCL");
		close(fd_excl);
		close(fd);
	}
	return 0;
}

