#include <string.h>
#include <iostream>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MSGSZ 128
#define SIZE 3

typedef struct _msgbuf {
    long mtype;
    char mes[MSGSZ];
    int array[SIZE] = {-3, 5, 2};
} message_buf;

int main(int argc, char*argv[]) {
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;

    key = 11;

    if((msqid = msgget(key, msgflg)) < 0) {
        std::cerr << "msgget failed\n";
        return -1;
    } 
    sbuf.mtype = 2;
    buf_length = (sizeof(int) * SIZE) + MSGSZ;
    strcpy(sbuf.mes, "Message");
    if(msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {        
        std::cerr << "msgsnd failed\n";
        return -1;
    }
    std::cout << sbuf.mes << std::endl;
    for(int i = 0; i < SIZE; ++i) {
        std::cout << sbuf.array[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}