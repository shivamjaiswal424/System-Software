#include <sys/types.h>  // Import for `socket`, `connect`
#include <sys/socket.h> // Import for `socket`, `connect`
#include <netinet/ip.h> // Import for `struct sockaddr_in`, `htons`
#include <stdio.h>      // Import for `perror` & `printf`
#include <unistd.h>     // Import for `_exit`, `read`, write`
#include <stdlib.h>

int main(){
	int clientDescriptor;
	clientDescriptor=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(1999);
	client.sin_addr.s_addr=INADDR_ANY;

	if(connect(clientDescriptor,(struct sockaddr*)(&client),sizeof(client))==-1){
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}
	printf("Client to server connection established\n");
	char datafromserver[100];
	int readbytes=read(clientDescriptor,datafromserver,100);
	printf("Data from server: %s\n",datafromserver);

	int writebytes=write(clientDescriptor,"Client is here",14);

	close(clientDescriptor);
}
