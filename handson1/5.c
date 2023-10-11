/*Name:5.c
 *Author:Shivam Jaiswal
 *Description:Write a program to create five new files with infinite loop.Execute the program in the background and check the file descriptor table at /proc/pid/fd.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
int main(){
	for(int i=1;i<=5;i++){
		if(i<=5){
			char file[20];
			snprintf(file,sizeof(file),"file%d.txt",i);

			int fd=creat(file,0644);
			if(fd==-1){
				perror("Error creating the file");
				return 0;
			}
			printf("file named '%s' is created\n ",file);

		}

	}
	while(true){
		continue;
	}
	return 0;

}

