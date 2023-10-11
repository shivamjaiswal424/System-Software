//Name:19.c
//Author:Shivam Jaiswal
//Description: Find out the priority of your running program. Modify the priority with nice command.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
	int old_priority=getpriority(PRIO_PROCESS,getpid());//PRIO_PROCESS indicates the argument is to  interpreted is a PROCESS_ID.
	
	if(old_priority==-1){
		perror("Error while opening the priority of a processs\n");
		return -1;
	}
	printf("Priority of a process before updating is %d\n",old_priority);

	printf("Enter the nice value between -20 and 19\n");
	int n;
	scanf("%d",&n);
	nice(n);
	int new_priority=getpriority(PRIO_PROCESS,getpid());

	if(new_priority==-1){
		if(errno==EINVAL){
			perror("Invalid argument");
		}
		else if(errno==EACCES){
			perror("Access denied");
		}
		else if(errno==ESRCH){
			perror("No  such process");
		}
		
	}

	printf("New priority of the process after priority is %d",new_priority);

	return 0;


}
