#include <stdio.h>      // Import for `printf` & `perror` functions
#include <errno.h>      // Import for `errno` variable
#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `connect`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `connect` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture
#include <string.h>     // Import for string functions
#include <stdlib.h>     //Import EXIT_FAILURE etc

void server_handler(int socketFD){
    char readBuff[1000],writeBuff[1000];
    ssize_t readBytes,writeBytes;
    char TempBuff[1000];
    do{
        bzero(readBuff,sizeof(readBuff));//Empty the read buffer
        bzero(writeBuff,sizeof(writeBuff));
        readBytes=read(socketFD,readBuff,sizeof(readBuff));
        if(readBytes==-1){
            perror("Error while reading from server!\n");
        }
        else if(readBytes==0){
            printf("Closing the connection now.\n");
        }
        else if(strchr(readBuff,'^')!=NULL){
            //skip read from client
            strncpy(TempBuff,readBuff,strlen(readBuff)-2);
            printf("%s\n",TempBuff);
            writeBytes=write(socketFD,"^",strlen("^"));
            if(writeBytes==-1){
                perror("Error while writing to server!\n");
                break;
            }
        }
        else if(strchr(readBuff,'$')!=NULL){
            //Server sent an error message and is closing it's connection
            strncpy(TempBuff,readBuff,strlen(readBuff)-2);
            printf("%s\n",TempBuff);
            printf("Closing the connection to the server now\n");
            break;
        }
        else{
            bzero(writeBuff,sizeof(writeBuff));
            if(strchr(readBuff,'#')!=NULL){
                strcpy(writeBuff,getpass(readBuff)); 
            }
            else{
                printf("%s\n",readBuff);
                scanf("%[^\n]%*c",writeBuff);//Take user input
            }
            if((writeBytes=write(socketFD,writeBuff,strlen(writeBuff)))==-1){
                perror("Error while writing to client socket!\n");
                printf("Closing the connection to the server now!\n");
                break;
            }
        }
    }while(readBytes>0);
    close(socketFD);

}

void main(){
    int socketFileDescriptor,connectStatus;
    struct sockaddr_in client;

    socketFileDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if(socketFileDescriptor==-1){
        perror("Error while creating client socket!\n");
        exit(EXIT_FAILURE);
    }
    client.sin_family=AF_INET;
    client.sin_port=htons(2005);
    client.sin_addr.s_addr=htonl(INADDR_ANY); //check here once

    connectStatus=connect(socketFileDescriptor,(struct sockaddr *)&client,sizeof(client));

    if(connectStatus==-1){
        perror("Error while connecting to server!\n");
        close(socketFileDescriptor);
        exit(0);
    }
    server_handler(socketFileDescriptor);
    close(socketFileDescriptor);

}