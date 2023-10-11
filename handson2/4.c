#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long rdtsc(){
	unsigned long long dst;
	__asm__ __volatile__("rdtsc":"=A"(dst));
	return dst;
}
int main(){
	long long int start,end;
	start=rdtsc();
	for(int i=0;i<100;i++){
		getppid();
	}
	end=rdtsc();
	printf("Time taken to execute 100 getppid() : %llu\n",end-start);
	
	exit(0);
}

