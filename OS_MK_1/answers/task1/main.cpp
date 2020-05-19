/* 
 * Hаписати програму, яка створює дочірні процеси (системний виклик fork ()), 
 * стежить за їх завершенням (сигнал SIGCHLD) 
 * і кожен раз при створенні або завершенні дочірніх процесів 
 * виводить їх поточну кількість на екран.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int count = 0;

int main(int argc, const char** argv) {
    
    int pid;
    
    for(int i = 0; i < atoi(argv[1]); ++i){
        
        pid = fork();
        
        switch(pid){

            case 0:
                printf("Child: parent pid=%d, pid=%d\n", getppid(), getpid());
                kill(getppid(), SIGCHLD);
            break;

            default:
                ++count;
                printf("Parent: pid=%d, child pid=%d\n", getpid(), pid);
                printf("Parent pid=%d: after creating a new process: process count = %d\n", getpid(), count);
                
                waitpid(pid, NULL, 0);
                --count;
                printf("Parent pid=%d: after kill a child: process count = %d\n", getpid(), count);
            break;
        }
    }

    return 0;
}

