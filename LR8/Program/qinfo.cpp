// Print queue info by key

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

void StatQueue(key_t key){    
    struct msqid_ds qstatus;
    int qid = msgget(key, IPC_CREAT);
    if(qid == -1){
        std::cerr << "msgget failed\n";
        return;
    }
    if(msgctl(qid, IPC_STAT, &qstatus) < 0){
        std::cerr << "msgctl failed\n";
    }
    std::cout << "user id: " << qstatus.msg_perm.cuid << std::endl;
    std::cout << "message queue id: " << qid << std::endl;
    std::cout << "message(s) on queue: " << qstatus.msg_qnum << std::endl;
    std::cout << "last message sent by process " << qstatus.msg_lspid << " at " << ctime(& (qstatus.msg_stime)) << std::endl;
}