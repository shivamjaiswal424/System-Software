/*Name:8.c
 *Author:Shivam Jaiswal
 *Description:Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
 *
 *
 *
 * */




#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("You did something wrong.Try again\n");
		return -1;

	}
	int fd_read=open(argv[1],O_RDONLY);
	if(fd_read==-1){
		printf("File not found.Try again\n");
		return 1;

	}
	while(1){
		char buff;
		int read_byte=read(fd_read, &buff,1);

		if(read_byte==0)
			break;
		write(STDOUT_FILENO,&buff,read_byte);
	}
	close(fd_read);
	return 0;
}


