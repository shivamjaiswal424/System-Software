// Name : 29.c
// Author : Shivam Jaiswal
// Description :Write a program to create a shared memory.
//  a. write some data to the shared memory
//  b. attach with O_RDONLY and check whether you are able to overwrite.
//  c. detach the shared memory
//  d. remove the shared memory
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int key,shmid;
	key=ftok(".",'b');
	if(key==-1){
		perror("key");
		exit(1);
	}
	system("ipcs -m");
	shmid=shmget(key,1024,IPC_CREAT|0744);
	if(shmid==-1){
		perror("shmid");
		exit(1);
	}
	system("ipcs -m");
	char *data=shmat(shmid,(char *)0,0);

	//system("ipcs -m");
	printf("Enter the text: ");
	scanf("%[^\n]",data);
	system("ipcs -m");
	int a=shmdt(data);
	int b=shmctl(shmid,IPC_RMID,NULL);
	system("ipcs -m");

	int key2,shmid2;
	key2=ftok("/tmp",'b');
	shmid2=shmget(key,1024,IPC_CREAT|0744);
	char *data2=shmat(shmid2,(char *)0,SHM_RDONLY);
	printf("Enter the text: \n ");
	scanf("%[^\n]",data2);
	int c=shmdt(data2);
	int d=shmctl(shmid2,IPC_RMID,NULL);

}
