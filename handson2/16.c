// Name : 16.c
// Author : Shivam Jaiswal
// Description :  Write a program to send and receive data from parent to child vice versa. Use two way 
//communication.


#include <stdio.h>
#include <stdlib.h>

int main(){
	char buff1[100],buff2[100];
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);

	if(!fork()){
		close(fd1[0]);//closing read end for child
		close(fd2[1]);//closing write end for child
		printf("Enter message to parent to be sent by child: ");
		scanf("%[^\n]",buff1);
		write(fd1[1],buff1,sizeof(buff1));
		read(fd2[0],buff2,sizeof(buff2));
		printf("Message from parent read by child: %s\n",buff2);
		
	}
	else{
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0],buff1,sizeof(buff1));
		printf("Message form child read by parent: %s\n",buff1);
		printf("Message to  child to be sent by parent: ");

		scanf("%[^\n]",buff2);
		write(fd2[1],buff2,sizeof(buff2));
	}
}
