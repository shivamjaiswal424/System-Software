#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS
#include "./common.h"


bool admin_operation_handler(int connectionFD);
bool add_student();
bool add_faculty();
bool activeDeactiveStudent();
bool update();

bool admin_operation_handler(int connectionFD){
    if(login_handler(0,connectionFD,NULL,NULL)){
        ssize_t writeBytes, readBytes;
        char readBuff[1000],writeBuff[1000];
        bzero(writeBuff,sizeof(writeBuff));
        strcpy(writeBuff,ADMIN_LOGIN_SUCCESS);
        while(1){
            strcat(writeBuff,"\n");
            strcat(writeBuff,ADMIN_MENU);
            writeBytes=write(connectionFD,writeBuff,strlen(writeBuff));
            if(writeBytes==-1){
                perror("Error while writing ADMIN_MENU to ADMIN");
                return false;
            }
            bzero(writeBuff,sizeof(writeBuff));
            readBytes=read(connectionFD,readBuff,sizeof(readBuff));
            if(readBytes==-1){
                perror("Error while reading user's for ADMIN_MENU ");
                return false;

            }
            int choice=atoi(readBuff);
            switch(choice){
                case 1:
                    //add Student
                    break;
                case 2:
                    //add Faculty
                    break;
                case 3:
                    //Activate/Deactivate
                    break;
                case 4:
                    //update
                    break;
                default:
                    writeBytes=write(connectionFD,ADMIN_LOGOUT,strlen(ADMIN_LOGOUT));
                    return false;
            }
        }
    }
    else{
        //ADMIN LOGIN FAILED
        return false;
    }
    return true;
}
#endif