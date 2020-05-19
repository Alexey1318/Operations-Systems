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

// Creating a signal handler
void CatchSignal(int signum){
    // In the handler we decrease the counter
    --count;
    printf("Parent pid=%d: after kill a child: process count = %d\n", getpid(), count);
    exit(signum);
}

int main(int argc, const char** argv) {
    
    // Handler reference for signal type
    signal(SIGCHLD, CatchSignal);

    pid_t pid;
    
    for(int i = 0; i < atoi(argv[1]); ++i){
        
        // Creating a new process
        pid = fork();
        
        if(pid == 0){
            // Starting in the process of another application
            execl("./child", NULL);
        }

        // In the parent process we increase the counter
        ++count;
        printf("Parent: pid=%d, child pid=%d\n", getpid(), pid);
        printf("Parent pid=%d: after creating a new process: process count = %d\n", getpid(), count);   

        sleep(3);
    }

    return 0;
}

