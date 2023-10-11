#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	//wrting ouput of ls -l to pipe 1 write-end=STDOUT
	if(fork()==0){
		dup2(fd1[1],1);//write-end of pipe1 =new STDOUT
		close(fd1[0]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("ls","ls","-l",NULL);

	}
	else{
	//writing ls -l | grep ^d where input is received from read-end of pipe 1=STDIN and ouput is written to write-end of pipe 2=STDOUT
		if(fork()==0){
			dup2(fd2[1],1);
			dup2(fd1[0],0);
			close(fd1[1]);
			close(fd2[0]);
			execlp("grep","grep","^d",NULL);
		}
		// this parent will be running ls -l | grep ^d | wc , where input is received from read-end of pipe 2=STDIN and output is written to STDOUT
		else{
			dup2(fd2[0],0);
			close(fd2[1]);
			close(fd1[0]);
			close(fd1[1]);
			execlp("wc","wc",NULL);
		}
	}

}
