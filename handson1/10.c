/*
 Name:10.c
Author:Shivam Jaiswal
Description:
Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10bytes (use lseek) and write again 10 bytes. 
 a. check the return value of lseek
 b. open the file with od and check the empty spaces in between the data. 
 */



#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char* path = "new.txt";
    int file = open(path, O_RDWR|O_CREAT);

    if (file == -1) {
        perror("Wrong Turn");
        return 1;
    }

    char data1[] = "ABCDEFGHIJ";
    write(file, data1, sizeof(data1)-1); 

    
    off_t seek_offset = lseek(file, 10, SEEK_CUR);
    printf("lseek return value: %ld\n", seek_offset);


    const char data2[] = "abc4efghij";
    write(file, data2, sizeof(data2)-1); 

    close(file);

    
    char od_command[100];
    snprintf(od_command, sizeof(od_command), "od -c %s", path);
    system(od_command);

    return 0;
}
