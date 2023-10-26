// Name : 27_.c
// Author : Shivam Jaiswal
// Description :Write a program to receive messages from the message queue.
 //a. with 0 as a flag
 //b. with IPC_NOWAIT as a flag



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

    // Generate the same key used in the sender program
    key = ftok("/tmp", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Open the message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive messages from the queue with flag 0
    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) { //The message type (positive integer) to receive. In this case, it's set to 1.
            perror("msgrcv");
            exit(1);
        }

        printf("Received message: %s", msg.msg_text);

        if (strncmp(msg.msg_text, "exit", 4) == 0) {
            break;
        }
    }

    return 0;
}

