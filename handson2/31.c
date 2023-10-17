// Name : 31.c
// Author : Shivam Jaiswal
// Description :Write a program to create a semaphore and initialize value to the semaphore.
//  a. create a binary semaphore
//  b. create a counting semaphore


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t binarySemaphore,countingSemaphore;
void *binarySemaphorefunction(void* args){
	printf("(%d) Waiting in the queue\n",*(int*)args);
	sem_wait(&binarySemaphore);
	printf("(%d) inside the function\n",*(int*)args);
	sleep(rand()%3+1);
	printf("(%d) going out of queue\n",*(int*)args);
	sem_post(&binarySemaphore);
	
}
void *countingSemaphorefunction(void* args){
	printf("(%d) waiting in the queue\n",*(int*)args);
	sem_wait(&countingSemaphore);
	printf("%d inside the function \n",*(int*)args);
	sleep(rand()%3+1);
	printf("(%d) going out of queue\n", *(int*)args);
	sem_post(&countingSemaphore);
}

int main(){
	//sem_t binarySemaphore,countingSemaphore;

	sem_init(&binarySemaphore,0,1);
	sem_init(&countingSemaphore,0,3);
	pthread_t thread1[5],thread2[6];
	
	for(int i=0;i<5;i++){
		int* a=malloc(sizeof(int));
		*a=i;
		pthread_create(&thread1[i],NULL,binarySemaphorefunction,a);
	}
	/*for(int i=0;i<6;i++){
                int* b=malloc(sizeof(int));
                b=i;
                pthread_create(&thread2[i],NULL,countingSemaphorefunction,b);
        }*/
	for(int i=0;i<5;i++){
		pthread_join(thread1[i],NULL);
	}
	
	sem_destroy(&binarySemaphore);
	for(int i=0;i<6;i++){
		int* b=malloc(sizeof(int));
		*b=i;
		pthread_create(&thread2[i],NULL,countingSemaphorefunction,b);
	}
	for(int i=0;i<6;i++){
		pthread_join(thread2[i],NULL);
	}
	//sem_destroy(&binarySemaphore);
	sem_destroy(&countingSemaphore);
	return 0;
}
