// Name : 20writer.c
// Author : Shivam Jaiswal
// Description :  Write two programs so that both can communicate by FIFO -Use one way communication.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	int fd=open("myfifo",0666);
	char buff[100];
	printf("Enter the text: \n");
	scanf("%[^\n]",buff);
	write(fd,buff,sizeof(buff));

}
