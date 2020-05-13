#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>

#define mln 1024

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
} message_buf;

int main (int argc, char*argv[]){

    using namespace std;
 
    // Объявление необходимых переменных    
    int msqid;
    message_buf rbuf;
    key_t key = atoi(argv[1]);

    // Подключение к очереди
    if ((msqid = msgget(key, 0666|IPC_CREAT)) < 0) {
        perror("serv::msgget");
        return -1;
    }
    
    while(true){
        // Изъятие сообщения из очереди
        if (msgrcv(msqid, &rbuf, mln, 2, 0) < 0) {
            perror("serv::msgrcv");
            return -1;
        }

        // Вывод полученного текста на экран
        cout << "serv::" << rbuf.mes << "\t";
        cout << rbuf.mtype << "\t";
        cout << msqid << "\t";
        cout << mln << endl;   
            
        // Запись ответа на запрос
        strcpy(rbuf.mes, "response"); 

        cout << "serv::" << rbuf.mes << "\t";
        cout << rbuf.mtype << "\t";
        cout << msqid << "\t";
        cout << mln << endl;    

        // Отправка сообщения с ответом
        rbuf.mtype = 1;
        if(msgsnd(msqid, &rbuf, mln, IPC_NOWAIT) < 0) {        
            perror("serv::msgsnd failed");
            return -1;
        }

        sleep(3);
    }
    return 0;
}