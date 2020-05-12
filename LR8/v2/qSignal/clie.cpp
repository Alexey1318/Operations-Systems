#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <signal.h>
#include <cstring>
#include <unistd.h>

#define mln 1024

bool f;
key_t key;

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
    int id;
} message_buf;

// Обработчик полученного сигнала
void SignalProc(int p){
    int msqid;
    message_buf rbuf;
    // Подключение к очереди
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("clie::msgget");
        return;
    }
    // Изъятие сообщения из очереди
    if (msgrcv(msqid, &rbuf, sizeof(int) + mln, 1, 0) < 0) {
        perror("clie::msgrcv");
        return;
    }
    // Вывод полученного текста на экран
    std::cout << "clie::" << rbuf.mes << " " << rbuf.id << std::endl;
}

int main (int argc, char*argv[]){

    // Установка обработчика сигналов
    signal(SIGINT, SignalProc);

    // Объявление необходимых переменных
    key = atoi(argv[0]);
    int msqid;
    message_buf sbuf;

    // Подключение к очереди
    if ((msqid = msgget(key, 0666|IPC_CREAT)) < 0) {
        perror("clie::msgget");
        return -1;
    }
    sbuf.mtype = 1;
    
    //while (true) {
        // Отправка сообщения на сервер
        strcpy(sbuf.mes, "request");
        sbuf.id = getpid();
        if(msgsnd(msqid, &sbuf, mln + sizeof(int), IPC_NOWAIT) < 0) {        
            std::cerr << "clie::msgsnd failed\n";
        }
        //sleep(5);
    //}
    sleep(5);

    return 0;
}