#include <stdio.h> // Import for `printf` & `perror` functions
#include <errno.h> // Import for `errno` variable

#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `accept`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `accept` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture

#include <string.h>  // Import for string functions
#include <stdbool.h> // Import for `bool` data type
#include <stdlib.h>  // Import for `atoi` function

void main(){
    int socketFileDescriptor,socketBind,socketListen,connectionFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

    socketFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if(socketFileDescriptor==-1){
        perror("Error while creating the server\n");
        exit(EXIT_FAILURE);
    }
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(2000);
    serverAddress.sin_addr.s_addr=INADDR_ANY; //look here once might be some error.

    socketBind=bind(socketFileDescriptor,(struct sockaddr *)(&serverAddress),sizeof(serverAddress));
    if(socketBind==-1){
        perror("Error while binding to server socket\n");
        exit(EXIT_FAILURE);
    }
    socketListen=listen(socketFileDescriptor,12);
    if(socketListen==-1){
        perror("Error while listening for connections \n");
        close(socketFileDescriptor);
        exit(EXIT_FAILURE);
    }
    int clientSize;
    while(1){
        clientSize=(int)sizeof(clientAddress);
        connectionFileDescriptor=accept(socketFileDescriptor,(struct sockaddr *)(&clientAddress),&clientSize);
        if(connectionFileDescriptor==-1){
            perror("Error while connecting to client!\n");
            close(socketFileDescriptor);
        }
        else{
            if(fork()==0){
                //some function for client
                close(connectionFileDescriptor);
                exit(0);
            }
        }
    }
    close(socketFileDescriptor);
}