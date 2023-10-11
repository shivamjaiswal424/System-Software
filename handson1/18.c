//Name:18.c
//Author:Shivam Jaiswal
//Description:Write a program to perform Record locking.
// a. Implement write lock
// b. Implement read lock
//Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct{
	int id;
	char data[50];
}Record;

void print_record(const Record* rec){
	printf("ID: %d\nData: %s\n",rec->id,rec->data);
}

int main(){
	const char* filename="records.dat";

	int fd=open(filename, O_RDWR | O_CREAT ,0666);

	if(fd==-1){
		perror("Error opening the file");
		return -1;
	}

	Record rec[3]={
		{1,"Record 1"},{2,"Record 2"},{3,"Record 3"}
	};

	write(fd, &rec,sizeof(rec));
	close(fd);

	int rec_num=1;

	Record record;
	
	off_t offset=rec_num * sizeof(Record);

	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=offset;
	lock.l_len=sizeof(Record);

	fd=open(filename,O_RDWR);

	if(fd==-1){
		perror("Error opening the file");
		return -1;
	}
	
	if(fcntl(fd,F_SETLKW,&lock)==-1){
		perror("Error acquiring read lock");
		close(fd);
		return -1;
	}

	lseek(fd,offset,SEEK_SET);
	ssize_t bytes_read=read(fd,&record,sizeof(Record));

	if(bytes_read==-1){
		perror("Error reading record");
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);
		return -1;
	}

	print_record(&record);

	sleep(2);

	record.id+=100;

	snprintf(record.data, sizeof(record.data), "Updated data for record %d",rec_num);

	lock.l_type=F_WRLCK;
	if(fcntl(fd,F_SETLK,&lock)==-1){
		perror("Error acquiring write lock");
		close(fd);
		return -1;
	}
	lseek(fd,offset,SEEK_SET);
	ssize_t bytes_written=write(fd,&record,sizeof(Record));

	if(bytes_written==-1){
		perror("Error writing record");
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);
		return -1;
	}
	printf("Record updated & written.\n");
	lock.l_type=F_UNLCK;
	if(fcntl(fd,F_SETLK,&lock)==-1){
		perror("Error releasing lock");
		close(fd);
		return -1;
	}
	close(fd);

	return 0;
}




