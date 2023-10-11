/*Name :9.c
 * Author:Shivam Jaiswal
 *Description:Write a program to print the following information about a given file.
 a. inode
 b. number of hard links
 c. uid
 d. gid
 e. size
 f. block size
 g. number of blocks
 h. time of last access
 i. time of last modification
 j. time of last change
 *
 *
 *
 * */



#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]){
           struct stat sb;

           if (argc != 3) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }
	   if(stat(argv[2], &sb)==-1){
		perror("Error while fetching file information");
		exit(EXIT_FAILURE);
	   }

           printf("I-node number:%ju\n", (uintmax_t) sb.st_ino);
	   printf("Hard Link count:%ju\n", (uintmax_t) sb.st_nlink);
	   printf("UID=%ju   \n",(uintmax_t) sb.st_uid);
	   printf("GID=%ju   \n",(uintmax_t) sb.st_gid);
	   printf("File size:  %jd bytes\n",(intmax_t) sb.st_size);

          printf("Block size: %jd bytes\n",(intmax_t) sb.st_blksize);
           printf("Number of Blocks: %jd\n",(intmax_t) sb.st_blocks);
	   printf("Time of last access: %s\n", ctime(&sb.st_atime));
           printf("Time of last change: %s\n", ctime(&sb.st_ctime));
           printf("Time of Last modification: %s\n", ctime(&sb.st_mtime));

           exit(EXIT_SUCCESS);
}
