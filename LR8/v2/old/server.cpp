#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <string.h>
#include <signal.h>

#define mln 1024

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
    int id;
    //int*array;
} message_buf;

int main(int argc, char*argv[]){
    int msqid;
    key_t key;
    message_buf rbuf;

    key = atoi(argv[0]);

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("server::msgget");
        return -1;
    }

    while(true){
        if (msgrcv(msqid, &rbuf, mln + sizeof(int), 1, 0) < 0) {
            perror("server::msgrcv");
            return -1;
        }
        std::cout << "server::" << rbuf.mes << " " << rbuf.id << std::endl;   
        strcpy(rbuf.mes, "response");
        std::cout << "server::" << rbuf.mes << " " << rbuf.id << std::endl;   
        if(msgsnd(msqid, &rbuf, mln + sizeof(int), IPC_NOWAIT) < 0) {        
            std::cerr << "server::msgsnd failed\n";
        }
        kill(rbuf.id, SIGINT);
    }
    return 0;
}
