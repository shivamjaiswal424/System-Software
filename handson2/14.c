#include <stdio.h>
#include <stdlib.h>


int main(){
	int fd[2];
	int i=pipe(fd);
	if(i==-1){
		perror("Failure occurred");
		return;
	}
	char buff[1000];
	int j;
	j=write(fd[1],"Hi this is Shivam\n",19);
	read(fd[0],buff,j);
	printf(buff);
	return;
}
