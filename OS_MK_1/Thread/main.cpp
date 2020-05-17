#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
int main(int argc, char*argv[]){
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;
    int file = creat("Threads.txt", mode);
    int pid,*tpid;
    for(int count = 0; count < atoi(argv[1]); ++count){
        pid = fork();        
        if(pid == 0){
            execl("./thread", "Threads.txt", "I'm thread #", std::to_string(count).c_str(), "\n", NULL);
        }        
        tpid = new int(pid);
        wait(tpid);
    }
    return 0;
}