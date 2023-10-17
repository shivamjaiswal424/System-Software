// Name : 21_a.c
// Author : Shivam Jaiswal
// Description :Write two programs so that both can communicate by FIFO -Use two way communications.


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
	int fd1=open("myfifo1",O_WRONLY);
	int fd2=open("myfifo2",O_RDONLY);
	printf("Enter the text :");
	char buff1[100],buff2[100];
	/*while(1){
		fgets(buff1,sizeof(buff1),stdin);
		if(strcmp(buff1,"exit\n")==0){
			break;
		}
	}*/
	scanf("%[^\n]",buff1);
	write(fd1,buff1,sizeof(buff1));
	read(fd2,buff2,sizeof(buff2));
	printf("The text from FIFO file:\n %s",buff2);

}
