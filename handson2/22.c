// Name : 22.c
// Author : Shivam Jaiswal
// Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select 
//system call with FIFO.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

int main(){
	fd_set rfds;//A set of file descriptors to be monitored by select.
	struct timeval tv;
	tv.tv_sec=5;
	tv.tv_usec=0;
	int fd=open("myfifo",O_RDONLY);
	char buff[100];
	FD_ZERO(&rfds);//Clears the file descriptor set rfds.

	FD_SET(fd,&rfds);
	if(select(fd+1,&rfds,NULL,NULL,&tv)==-1){
		printf("No data is available for reading\n");
	}
	else if(select(fd+1,&rfds,NULL,NULL,&tv)==0){
		printf("Timeout\n");
	}
	else{
		printf("Data is available now\n");
		read(fd,buff,sizeof(buff));
		printf("data from FIFO: %s\n",buff);
	}
	close(fd);
}

