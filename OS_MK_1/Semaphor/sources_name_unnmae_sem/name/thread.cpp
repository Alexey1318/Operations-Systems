#include "include.h"

int main(int argc, char*argv[]){

    printf("Process ID: %d\n", getpid());

    pthread_t tWrite;

    // Open (not create!) the existing semaphore
    mySem = sem_open(SEMAPHORE_NAME, 0);
    if(mySem == SEM_FAILED){
        perror("sem_open");
        return -1;
    }

    // Show value of the used semaphore
    int v;
    sem_getvalue(mySem, &v);
    printf("Value of semaphore: %d\n", v);

    // Create and run new thread
    pthread_create(&tWrite, NULL, Write, (void*)"Goodbye!");

    // Waiting for the end of the thread write 
    pthread_join(tWrite, NULL);

    // Close semaphore
    sem_close(mySem);

    return 0;
}