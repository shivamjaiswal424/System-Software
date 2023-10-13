#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS

#include <stdio.h>     // Import for `printf` & `perror`
#include <unistd.h>    // Import for `read`, `write & `lseek`
#include <string.h>    // Import for string functions
#include <stdbool.h>   // Import for `bool` data type
#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <stdlib.h>    // Import for `atoi`
#include <errno.h>     // Import for `errno`

#include "./structures.h"
#include "./admin-credentials.h"
#include "./defines.h"

bool login_handler(int who,int connFD,Student *ptrToStudentID,Faculty *ptrToFacultyID){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    char tempBuff[1000];
    Student student;
    Faculty faculty;

    int ID;
    bzero(readBuff,sizeof(readBuff));
    bzero(writeBuff,sizeof(writeBuff));

    //Get Login message for respective user type
    if(who==0){
        strcpy(writeBuff,ADMIN_LOGIN_WELCOME);
    }
    else if(who==1){
        strcpy(writeBuff,FACULTY_LOGIN_WELCOME);
    }
    else{
        strcpy(writeBuff,STUDENT_LOGIN_WELCOME);
    }
    strcat(writeBuff,"\n");
    strcat(writeBuff,LOGIN_ID);

    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error while writing WELCOME & LOGIN_ID message!");
        return false;
    }

    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading login ID from user!");
        return false;
    }
    bool userFound=false;

    if(who==0){
        if(strcmp(readBuff,ADMIN_LOGIN_ID)==0) userFound=true;
    }
    else{
        //some code for faculty and student
        
    }

    if(userFound){
        bzero(writeBuff,sizeof(writeBuff));
        writeBytes=write(connFD,PASSWORD,strlen(PASSWORD));
        if(writeBytes==-1){
            perror("Error writing PASSWORD message to the user!");
            return false;
        }

        bzero(readBuff,sizeof(readBuff));
        readBytes=read(connFD,readBuff,sizeof(readBuff));

        if(readBytes==-1){
            perror("Error reading password from the user");
            return false;
        }
        char hashedPassword[1000];
        strcpy(hashedPassword,crypt(readBuff,"somesalt"));
        if(who==0){
            char *password=ADMIN_PASSWORD;
            char *hasspass=crypt(password,"somesalt");
            if(strcmp(ADMIN_PASSWORD,readBuff)==0) {
                printf("TRUE\n");
                return true;
            }
        }
        else{
            //Some functions for Faculty and Student
            return true;
        }
        bzero(writeBuff,sizeof(writeBuff));
        writeBytes=write(connFD,INVALID_PASSWORD,strlen(INVALID_PASSWORD));
    }
    else{
        bzero(writeBuff,sizeof(writeBuff));
        writeBytes=write(connFD,INVALID_LOGIN,strlen(INVALID_LOGIN));
    }
    return false;
    


}


#endif