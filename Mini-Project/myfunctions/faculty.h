#ifndef FACULTY_FUNCTIONS
#define FACULTY_FUNCTIONS
#include "./common.h"
#include <sys/ipc.h>
#include <sys/sem.h>

struct Faculty loggedInFaculty;
int semIdentifier;

//Functions
bool faculty_handler(int connFD);
bool lock_critical_section(struct sembuf *semOp);
bool unlock_critical_section(struct sembuf *sem_op);


bool faculty_handler(int connFD){
    if(login_handler(1,connFD,NULL,&loggedInFaculty)){
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        // Get a semaphore for the user
        key_t semKey = ftok(FACULTY_FILE, loggedInFaculty.faculty_id); // Generate a key based on the faculty ID hence, different faculty will have different semaphores
        printf("%d faculty id\n",loggedInFaculty.faculty_id);
        
        union semun
        {
            int val; // Value of the semaphore
        } semSet;

        int semctlStatus;
        semIdentifier = semget(semKey, 1, 0); // Get the semaphore if it exists
        if (semIdentifier == -1)
        {
            semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create a new semaphore
            if (semIdentifier == -1)
            {
                perror("Error while creating semaphore!");
                _exit(1);
            }

            semSet.val = 1; // Set a binary semaphore
            semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
            if (semctlStatus == -1)
            {
                perror("Error while initializing a binary sempahore!");
                _exit(1);
            }
        }

        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, FACULTY_LOGIN_SUCCESS);
        while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, FACULTY_MENU);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
            if (writeBytes == -1)
            {
                perror("Error while writing CUSTOMER_MENU to client!");
                return false;
            }
            bzero(writeBuffer, sizeof(writeBuffer));

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for CUSTOMER_MENU");
                return false;
            }
            
            // printf("READ BUFFER : %s\n", readBuffer);
            int choice = atoi(readBuffer);
            // printf("CHOICE : %d\n", choice);
            switch (choice)
            {
            case 1:
                //add_course(connFD);
                break;
            case 2:
                //remove_course(connFD);
                break;
            case 3:
                //view_course_details(connFD);
                break;
            case 4:
                //password_change(connFD);
                break;            
            default:
                writeBytes = write(connFD, FACULTY_LOGOUT, strlen(FACULTY_LOGOUT));
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool lock_critical_section(struct sembuf *semOp)
{
    semOp->sem_flg = SEM_UNDO;
    semOp->sem_op = -1;
    semOp->sem_num = 0;
    int semopStatus = semop(semIdentifier, semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while locking critical section");
        return false;
    }
    return true;
}

bool unlock_critical_section(struct sembuf *semOp)
{
    semOp->sem_op = 1;
    int semopStatus = semop(semIdentifier, semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    return true;
}

// bool add_courses(int connFD){

// }

#endif