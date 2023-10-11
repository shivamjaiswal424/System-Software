#include <stdio.h>
#include <stdlib.h>

int main(){
	char buff[100];
	int fd[2];
	int i=pipe(fd);
	if(i==-1){
		perror("Error occurred");
		return;
	}
	if(fork()){
		close(fd[0]);//close the read end for parent
		printf("Enter message to be sent from parent ");
		scanf("%[^\n]",buff);
		write(fd[1],buff,sizeof(buff));

	}
	else{
		close(fd[1]);
		read(fd[0],buff,sizeof(buff));
		printf("Message from parent: %s\n",buff);
	}
	wait(0);

}

