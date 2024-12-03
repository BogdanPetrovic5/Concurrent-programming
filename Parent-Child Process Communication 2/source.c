#include <stdio.h> 
#include <stdlib.h>
#include <signal.h> 
#include <wait.h>
#include <unistd.h>

pid_t pid_child;
int number = 0;

void parentProccess(){
    while(1){
        int randomNumber = rand() % 10;
        
        if(randomNumber % 2 == 0){
            kill(pid_child, SIGINT);
        }else if(randomNumber % 2 != 0){
            kill(pid_child, SIGCHLD);
        }else if(randomNumber == 0){
            kill(pid_child, SIGFPE);
        }
        sleep(6);
        
    }
}
void signal_handler(int signal){
    if(signal == SIGINT){
        number += 1;
        printf("Number increased!\n");
    }else if(signal == SIGCHLD){
        number -= 1;
        printf("Number decreased\n");
    }else if(signal == SIGFPE){
        printf("Task finished!\n");
        printf("%d\n", number);
        exit(0);
    }
}
void childProccess(){
    signal(SIGINT, signal_handler);
    signal(SIGCHLD, signal_handler);
    signal(SIGFPE, signal_handler);

    while(1){
        printf("I'm the child with PID: %d\n", getpid());
        sleep(3);
    }
}
int main(){
    pid_child = fork();

    if(pid_child < 0){
        perror("Error while creating a fork!");
        exit(1);
    }

    if(pid_child){
        parentProccess();
    }else{
        childProccess();
    }

    printf("%d\n", number);
}