#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
int main (int argc, char*argv[]){
    if(fork() == 0){
        execl("./serv", argv[1], NULL);        
    }
    execl("./clie", argv[1], NULL);
    return 0;
}