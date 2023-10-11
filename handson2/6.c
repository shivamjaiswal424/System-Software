#include <pthread.h>
#include<stdio.h>
#include <stdlib.h>

void *myThreadFunction(void *argvp){
	printf("Thread id is %ld\n",pthread_self());
	return NULL ;
}

int main(){
	pthread_t tid[3];
	for(int i=0;i<3;i++){
		pthread_create(&tid[i],NULL,myThreadFunction,NULL);
	}
	for(int i=0;i<3;i++){
		pthread_join(tid[i],NULL);
	}
	exit(0);

}
