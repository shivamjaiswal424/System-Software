/*
 * Name 11.c
 * Author: Shivam Jaiswal
 * Description:
 Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
 a. use dup
 b. use dup2
 c. use fcntl

 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print_file(char* filename){
	printf("Contents of file %s displayed below : \n",filename);

	char buffer[1024];
	int fd =open(filename, O_RDONLY);

	if(fd==-1){
		perror("Error opening file");
		exit(1);
	}

	ssize_t print;
	while((print=read(fd,buffer,sizeof(buffer)))>0){
		write(STDOUT_FILENO,buffer,print);
	}
	close(fd);
	printf("\n");

}

int main(){
	char* path="new_file.txt";
	int file = open(path, O_RDWR|O_CREAT, 0666);
	
	if(file == -1){
		perror("Error opening the file");
		return 1;
	}
	
	char data[] = "Hey, this is Shivam\n";

	int dup_fd = dup(file);
	if(dup_fd == -1){
		perror("File descriptor not duplicated properly");
		close(file);
		return 1;
	}
	
	char data2[] ="Hey, this is Shivam again \n";

	write(file,data,strlen(data));
	write(dup_fd,data2,strlen(data2));
	
	int dup2_fd=dup2(file,99);
	if(dup2_fd==-1){
		perror("Error while duplicating dup2");
		close(file);
		close(dup_fd);
		close(dup2_fd);
		return 1;
	}

	char data3[]="Hey this is Shivam using dup2\n";

	write(dup2_fd,data3,strlen(data3));

	int fcntl_dup_fd=fcntl(file,F_DUPFD);
	if(fcntl_dup_fd==-1){
		perror("Error using fcntl");
		close(file);
		close(dup_fd);
		close(dup2_fd);
		close(fcntl_dup_fd);
		return 1;
	}
	char data4[]="Shivam is using fcntl\n";
	write(fcntl_dup_fd,data4,strlen(data4));

	close(file);
	close(dup_fd);
	close(dup2_fd);
	close(fcntl_dup_fd);

	print_file(path);

	return 0;




}

