#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <signal.h>
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
    key_t key = atoi(argv[1]);
    int msqid;
    message_buf sbuf;

    // Подключение к очереди
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("clie::msgget");
        return -1;
    }
    
    while(true){    
        strcpy(sbuf.mes, "request");
    
        cout << "clie::" << sbuf.mes << "\t";
        cout << sbuf.mtype << "\t";
        cout << msqid << "\t";
        cout << mln << endl;  

        // Отправка сообщения на сервер
        sbuf.mtype = 2;
        if(msgsnd(msqid, &sbuf, mln, IPC_NOWAIT) < 0) {        
            perror("clie::msgsnd failed");
            return -1;
        }

        // Изъятие сообщения из очереди
        if (msgrcv(msqid, &sbuf, mln, 1, 0) < 0) {
            perror("clie::msgrcv");
            return -1;
        }

        // Вывод полученного текста на экран
        cout << "clie::" << sbuf.mes << "\t";
        cout << sbuf.mtype << "\t";
        cout << msqid << "\t";
        cout << mln << endl;      

        sleep(3);
    }

    return 0;
}