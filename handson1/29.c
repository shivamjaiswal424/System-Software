//Name:29.c
//Author:Shivam Jaiswal
//Description:Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR)


#define _GNU_SOURCE // Needed for SCHED_FIFO and SCHED_RR
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>

int main(){
        int pid=getpid();

        int current_policy=sched_getscheduler(pid);//gets the current scheduling policy

        if(current_policy==-1){
                perror("Error getting scheduling policy");
                exit(EXIT_FAILURE);
        }

        printf("Current scheduling policy:\n");

        switch(current_policy){
                case SCHED_FIFO:
                        printf("SCHED_FIFO\n");
                        break;
                case SCHED_RR:
                        printf("SCHED_RR\n");
			break;
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
		default:
			printf("Unknown (%d)\n", current_policy);
			break;
	}

	//Will modify the policy
	struct sched_param param;
	param.sched_priority=99; //highest priority for SCHED_FIFO
	
	int result=sched_setscheduler(pid,SCHED_FIFO,&param);

	if(result==-1){
		perror("sched_setscheduler");
		return 1;
	}
	int updated_policy=sched_getscheduler(pid);

	if(updated_policy==-1){
		perror("Sched_getscheduler");
		return 1;
	}

	printf("Updated scheduling policy:\n");

	switch(updated_policy){
		case SCHED_FIFO:
			printf("SCHED_FIFO\n");
			break;
		case SCHED_RR:
			printf("SCHED_RR\n");
			break;
		case SCHED_OTHER:
			printf("SCHED_OTHER\n");
			break;
		default:
			printf("Unknown (%d)\n",updated_policy);

	}
	return 0;
}
