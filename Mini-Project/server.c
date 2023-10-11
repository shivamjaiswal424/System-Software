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
#define INITIAL_PROMPT "Welcome to IIITB College!\nWho are you?\n1. Admin\n2. Faculty\n3.Student\nPress any other number to exit\nEnter the number corresponding to the choice!"

void client_handler(int connectionFD){
    printf("Client has connected to the server.\n");

    char readBuff[1000],writeBuff[1000];
    ssize_t readBytes,writeBytes;
    int choice;
    writeBytes=write(connectionFD,INITIAL_PROMPT,sizeof(INITIAL_PROMPT));
    if(writeBytes==-1){
        perror("Error while send the message to the User\n");
    }
    else{
        bzero(readBuff,sizeof(readBuff));//clearing the buffer
        readBytes=read(connectionFD,readBuff,sizeof(readBuff));
        if(readBytes==-1){
            perror("Error while reading from client.\n");
        }
        else if(readBytes==0){
            printf("No data has been sent by the client.\n");
        }
        else{
            choice=atoi(readBuff);
            switch(choice){
                case 1:
                    //Admin
                    //admin_function(connectionFD)
                    break;
                case 2:
                    //Faculty
                    //Faculty_function(connectionFD)
                    break;
                case 3:
                    //Student
                    //Student_function(connectionFD)
                    break;
                default:
                    //Exit
                    break;
            }
        }
    }
    printf("Terminating connection. \n");
}

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
                //client_handler(connectionFileDescriptor);
                close(connectionFileDescriptor);
                exit(0);
            }
        }
    }
    close(socketFileDescriptor);
}