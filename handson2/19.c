#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(){
	int i=mkfifo("myfifo_by_mkfifo",0766);
	if(i==-1){
		perror("mkfifo");
		return -1;
	}
	int j=mknod("myfifo_by_mknod", S_IFIFO | 0766, 0);
	if(j==1){
		perror("mknod");
		return -1;
	}
	return 0;
	
}
