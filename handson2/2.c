#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>

int main(){
	struct rlimit limit;

	if(getrlimit(RLIMIT_CPU,&limit)==0){
		printf("CPU time limit (soft/hard):%ld /%ld\n",limit.rlim_cur,limit.rlim_max);
	}
	else{
		perror("getrlimit");
		return EXIT_FAILURE;
	}

	if(getrlimit(RLIMIT_FSIZE,&limit)==0){
		printf("File size Limit (soft/hard): %ld / %ld\n",limit.rlim_cur,limit.rlim_max);
	}
	else{
		perror("getrlimit");
		return EXIT_FAILURE;
	}
	// on running it is showing -1/-1 for both
	return EXIT_SUCCESS;

}


