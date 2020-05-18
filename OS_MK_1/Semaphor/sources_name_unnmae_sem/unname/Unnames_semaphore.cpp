#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <iostream>

sem_t mutex; 
std::string text;
  
void* thread(void* arg){ 

    //wait 
    sem_wait(&mutex); 
    printf("\nEntered..\n"); 
  
    // do something 
    text = (const char*)arg;
    std::cout << text << std::endl;
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&mutex); 

    return NULL;
} 
  
  
int main(int argc, char*argv[]){ 

    // Initialize an unnamed semaphore
    sem_init(&mutex, 0, 1); 

    // Define two threads
    pthread_t t1,t2; 

    // Create a new thread for task <void* thread(void* arg)>
    pthread_create(&t1, NULL, thread, (void*)"QWERTYUIOP"); 

    // Create a new thread for task <void* thread(void* arg)>
    pthread_create(&t2, NULL, thread, (void*)"asdfghjkl"); 

    // Waiting for the end of the first thread
    pthread_join(t1, NULL); 
    
    // Waiting for the end of the second thread
    pthread_join(t2, NULL); 

    // Destroy semaphore
    sem_destroy(&mutex); 

    return 0; 
} 
