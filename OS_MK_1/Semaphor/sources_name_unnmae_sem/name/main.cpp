#include "include.h"
#include <cstring>

int main(int argc, char*argv[]){
 
    printf("Process ID: %d\n", getpid());

    // Unlink existing semaphore
    sem_unlink(SEMAPHORE_NAME);

    // Open it (or create)
    mySem = sem_open(SEMAPHORE_NAME, O_CREAT, 0777, 0);
    if(mySem == SEM_FAILED){
        perror("sem_open");
        return -1;
    }

    // Define thread for writing data 
    pthread_t tWrite;

    // Open semaphore before the thread going to starting
    sem_post(mySem);

    // Show value of the used semaphore
    int v;
    sem_getvalue(mySem, &v);
    printf("Value of semaphore: %d\n", v);

    // Create a new thread 
    pthread_create(&tWrite, NULL, Write, (void*)"Hello!");

    // Waiting for the end of the thread write
    pthread_join(tWrite, NULL);

    // Close semaphore
    sem_close(mySem);

    return 0;
}