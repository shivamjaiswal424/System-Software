#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void timer_handler(int sig){
	printf("Timer expired!\n");
	//exit(0);
}

int main(){
	struct itimerval timer;
	timer.it_value.tv_usec=10;
	timer.it_value.tv_sec=0;
	timer.it_interval.tv_sec=0;
	timer.it_interval.tv_usec=10;

	signal(SIGVTALRM,timer_handler);
	setitimer(ITIMER_VIRTUAL,&timer,0);

	while(1){
	}
	return 0;
}
