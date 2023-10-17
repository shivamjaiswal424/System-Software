// Name : 24.c
// Author : Shivam Jaiswal
// Description :Write a program to create a message queue and print the key and message queue id.

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
int main(){
	key_t key=ftok(".",'a');
	int msgid=msgget(key,IPC_CREAT|IPC_EXCL|0744);
	printf("key=0x%0x\t msgid=%d\n",key,msgid);	
}

