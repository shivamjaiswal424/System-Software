/*Name-ticket2_17.c
 *Author-Shivam Jaiswal
 *Description:Write a program to simulate online ticket reservation. Implement write lock 
Write a program to open a file, store a ticket number and exit. Write a separate program, to 
open the file, implement write lock, read the ticket number, increment the number and print 
the new ticket number then close the file.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

int main(){
        char* file="Ticket_System.txt";
        int fd=open(file, O_RDWR |O_CREAT ,0777);

        if(fd==-1){
                perror("Error occurred");
                return -1;
        }

        //Acquire a write Lock
        if(flock(fd ,LOCK_EX)==-1){
                perror("Error acquiring the lock");
                close(fd);
                return -1;
        }


        char buffer[20];
        int bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            perror("Error reading from file");
            close(fd);
            return 1;
        }

        int currentTicket = atoi(buffer);
        printf("Current ticket number: %d\n", currentTicket);

        lseek(fd, 0, SEEK_SET);
        snprintf(buffer, sizeof(buffer), "%d\n", currentTicket + 1);
        ssize_t br;
        br = write(fd, buffer, strlen(buffer));

        if(br == -1){
            perror("Error in writing to the file");
            exit(1);
        }
	getchar();
        if(flock(fd,LOCK_UN)==-1){
                perror("Error releasing the lock");
                close(fd);
                return -1;
        }

        printf("New Ticket Number: %d\n",currentTicket+1);

        close(fd);

        return 0;
}
