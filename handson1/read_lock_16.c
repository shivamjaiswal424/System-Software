/*Name: read_lock_16.c
 *Author:Shivam Jaiswal
 *Description:Write a program to perform mandatory locking.
 a. Implement write lock
 b. Implement read lock
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
        char* file="src.txt";
        int fd=open(file, O_RDONLY);

        if(fd==-1){
                perror("Error while opening the file");
                return EXIT_FAILURE;
        }
        struct flock lock;
        lock.l_type=F_RDLCK; // write lock
        lock.l_whence=SEEK_SET; // sets the reference point for the start of the lock to the beginning of the file
        lock.l_start=0; // sets the starting offset of the  lock to 0
        lock.l_len=0;//lock the entire file

        if(fcntl(fd,F_SETLK,&lock)==-1){
                perror("Error on locking the file");
                close(fd);
                return EXIT_FAILURE;
        }

        printf("Read lock is acquired.Press Enter to release the lock...\n");
        getchar();

        lock.l_type=F_UNLCK;
        if(fcntl(fd,F_SETLK,&lock)==-1){
                perror("Error while unlocking the file");
                close(fd);
                return EXIT_FAILURE;
        }

        printf("Read lock released\n");
        close(fd);
        return EXIT_SUCCESS;
}
