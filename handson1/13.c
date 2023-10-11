/*
 *Name: 13.c
 *Author:Shivam Jaiswal
Description:Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).	
 * */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>

int main(void)
{
	fd_set rfds; //file descriptor set for read-ready events
	struct timeval tv;
	int retval;

	/* Watch stdin (fd 0) to see when it has input. */

	FD_ZERO(&rfds); // make the set empty
	FD_SET(0, &rfds);//add file descriptor 0 to the set.
	
	printf("Waiting for input on stdin for 10 seconds\n");
	/* Wait up to 10 seconds. */
	char buff[100];
	int r=read(STDIN_FILENO, buff,sizeof(buff));	

        tv.tv_sec = 10;
        tv.tv_usec = 0;//this is for microseconds
	

	retval = select(1, &rfds, NULL, NULL, &tv);
	//the first argument "1" is file descriptor to check plus one.
	//third & fourth argument is the set of file descriptors to monitor for write and exception events which we don't require hence NULL.
	/* Don't rely on the value of tv now! */

	if (retval == -1)
		perror("Error in select()");
	else if (retval){
        	//printf("Data is available within 10 second.\n");
		write(STDOUT_FILENO, &buff,r);
		printf("Data is available within 10 second.\n");
	}
	/* FD_ISSET(0, &rfds) will be true. */
	else
        	printf("No data within 10 seconds.\n");

	exit(EXIT_SUCCESS);
}			
