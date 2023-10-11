/*
 *Name:6.c
 *Author:Shivam Jaiswal
 *Description:Write a program to take input from STDIN and display on STDOUT.Use only read write system call.
 *
 *
 * */


#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	
	char buffer[1024]; //char array "buffer" of size 1024.This is used to  store the input we read from STDIN.
	ssize_t bytesRead;// declared a variable of type ssize_t.This variable will store the number of bytes read from STDIN.


	bytesRead=read(STDIN_FILENO,buffer,sizeof(buffer));

	write(STDOUT_FILENO,buffer,bytesRead);

	return 0;

}
