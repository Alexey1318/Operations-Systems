#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>

#define mln 1024

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
    int id;
} message_buf;

int main (int argc, char*argv[]){
 
    // Объявление необходимых переменных    
    int msqid;
    message_buf rbuf;
    key_t key = atoi(argv[0]);

    // Подключение к очереди
    if ((msqid = msgget(key, 0666|IPC_CREAT)) < 0) {
        perror("serv::msgget");
        return -1;
    }
    rbuf.mtype = 1;

    //while(true){
        // Изъятие сообщения из очереди
        if (msgrcv(msqid, &rbuf, sizeof(int) + mln, 1, 0) < 0) {
            perror("serv::msgrcv");
            return -1;
        }

        // Вывод полученного текста на экран
        std::cout << "serv::" << rbuf.mes << " " << rbuf.id << std::endl;   

        // Запись ответа на запрос
        strcpy(rbuf.mes, "response"); 

        // Отправка сообщения с ответом
        if(msgsnd(msqid, &rbuf, mln + sizeof(int), IPC_NOWAIT) < 0) {        
            std::cerr << "serv::msgsnd failed\n";
        }

        // Отправка сигнала об обработанном запросе
        kill(rbuf.id, SIGINT);
    //}

    return 0;
}