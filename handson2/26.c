#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer{
	long msg_type;
	char msg_text[1024];
};

int main(){
	struct msg_buffer msg;
	key_t key;
	int msgid;
	key=ftok("/tmp",'a');
	if(key==-1){
		perror("ftok");
		exit(1);
	}
	msgid=msgget(key,0666|IPC_CREAT);
	if(msgid==-1){
		perror("msgget");
		exit(1);
	}
	fgets(msg.msg_text,1024,stdin);
	msg.msg_type=1;
	if(msgsnd(msgid,&msg,sizeof(msg.msg_text),0)==-1){
		perror("msgsnd");
		exit(1);
	}
	//Display information about the message queue
	system("ipcs -q");
	//Remove the message from queue
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
}
