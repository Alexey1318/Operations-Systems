#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <csignal>

#define mln 1024

std::string commands[3] = {"sort", "line", "stat"};
key_t gkey;

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
    int id;
    //int *array;
} message_buf;

// Перенеси это в серверную часть
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

// Обработчик полученного сигнала
void SignalProcessed(int ad){
    int msqid;
    message_buf rbuf;
    if ((msqid = msgget(gkey, 0666)) < 0) {
        perror("client::msgget");
        return;
    }
    if (msgrcv(msqid, &rbuf, mln + sizeof(int), 1, 0) < 0) {
        perror("client::msgrcv");
        return;
    }
    std::cout << "client::" << rbuf.mes << std::endl;
    return;
}

int main(int argc, char*argv[]){
    signal(SIGINT, SignalProcessed);

// 1. Объявляем вспомогательные переменные
    /*
     * id очереди, 
     * флаги доступа - создать очередь, если ее не существует и дать доступ на чтение-запись всем пользователям,
     * ключ 
     * буфер для отправки сообщения и его длину
    */
    int msqid;
    int msflg = IPC_CREAT | 0666;
    message_buf sbuf;
    size_t bln;

// 2. Создаем очередь или подключаемся к уже существующей
    gkey = atoi(argv[0]);
    if((msqid = msgget(gkey, msflg)) < 0){
        std::cerr << "client::msgget error\n";
        return -1;
    }
    sbuf.mtype = 1;

// 3. В зависимости от указанной пользователем команды 
//      отправляем запрос на обработку массива, строки или показ статистики
    std::string com;
    while (true)
    {  
        std::cout << "client::command ";
        std::cin >> com;
        if(strncmp(com.c_str(), commands[0].c_str(), commands[0].length()) == 0){
            /*sbuf.array = new int[5] {-3, 1, -4, 5, 3};
            bln = mln + 5 * sizeof(int);
            if(msgsnd(msqid, &sbuf, bln, IPC_NOWAIT) < 0) {        
                std::cerr << "1msgsnd failed\n";
            }*/
        } 
        if(strncmp(com.c_str(), commands[1].c_str(), commands[1].length()) == 0){
            std::cin >> com;
            strcpy(sbuf.mes, com.c_str());
            sbuf.id = getpid();
            bln = mln + sizeof(int);// + sizeof(int);
            if(msgsnd(msqid, &sbuf, bln, IPC_NOWAIT) < 0) {        
                std::cerr << "client::msgsnd failed\n";
            }
        } 
        if(strncmp(com.c_str(), commands[2].c_str(), commands[2].length()) == 0){
            StatQueue(1);
        }
        if(strcmp(com.c_str(), "exit") == 0){
            break;
        }
        std::cout << std::endl;
    }    
//----------------------------------------------------------------------------
    return 0;
}