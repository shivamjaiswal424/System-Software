// Name : 21_b.c
// Author : Shivam Jaiswal
// Description :Write two programs so that both can communicate by FIFO -Use two way communications.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
	int fd2=open("myfifo1",O_RDONLY);
	int fd1=open("myfifo2",O_WRONLY);
	
	char buff1[100],buff2[100];
	
	read(fd2,buff1,sizeof(buff1));
	printf("The text from FIFO file: \n%s",buff1);
	printf("Enter the text: \n");
	scanf("%[^n]",buff2);
	write(fd2,buff2,sizeof(buff2));
	/*
	while(1){
		fgets(buff2,sizeof(buff2),stdin);
		if(strcmp(buff2,"exit\n")==0) break;
		write(fd1,buff2,sizeof(buff2));
	}*/
}
