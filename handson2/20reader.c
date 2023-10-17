// Name : 20reader.c
// Author : Shivam Jaiswal
// Description :  Write two programs so that both can communicate by FIFO -Use one way communication.



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
	int fd=open("myfifo",O_RDONLY);
	char buff[100];
	read(fd,buff,sizeof(buff));
	printf("The text from FIFO file:\n %s",buff);
}
