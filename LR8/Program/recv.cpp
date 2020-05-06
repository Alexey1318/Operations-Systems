#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <string.h>

#define MSGSZ 128
#define SIZE 5

typedef struct _msgbuf {
    long mtype;
    char mes[MSGSZ];
    int array[SIZE];
} message_buf;

int main(int argc, char*argv[]) {
    int msqid;
    key_t key;
    message_buf rbuf;

    key = atoi(argv[1]);

    if((msqid = msgget(key, 0666)) < 0) {
        std::cerr << "msgget failed\n";
        return -1;
    }

    rbuf.mtype = 1;

    int buf_length = (sizeof(int) * SIZE) + MSGSZ;

    if(msgrcv(msqid, &rbuf, buf_length, rbuf.mtype, 0) < 0) {  
        std::cerr << "msgrecv failed\n";
        return -1;
    } else {
        std::cout << rbuf.mes << std::endl;
        for(int i = 0; i < SIZE; ++i) {
            std::cout << rbuf.array[i] << " ";
        } 
        std::cout << std::endl;
    }
    return 0;
}
