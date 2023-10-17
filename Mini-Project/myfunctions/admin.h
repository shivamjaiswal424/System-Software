#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS
#include "./common.h"


bool admin_handler(int connectionFD);
bool add_student(int connFd);
bool add_faculty(int connFd);
bool update_student(int connFD);

//bool update();

bool admin_handler(int connectionFD){
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
                    //add Faculty
                    add_faculty(connectionFD);
                    break;
                case 2:
                    add_student(connectionFD);
                    break;
                case 3:
                    //Activate_Deactivate_Student(connectionFD,NULL);
                    break;
                case 4:
                    update_student(connectionFD);
                    break;
                case 5:
                    get_student_details(connectionFD,NULL);
                    break;
                case 6:
                    get_faculty_details(connectionFD,NULL);
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
bool add_student(int connFD){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    struct Student newStudent,prevStudent;
    memset(&newStudent,0,sizeof(struct Student));
    memset(&prevStudent,0,sizeof(struct Student));

    int StudentFileDescriptor=open(STUDENT_FILE,O_RDONLY);
    if(StudentFileDescriptor==-1 && errno==ENOENT){
        newStudent.stud_id=0;
    }
    else if(StudentFileDescriptor==-1){
        perror("Error while opening the Student file\n");
        return false;
    }
    else{
        int offset=lseek(StudentFileDescriptor,-sizeof(struct Student),SEEK_END);
        if(offset==-1){
            perror("Error seeking to last Student record");
            return false;
        }
        struct flock lock={F_RDLCK,SEEK_SET,offset,sizeof(newStudent),getpid()};
        int lockingStatus=fcntl(StudentFileDescriptor,F_SETLKW,&lock);
        if(lockingStatus==-1){
            perror("Error obtaining read lock on Student record");
            return false;
        }
        readBytes=read(StudentFileDescriptor,&prevStudent,sizeof(struct Student));
        if(readBytes==-1){
            perror("Error while reading Student record from file!");
            return false;
        }

        lock.l_type=F_UNLCK;
        fcntl(StudentFileDescriptor,F_SETLK,&lock);

        close(StudentFileDescriptor);
        newStudent.stud_id=prevStudent.stud_id+1;
    
    }
    newStudent.active=1;
    memset(newStudent.courses_ID,-1,30*sizeof(int));
    bzero(writeBuff,sizeof(writeBuff));
    strcpy(writeBuff,ADD_DETAILS);
    strcat(writeBuff,"Enter Student Login ID\n");
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking details!\n");
        return false;
    }
    bzero(readBuff,sizeof(readBuff));
    readBytes=read(connFD,&readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error while reading LOGIN ID from STUDENT");
        return false;
    }
    strcpy(newStudent.login_id,readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    strcpy(writeBuff,USER_NAME);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking user name.");
        return false;
    }
    bzero(readBuff,sizeof(readBuff));
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading User Name from the user");
        return false;
    }
    strcpy(newStudent.name,readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_PASSWORD);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for password.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error while reading password from the User");
        return false;
    }
    strcpy(newStudent.password,readBuff);
    newStudent.pass_modify=0;//this will be changed later by student.
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_AGE);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for user age.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading age from User");
    }
    newStudent.age=atoi(readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_EMAIL);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for Email ID.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading Email from the User.");
    }
    strcpy(newStudent.email_id,readBuff);

    strcpy(newStudent.login_id,newStudent.email_id);



    StudentFileDescriptor=open(STUDENT_FILE,O_CREAT|O_APPEND|O_WRONLY,S_IRWXU);
    if(StudentFileDescriptor==-1){
        perror("Error while creating / opening Student File!");
        return false;
    }
    writeBytes=write(StudentFileDescriptor,&newStudent,sizeof(struct Student));
    if(writeBytes==-1){
        perror("Error while adding Student to the record!");
        return false;
    }
    bzero(writeBuff,sizeof(writeBuff));
    sprintf(writeBuff,"%s%d",STUDENT_ADD_ID,newStudent.stud_id);
    strcat(writeBuff,"\nRedirecting you to the main menu...^");
    writeBytes=write(connFD,writeBuff,sizeof(writeBuff));
    readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
    close(StudentFileDescriptor);
    return true;
}

