#include <unistd.h>
#include <stdio.h>
int main(int argc, char*argv[]){
    int pid = fork();
    switch(pid){
        case 0:
        // do something in child process 
        printf("Child: parent pid=%d, pid=%d\n", getppid(), getpid());
        break;
        default:
        // do something in parent
        printf("Parent: pid=%d, child pid=%d\n", getpid(), pid);
        break;
    }
    return 0;
}
