/*
 *Name:15.c
 *Author:Shivam Jaiswal
 *Description:. Write a program to display the environmental variable of the user (use environ).
 * */



#include<stdlib.h>
#include <stdio.h>

int main(){
	if(getenv("USER")==NULL){
		printf("Error");
	}
	else{
		printf("Environment variable for user is: %s\n",getenv("USER"));
	}
	return 0;
}