bool add_faculty(int connFD){
    ssize_t readBytes,writeBytes;
    char readBuff[1000],writeBuff[1000];
    struct Faculty newFaculty,prevFaculty;
    
    int FacultyFileDescriptor=open(FACULTY_FILE,O_RDONLY);
    memset(&newFaculty,0,sizeof(struct Faculty));
    memset(&prevFaculty,0,sizeof(struct Faculty));
    if(FacultyFileDescriptor==-1 && errno==ENOENT){
        newFaculty.faculty_id=0;
    }
    else if(FacultyFileDescriptor==-1){
        perror("Error while opening the Faculty file\n");
        return false;
    }
    else{
        int offset=lseek(FacultyFileDescriptor,-sizeof(struct Faculty),SEEK_END);
        if(offset==-1){
            perror("Error seeking to last Faculty record");
            return false;
        }
        struct flock lock={F_RDLCK,SEEK_SET,offset,sizeof(newFaculty),getpid()};
        int lockingStatus=fcntl(FacultyFileDescriptor,F_SETLKW,&lock);
        if(lockingStatus==-1){
            perror("Error obtaining read lock on Faculty record");
            return false;
        }
        readBytes=read(FacultyFileDescriptor,&prevFaculty,sizeof(struct Faculty));
        if(readBytes==-1){
            perror("Error while reading Faculty record from file!");
            return false;
        }

        lock.l_type=F_UNLCK;
        fcntl(FacultyFileDescriptor,F_SETLK,&lock);

        close(FacultyFileDescriptor);
        newFaculty.faculty_id=prevFaculty.faculty_id+1;
    
    }
    newFaculty.active=true;
    memset(newFaculty.courses_ID,-1,30*sizeof(int));
    bzero(writeBuff,sizeof(writeBuff));
    strcpy(writeBuff,ADD_DETAILS);
    strcat(writeBuff,"Enter Faculty Login ID\n");
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking details!\n");
        return false;
    }
    bzero(readBuff,sizeof(readBuff));
    readBytes=read(connFD,&readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error while reading LOGIN ID from Faculty");
        return false;
    }
    strcpy(newFaculty.login_id,readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    strcpy(writeBuff,USER_NAME);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking user name.");
        return false;
    }
    bzero(readBuff,sizeof(readBuff));
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading User Name from the user");
        return false;
    }
    strcpy(newFaculty.name,readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_PASSWORD);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for password.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error while reading password from the User");
        return false;
    }
    
    
    
    strcpy(newFaculty.password,readBuff);
    //printf("faculty password %s",newFaculty.password);
    newFaculty.pass_modify=0;//this will be changed later.
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_AGE);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for user age.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading age from User");
    }
    newFaculty.age=atoi(readBuff);
    bzero(writeBuff,sizeof(writeBuff));
    bzero(readBuff,sizeof(readBuff));
    strcpy(writeBuff,ENTER_EMAIL);
    writeBytes=write(connFD,writeBuff,strlen(writeBuff));
    if(writeBytes==-1){
        perror("Error asking for Email ID.");
        return false;
    }
    readBytes=read(connFD,readBuff,sizeof(readBuff));
    if(readBytes==-1){
        perror("Error reading Email from the User.");
    }
    strcpy(newFaculty.email_id,readBuff);

    strcpy(newFaculty.login_id,newFaculty.email_id);



    FacultyFileDescriptor=open(FACULTY_FILE,O_CREAT|O_APPEND|O_WRONLY,S_IRWXU);
    if(FacultyFileDescriptor==-1){
        perror("Error while creating / opening faculty File!");
        return false;
    }
    writeBytes=write(FacultyFileDescriptor,&newFaculty,sizeof(struct Faculty));
    if(writeBytes==-1){
        perror("Error while adding Faculty to the record!");
        return false;
    }
    bzero(writeBuff,sizeof(writeBuff));
    sprintf(writeBuff,"%s%d",FACULTY_ADD_ID,newFaculty.faculty_id);
    strcat(writeBuff,"\nRedirecting you to the main menu...^");
    writeBytes=write(connFD,writeBuff,sizeof(writeBuff));
    readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
    bzero(readBuff,sizeof(readBuff));
    close(FacultyFileDescriptor);
    return true;
}


