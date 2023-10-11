/*Name:write_lock_16.c
Author:Shivam Jaiswal
 *Description:Write a program to perform mandatory locking.
 a. Implement write lock
 b. Implement read lock
 *
 * */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char* file="file_writelock.txt";
	int fd=open(file, O_RDWR|O_CREAT);

	if(fd==-1){
		perror("Error while openning the file");
		return EXIT_FAILURE;
	}
	struct flock lock;
	lock.l_type=F_WRLCK; // write lock
	lock.l_whence=SEEK_SET; // sets the reference point for the start of the lock to the beginning of the file
	lock.l_start=0; // sets the starting offset of the  lock to 0
	lock.l_len=0;//lock the entire file
		     
	if(fcntl(fd,F_SETLK,&lock)==-1){
		perror("Error on locking the file");
		close(fd);
		return EXIT_FAILURE;
	}

	printf("Write lock is acquired.Press Enter to release the lock...\n");
	getchar();

	lock.l_type=F_UNLCK;
	if(fcntl(fd,F_SETLK,&lock)==-1){
		perror("Error while unlocking the file");
		close(fd);
		return EXIT_FAILURE;
	}

	printf("Write lock released\n");
	close(fd);
	return EXIT_SUCCESS;
}

