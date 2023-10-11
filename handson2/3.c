#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>


int main(){
	struct rlimit limit;
	limit.rlim_cur=1024;
	limit.rlim_max=2048;
	if(setrlimit(RLIMIT_CPU,&limit)==0){
		printf("CPU soft time limit changed to %ld\n",limit.rlim_cur);
		printf("CPU time hard limit changes to %ld\n",limit.rlim_max);
	}
	else{
		perror("setrlimit\n");
	}

	return 0;
}
