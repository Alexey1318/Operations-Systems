#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[]) {
    
    // For pull info about queue
    struct msqid_ds qstatus;
    
    // Define variables for work with queue
    key_t key = atoi(argv[1]);   
    int msqid;

    // Connect to the queue
    msqid = msgget(key, IPC_CREAT);
    if (msqid == -1) {
        perror("serv::msgget");
        return -1;
    }

    while(true){
        // Get info and write it in object qstatus
        if(msgctl(msqid, IPC_STAT, &qstatus) < 0){
            perror("msgctl");
            return -1;
        }
        printf("msqid: %d\tmessage(s) in queue: %d\ttime of last message:%s\n",
         msqid, 
         qstatus.msg_qnum, 
         ctime(&(qstatus.msg_ctime)));
        sleep(5);
    }

    return 0;
}