#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
  
sem_t mutex; 
  
void* thread(void* arg){ 

    //wait 
    sem_wait(&mutex); 
    printf("\nEntered..\n"); 
  
    // do something - in example we just waiting 4 seconds
    sleep(4); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&mutex); 
} 
  
  
int main(int argc, char*argv[]){ 

    // Initialize an unnamed semaphore
    sem_init(&mutex, 0, 1); 

    // Define two threads
    pthread_t t1,t2; 

    // Create a new thread for task <void* thread(void* arg)>
    pthread_create(&t1, NULL, thread, NULL); 

    sleep(2); 

    // Create a new thread for task <void* thread(void* arg)>
    pthread_create(&t2, NULL, thread, NULL); 

    // Waiting for the end of the first thread
    pthread_join(t1, NULL); 
    
    // Waiting for the end of the second thread
    pthread_join(t2, NULL); 

    // Destroy semaphore
    sem_destroy(&mutex); 

    return 0; 
} 
