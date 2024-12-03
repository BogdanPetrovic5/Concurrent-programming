#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct Message{
    long messageType;
    char message[100];
}Message;

int main(){
   
    key_t KEY;
    pid_t pid;
    int rowID;
    KEY = ftok("./chat.c", 65);
   

    rowID = msgget(KEY, IPC_CREAT | 0666);
    if(rowID == -1){
        perror("Error while creating row of messages!");
    }

    pid = fork();
    if(pid < 0){
        perror("Error while creating fork!");
        exit(1);
    }

    
    while(1){
        if(pid == 0){
            Message message;
    
            msgrcv(rowID, &message, sizeof(message),1, 0);
            printf("Message received from parent: %s", message.message);

            printf("Enter child message: ");
            message.messageType = 2;
            fgets(message.message, sizeof(message.message), stdin);
            if(strcmp(message.message, "stop\n")==0){
                pid_t parentPid = getppid();
                msgctl(rowID, IPC_RMID, NULL);
                fflush(stdin);
                kill(parentPid, SIGKILL);
                exit(0);
            }
            msgsnd(rowID, &message,sizeof(message), 0);
        }else{
            Message message;
            
            printf("Enter parent message: ");
            message.messageType = 1;
            fgets(message.message, sizeof(message.message), stdin);
            if(strcmp(message.message, "stop\n")==0){
            msgctl(rowID, IPC_RMID, NULL);
                fflush(stdin);
                kill(pid, SIGKILL);   
                msgctl(rowID, IPC_RMID, NULL);             
                exit(0);
            }
            msgsnd(rowID, &message,sizeof(message), 0);

            msgrcv(rowID, &message, sizeof(message), 2, 0);
            printf("Message received from child: %s", message.message);
        }
    }
     
}