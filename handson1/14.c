/*
 *Name :14.c
 *Author:Shivam Jaiswal
Description:Write a program to find the type of a file.
 a. Input should be taken from command line.
 b. program should be able to identify any type of a file. 
 * */
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]){
	struct stat sb;

        if (argc < 2) {
        	fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               	return 0;
        }
	int fd = open(argv[1], O_RDWR);
	if(fd==-1){
		printf("File does not exist\n");
		return -1;
	}

        if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
        }

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

	   int cl=close(fd);
	   return 0;
}
