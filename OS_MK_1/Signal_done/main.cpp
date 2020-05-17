#include <unistd.h>
#include <csignal>
#include <iostream>
void Catch(int signum){
    std::cout << "Catch signal from child\n";
    exit(signum);
}
int main(int argc, char*argv[]){
    signal(SIGALRM, Catch);
    int pid = fork();
    if(pid == 0){
        execl("./catch", NULL);
    }
    sleep(3);
    kill(pid, SIGINT);
    for(int i = 1;;++i){
        std::cout << "Wait for child signal " << i << " seconds\n";
        sleep(1);
    }
    return 0;
}