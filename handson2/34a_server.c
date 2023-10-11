#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `accept`
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `accept`
#include <netinet/ip.h> // Import for `struct sockaddr_in`, `htons`
#include <stdio.h>      // Import for `perror` & `printf`
#include <unistd.h>     // Import for `_exit`, `read`, `write`


int main(){
        int serverDescriptor,clientDescriptor;
        struct sockaddr_in server,client;

        serverDescriptor=socket(AF_INET,SOCK_STREAM,0);

        if(serverDescriptor==-1){
                perror("Socket creation failed");
                exit(EXIT_FAILURE);
        }

        server.sin_family=AF_INET;
        server.sin_port=htons(1999);
        server.sin_addr.s_addr=INADDR_ANY;

        int bindStatus=bind(serverDescriptor, (struct sockaddr *)(&server),sizeof(server));

        if(bindStatus==-1){
                perror("Bind failed");
                exit(EXIT_FAILURE);
        }
        if(listen(serverDescriptor,4)==-1){
                perror("Listen failed");
                exit(EXIT_FAILURE);
        }
        else{
                printf("Server is listening\n");
        }
	while(1){

        	int cs=(int)sizeof(client);
        	clientDescriptor=accept(serverDescriptor,(struct sockaddr *)(&client),&cs);


        	if(clientDescriptor==-1){
                	perror("Accept failed");
        	        exit(EXIT_FAILURE);
        	}
        	else{
                	if(fork()==0){

        	
        			char datafromclient[100];
        			int writebytes=write(clientDescriptor,"Server is here",14);
        			if(writebytes==-1){
        		        	perror("error while writing\n");
        			}
        			int readbytes=read(clientDescriptor,datafromclient,100);
        			if(readbytes==-1){
        		        	perror("Error while reading\n");
        			}
				else{
        				printf("Data from Client: %s\n",datafromclient);
				}
			}
			else{
				close(clientDescriptor);
			}
		}
	}
        close(serverDescriptor);
        //close(clientDescriptor);
        return 0;

}
