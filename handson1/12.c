/*
 *Name:12.c
 * Author:Shivam Jaiswal
 * Description:Write a program to find out the opening mode of a file. Use fcntl.
 * */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void print_opening_mode(int file){
	int flags=fcntl(file, F_GETFL);
        if(flags==-1){
                perror("Error getting the flag");
                exit(1);
        }

        int access_mode = flags & O_ACCMODE;
        int opening_mode;

        switch(access_mode){
                case O_RDONLY:
                        printf("Opening mode is read only\n");
                        break;
                case O_WRONLY:
			printf("Opening mode is write only\n");
                        break;
                case O_RDWR:
			printf("Opening mode is read-write only\n");
                        
                        break;
                default:
			printf("Opening mode not found\n");
                        
        }

}

int main(){
	char* path="new_file.txt";
	int file=open(path , O_RDWR | O_CREAT);

	if(file == -1){
		perror("Error opening the file");
		return 1;
	}

	print_opening_mode(file);
	
	close(file);
	return 0;
}
