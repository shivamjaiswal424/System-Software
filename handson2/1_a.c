#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

void timer_handler(int sig){
	printf("Timer Expired!\n");
	
}

int main(){
	struct itimerval timer;
	//struct sigaction sa;

	timer.it_value.tv_sec=0;
	timer.it_value.tv_usec=10;
	timer.it_interval.tv_sec=0;
	timer.it_interval.tv_usec=10;
	//sa.sa_handler=timer_handler;
	signal(SIGALRM,timer_handler);
	//sigaction(SIGALRM,&sa,0);
	setitimer(ITIMER_REAL,&timer,0);
	while(1){

	}
	return 0;


}

