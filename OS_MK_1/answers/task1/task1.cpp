/* 
 * Hаписати програму, яка створює дочірні процеси (системний виклик fork ()), 
 * стежить за їх завершенням (сигнал SIGCHLD) 
 * і кожен раз при створенні або завершенні дочірніх процесів 
 * виводить їх поточну кількість на екран.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char*argv[]){
    int pid;
    pid = fork();
    if(pid == 0){
        // Child
        
    }
}
