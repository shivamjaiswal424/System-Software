/*
 *Name:1.c
 *Author:Shivam Jaiswal
 *Description:
 Create the following types of a files using (i) shell command (ii) system call
 a. soft link (symlink system call)
 b. hard link (link system call)
 c. FIFO (mkfifo Library Function or mknod system call)

 * */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	char file1[100],file2[100];
	printf("Enter filename to be pointed by softlink\n");
	scanf("%s",file1);
	printf("Enter softlink filename\n");
	scanf("%s",file2);
	int soft_link=symlink(file1,file2);
	if(soft_link==-1){
		perror("Soft linking failed\n");
		return 1;
	}
	else{
		printf("softlink created successfully\n");
	}

	printf("Enter filename to pointed by hardlink\n");
	scanf("%s",file1);
	printf("Enter hardlink filename\n");
	scanf("%s",file2);
	int hard_link=link(file1,file2);
	if(hard_link==-1){
		perror("Hard linking failed\n");
		return 1;
	}
	else{
		printf("Hardlink created successfully\n");
	}

	printf("Enter pipename\n");
	scanf("%s",file1);

	if(mknod(file1,S_IFIFO,0)==-1){
		perror("Error creating named pipe");
		return 1;
	}
	printf("Named pipe '%s' created successfully.\n", file1);

	return 0;
}
