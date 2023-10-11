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
