#include <sys/sem.h>
#include <sys/ipc.h>
#include <iostream>

int main(int argc, char*argv[]){
    
    key_t key;
    int semid;

    // To create a System V semaphore we need a System V IPC key;
    // Create the key with the ftok()
    key = ftok(".", 's');

    return 0;
}