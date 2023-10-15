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

bool login_handler(int who,int connFD,struct Student *ptrToStudentID,struct Faculty *ptrToFacultyID){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    char tempBuff[1000];
    struct Student student;
    struct Faculty faculty;

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

bool get_student_details(int connFD, struct Student *ptrToStudent){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    char tempBuff[1000];

    int studentID;
    struct Student student;
    int StudentFileDescriptor;
    struct flock lock={F_RDLCK,SEEK_SET,0,sizeof(struct Student),getpid()};

    if(ptrToStudent==NULL){
        writeBytes=write(connFD,GET_STUDENT_ID,strlen(GET_STUDENT_ID));
        if(writeBytes==-1){
            perror("Error  writing GET_STUDENT_ID message to user!");
            return false;
        }
        bzero(readBuff,sizeof(readBuff));
        readBytes=read(connFD,readBuff,sizeof(readBuff));
        if(readBytes==-1){
            perror("Error reading account number response from user!");
            return false;
        }
        studentID=atoi(readBuff);
    }
    StudentFileDescriptor=open(STUDENT_FILE,O_RDONLY);

    if(StudentFileDescriptor==-1){
        bzero(writeBuff,sizeof(writeBuff));
        strcpy(writeBuff,NO_STUDENT_ID);
        strcat(writeBuff,"^");
        perror("Error while opening student file to get student details!");
        writeBytes=write(connFD,writeBuff,strlen(writeBuff));
        if(writeBytes==-1){
            perror("Error while writing NO_STUDENT_ID message to the user.\n");
            return false;
        }
        readBytes=read(connFD,readBuff,sizeof(readBuff));
        return false;
    }
    int offset=lseek(StudentFileDescriptor,(studentID)*sizeof(struct Student),SEEK_SET); //0-indexing
    if(errno==EINVAL){
        //Student doesn't exist
        bzero(writeBuff,sizeof(writeBuff));
        strcpy(writeBuff,NO_STUDENT_ID);
        strcat(writeBuff,"^");
        perror("Error seeking to Student record to get Student details!");
        writeBytes=write(connFD,writeBuff,strlen(writeBuff));
        if(writeBytes==-1){
            perror("Error while writing NO_STUDENT_ID message to the user");
            return false;
        }
        readBytes=read(connFD,readBuff,sizeof(readBuff));//Dummy read for "^".
        return false;
    }
    else if(offset==-1){
        perror("Error seeking to Student record to get Student details!");
        return false;
    }
    lock.l_start=offset;
    int lockingStatus=fcntl(StudentFileDescriptor,F_SETLKW,&lock);
    if(lockingStatus==-1){
        perror("Error obtaining read lock on Student record");
        return false;
    }
    readBytes=read(StudentFileDescriptor,&student,sizeof(struct Student));
    if(readBytes==-1){
        perror("Error reading Student record from the file!");
        return false;
    }
    lock.l_type=F_UNLCK;
    fcntl(StudentFileDescriptor,F_SETLK,&lock);

    if(ptrToStudent!=NULL){
        *ptrToStudent=student;
        return true;
    }
    bzero(writeBuff,sizeof(writeBuff));
    sprintf(writeBuff, "Student Details- \nStudent Name: %s\nStudent Age: %d\nStudent Login ID: %s\nStudent status: %s\nStudent Email ID: %s\nStudent ID: %d\n",student.name,student.age,student.login_id, (student.active? "Active" : "Deactive"),student.email_id,(student.stud_id));
    if(student.active){
        //show the courses ,student has taken
    }
    strcat(writeBuff,"\nRedirecting you to the main menu ...^");
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error while giving info to user");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    return true;
}

bool get_faculty_details(int connFD, struct Faculty *ptrTofaculty){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    char tempBuff[1000];

    int facultyID;
    struct Faculty faculty;
    int FacultyFileDescriptor;
    struct flock lock={F_RDLCK,SEEK_SET,0,sizeof(struct Faculty),getpid()};

    if(ptrTofaculty==NULL){
        writeBytes=write(connFD,GET_FACULTY_ID,strlen(GET_FACULTY_ID));
        if(writeBytes==-1){
            perror("Error  writing GET_FACULTY_ID message to user!");
            return false;
        }
        bzero(readBuff,sizeof(readBuff));
        readBytes=read(connFD,readBuff,sizeof(readBuff));
        if(readBytes==-1){
            perror("Error reading account number response from user!");
            return false;
        }
        facultyID=atoi(readBuff);
    }
    FacultyFileDescriptor=open(FACULTY_FILE,O_RDONLY);

    if(FacultyFileDescriptor==-1){
        bzero(writeBuff,sizeof(writeBuff));
        strcpy(writeBuff,NO_FACULTY_ID);
        strcat(writeBuff,"^");
        perror("Error while opening faculty file to get faculty details!");
        writeBytes=write(connFD,writeBuff,strlen(writeBuff));
        if(writeBytes==-1){
            perror("Error while writing NO_FACULTY_ID message to the user.\n");
            return false;
        }
        readBytes=read(connFD,readBuff,sizeof(readBuff));
        return false;
    }
    int offset=lseek(FacultyFileDescriptor,(facultyID)*sizeof(struct Faculty),SEEK_SET); //0-indexing
    if(errno==EINVAL){
        //Student doesn't exist
        bzero(writeBuff,sizeof(writeBuff));
        strcpy(writeBuff,NO_FACULTY_ID);
        strcat(writeBuff,"^");
        perror("Error seeking to faculty record to get faculty details!");
        writeBytes=write(connFD,writeBuff,strlen(writeBuff));
        if(writeBytes==-1){
            perror("Error while writing NO_FACULTY_ID message to the user");
            return false;
        }
        readBytes=read(connFD,readBuff,sizeof(readBuff));//Dummy read for "^".
        return false;
    }
    else if(offset==-1){
        perror("Error seeking to Faculty record to get Faculty details!");
        return false;
    }
    lock.l_start=offset;
    int lockingStatus=fcntl(FacultyFileDescriptor,F_SETLKW,&lock);
    if(lockingStatus==-1){
        perror("Error obtaining read lock on Faculty record");
        return false;
    }
    readBytes=read(FacultyFileDescriptor,&faculty,sizeof(struct Faculty));
    if(readBytes==-1){
        perror("Error reading Faculty record from the file!");
        return false;
    }
    lock.l_type=F_UNLCK;
    fcntl(FacultyFileDescriptor,F_SETLK,&lock);

    if(ptrTofaculty!=NULL){
        *ptrTofaculty=faculty;
        return true;
    }
    bzero(writeBuff,sizeof(writeBuff));
    sprintf(writeBuff, "Faculty Details- \nFaculty Name: %s\nFacultyAge: %d\nFaculty Login ID: %s\nFaculty status: %s\nFacultyEmail ID: %s\nFaculty ID: %d\n",faculty.name,faculty.age,faculty.login_id, (faculty.active? "Active" : "Deactive"),faculty.email_id,(faculty.faculty_id));
    if(faculty.active){
        //show the courses ,
    }
    strcat(writeBuff,"\n Redirecting you to the main menu ...^");
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error while giving info to user");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    return true;
}
#endif