// Name : 19.c
// Author : Shivam Jaiswal
// Description :  Create a FIFO file by
//  a. mknod command
//  b. mkfifo command
//  c. use strace command to find out, which command (mknod or mkfifo) is better.
//  c. mknod system call
//  d. mkfifo library function




#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(){
	int i=mkfifo("myfifo_by_mkfifo",0766);
	if(i==-1){
		perror("mkfifo");
		return -1;
	}
	int j=mknod("myfifo_by_mknod", S_IFIFO | 0766, 0);
	if(j==1){
		perror("mknod");
		return -1;
	}
	return 0;
	
}
