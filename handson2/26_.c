// Name : 26_.c
// Author : Shivam Jaiswal
// Description :Write a program to send messages to the message queue. Check $ipcs -q


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MSG_SIZE 1024

// Define a structure for the message
struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer msg;
    
    // Generate a unique key for the message queue
    key = ftok("/tmp", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or open the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Send messages to the message queue
    while (1) {
        printf("Enter a message to send to the queue (or type 'exit' to quit): ");
        fgets(msg.msg_text, MAX_MSG_SIZE, stdin);
        msg.msg_type = 1; // Message type can be any positive integer

        // Send the message to the queue
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        if (strncmp(msg.msg_text, "exit", 4) == 0) {
            break;
        }
    }

    // Display information about the message queue using `ipcs -q`
    system("ipcs -q");

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}

