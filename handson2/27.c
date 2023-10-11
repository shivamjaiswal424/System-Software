#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msg{
	long m_type;
	char message[80];
};

int main(){
	struct msg m1,m2;
	int key1=ftok(".",'a');
	int key2=ftok("..",'b');
	int msgid1=msgget(key1,0);
	int msgid2=msgget(key2,0);
	printf("Enter message type for 0 as a flag: ");
	scanf("%ld",&m1.m_type);
	printf("Enter message type for IPC_NOWAIT as a flag: ");
	scanf("%ld", &m2.m_type);
//	m1.m_type=1;
//	m2.m_type=2;
//	printf("HELLO");
	int res1=msgrcv(msgid1,&m1,sizeof(m1.message),m1.m_type,0|MSG_NOERROR);

	int res2=msgrcv(msgid2,&m2,sizeof(m2.message),m2.m_type,IPC_NOWAIT|MSG_NOERROR);
	if(res1==-1){
		perror("error with 0 flag");
	}
	if(res2==-1){
		perror("Error with IPC_NOWAIT");
	}
	printf("Message type with 0 as a flag: %ld\n  Message: %s\n",m1.m_type, m1.message);
	printf("Message type with IPC_NOWAIT: %ld\n Message: %s\n",m2.m_type, m2.message);	
}
