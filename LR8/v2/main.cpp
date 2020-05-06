#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char*argv[]){
    const char* arg = "1"; // Number of queue
    int pid = fork();
    if(pid == 0){
        // start server part 
        // sending signal about ending task process
        execl("./server", NULL);
    }
    // start client app wath sending messages into queue
    execl("./client", arg, NULL);

    return 0;
}