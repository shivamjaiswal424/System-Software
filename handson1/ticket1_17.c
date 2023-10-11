/*Name-Ticket1_17.c
 *Author-Shivam Jaiswal
 *Description:Write a program to simulate online ticket reservation. Implement write lock 
Write a program to open a file, store a ticket number and exit. Write a separate program, to 
open the file, implement write lock, read the ticket number, increment the number and print 
the new ticket number then close the file.
 *
 *
 * */





#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>

int main(){
	char* file="Ticket_System.txt";
	int fd = open(file, O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);

        if(fd==-1){
                perror("Error while opening the file");
                return -1;
        }

        int initialTicketNo=1;
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%d\n", initialTicketNo);
        ssize_t br;
        br = write(fd, buffer, strlen(buffer));
        if(br == -1){
            perror("Error in writing to the file");
            exit(1);
        }
	
        close(fd);

       	printf("Initial Ticket Number: %d\n",initialTicketNo);
	getchar();
        return 0;
}
