#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <iostream>

#define SEMAPHORE_NAME "/my_named_semaphore"

std::string text;
sem_t *mySem;

void* Write(void *arg){

    // Close semaphore for access
    sem_wait(mySem); 
    std::cout << "Semaphore closed" << std::endl;

    // Show value of the used semaphore
    int v;
    sem_getvalue(mySem, &v);
    printf("Value of semaphore: %d\n", v);

    text = (const char*)arg;
    std::cout << text << std::endl;

    // Open semaphore for access
    sem_post(mySem); 
    std::cout << "Semaphore opened" << std::endl;

    return NULL;
}