bool update_student(int connFD){
    ssize_t readBytes, writeBytes;
    char readBuff[1000],writeBuff[1000];
    struct Student student;
    int studentID;
    off_t offset;
    int lockingStatus;
    writeBytes=write(connFD,STUDENT_MOD_ID,strlen(STUDENT_MOD_ID));
    if (writeBytes == -1)
    {
        perror("Error while writing STUDENT_MOD_ID message to client!");
        return false;
    }
    bzero(readBuff, sizeof(readBuff));
    readBytes = read(connFD, readBuff , sizeof(readBuff ));
    if (readBytes == -1)
    {
        perror("Error while reading cstudent ID from client!");
        return false;
    }
    studentID=atoi(readBuff);

    int StudentFileDescriptor=open(STUDENT_FILE,O_RDONLY);
    if (StudentFileDescriptor == -1)
    {
        //  File doesn't exist
        bzero(writeBuff, sizeof(writeBuff));
        strcpy(writeBuff, NO_STUDENT_ID);
        strcat(writeBuff, "^");
        writeBytes = write(connFD, writeBuff, strlen(writeBuff));
        if (writeBytes == -1)
        {
            perror("Error while writing NO_STUDENT_ID_ message to client!");
            return false;
        }
        readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
        return false;
    }   
    offset = lseek(StudentFileDescriptor, studentID * sizeof(struct Student), SEEK_SET);
    if (errno == EINVAL)
    {
        // Student record doesn't exist
        bzero(writeBuff, sizeof(writeBuff));
        strcpy(writeBuff, NO_STUDENT_ID);
        strcat(writeBuff, "^");
        writeBytes = write(connFD, writeBuff, strlen(writeBuff));
        if (writeBytes == -1)
        {
            perror("Error while writing NO_CUSTOMER_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required student record!");
        return false;
    }

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Student), getpid()};

    // Lock the record to be read
    lockingStatus = fcntl(StudentFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Couldn't obtain lock on student record!");
        return false;
    }

    readBytes = read(StudentFileDescriptor, &student, sizeof(struct Student));
    if (readBytes == -1)
    {
        perror("Error while reading student record from the file!");
        return false;
    }

    // Unlock the record
    lock.l_type = F_UNLCK;
    fcntl(StudentFileDescriptor, F_SETLK, &lock);

    close(StudentFileDescriptor);

    writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_MENU, strlen(ADMIN_MOD_CUSTOMER_MENU));
    if (writeBytes == -1)
    {
        perror("Error while writing ADMIN_MOD_CUSTOMER_MENU message to client!");
        return false;
    }
    readBytes = read(connFD, readBuff, sizeof(readBuff));
    if (readBytes == -1)
    {
        perror("Error while getting student modification menu choice from client!");
        return false;
    }

    int choice=atoi(readBuff);
    if (choice == 0)
    { // A non-numeric string was passed to atoi
        bzero(writeBuff, sizeof(writeBuff));
        strcpy(writeBuff, ERRON_INPUT_FOR_NUMBER);
        writeBytes = write(connFD, writeBuff, strlen(writeBuff));
        if (writeBytes == -1)
        {
            perror("Error while writing ERRON_INPUT_FOR_NUMBER message to client!");
            return false;
        }
        readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
        return false;
    }
    bzero(readBuff,sizeof(readBuff));

    switch (choice)
    {
    case 1:
        writeBytes = write(connFD, ADMIN_MOD_STUDENT_NEW_NAME, strlen(ADMIN_MOD_STUDENT_NEW_NAME));
        if (writeBytes == -1)
        {
            perror("Error while writing ADMIN_MOD_STUDENT_NEW_NAME message to client!");
            return false;
        }
        readBytes = read(connFD, &readBuff, sizeof(readBuff));
        if (readBytes == -1)
        {
            perror("Error while getting response for Student's new name from client!");
            return false;
        }
        strcpy(student.name, readBuff);
        break;
    case 2:
        writeBytes = write(connFD, ADMIN_MOD_STUDENT_NEW_AGE, strlen(ADMIN_MOD_STUDENT_NEW_AGE));
        if (writeBytes == -1)
        {
            perror("Error while writing ADMIN_MOD_STUDENT_NEW_AGE message to client!");
            return false;
        }
        readBytes = read(connFD, &readBuff, sizeof(readBuff));
        if (readBytes == -1)
        {
            perror("Error while getting response for student's new age from client!");
            return false;
        }
        int updatedAge = atoi(readBuff);
        if (updatedAge == 0)
        {
            // Either client has sent age as 0 (which is invalid) or has entered a non-numeric string
            bzero(writeBuff, sizeof(writeBuff));
            strcpy(writeBuff, ERRON_INPUT_FOR_NUMBER);
            writeBytes = write(connFD, writeBuff, strlen(writeBuff));
            if (writeBytes == -1)
            {
                perror("Error while writing ERRON_INPUT_FOR_NUMBER message to client!");
                return false;
            }
            readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
            return false;
        }
        student.age = updatedAge;
        break;
    case 3:
        writeBytes = write(connFD, ADMIN_MOD_STUDENT_NEW_LOGIN_ID, strlen(ADMIN_MOD_STUDENT_NEW_LOGIN_ID));
        if (writeBytes == -1)
        {
            perror("Error while writing ADMIN_MOD_CUSTOMER_NEW_GENDER message to client!");
            return false;
        }
        readBytes = read(connFD, &readBuff, sizeof(readBuff));
        if (readBytes == -1)
        {
            perror("Error while getting response for student's new gender from client!");
            return false;
        }
        strcpy(student.login_id , readBuff);
        break;
    case 4:
        writeBytes = write(connFD, ADMIN_MOD_STUDENT_NEW_STATUS, strlen(ADMIN_MOD_STUDENT_NEW_STATUS));
        if (writeBytes == -1)
        {
            perror("Error while writing ADMIN_MOD_STUDENT_NEW_STATUS message to client!");
            return false;
        }
        readBytes = read(connFD, &readBuff, sizeof(readBuff));
        if (readBytes == -1)
        {
            perror("Error while getting response for student's new gender from client!");
            return false;
        }

        student.active=atoi(readBuff);
        break;
    default:
        bzero(writeBuff, sizeof(writeBuff));
        strcpy(writeBuff, INVALID_MENU_CHOICE);
        writeBytes = write(connFD, writeBuff, strlen(writeBuff));
        if (writeBytes == -1)
        {
            perror("Error while writing INVALID_MENU_CHOICE message to client!");
            return false;
        }
        readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read
        return false;
    }

    StudentFileDescriptor = open(STUDENT_FILE, O_WRONLY);
    if (StudentFileDescriptor == -1)
    {
        perror("Error while opening student file");
        return false;
    }
    offset = lseek(StudentFileDescriptor, studentID * sizeof(struct Student), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required student record!");
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lockingStatus = fcntl(StudentFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on student record!");
        return false;
    }

    writeBytes = write(StudentFileDescriptor, &student, sizeof(struct Student));
    if (writeBytes == -1)
    {
        perror("Error while writing update student info into file");
    }

    lock.l_type = F_UNLCK;
    fcntl(StudentFileDescriptor, F_SETLKW, &lock);

    close(StudentFileDescriptor);

    writeBytes = write(connFD, ADMIN_MOD_STUDENT_SUCCESS, strlen(ADMIN_MOD_STUDENT_SUCCESS));
    if (writeBytes == -1)
    {
        perror("Error while writing ADMIN_MOD_STUDENT_SUCCESS message to client!");
        return false;
    }
    readBytes = read(connFD, readBuff, sizeof(readBuff)); // Dummy read

    return true;

}


#endif