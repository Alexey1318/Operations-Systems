#include <unistd.h>
#include <csignal>
#include <iostream>
void SignalCatch(int signum){
    std::cout << "Catch signal #" << signum << std::endl;
    kill(getppid(),SIGALRM);
    exit(signum);
}
int main(int argc, char*argv[]){
    signal(SIGINT, SignalCatch);
    for(int i = 1; ; ++i){
        std::cout << "Wait for signal " << i << " seconds\n";
        sleep(1);
    }
    return 0;
}