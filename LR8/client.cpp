#include "include.h"

int main(int argc, char* argv[]){

    // Объявление необходимых переменных
    key_t key = atoi(argv[1]);
    int msqid;

    message_buf smbuf;
    array_buf sabuf;

    // Подключение к очереди
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("clie::msgget");
        return -1;
    }
    std::cout << "Connect to queue success" << std::endl;
    
    // Отправка сообщения на сервер
    smbuf.mtype = 2;
    strcpy(smbuf.mes, "request");
    if(msgsnd(msqid, &smbuf, mbufsize, IPC_NOWAIT) < 0) {        
        perror("clie::msgsnd failed");
        return -1;
    }
    std::cout << "Send message to queue success" << std::endl;

    sabuf.mtype = 4;
    for(int i = 0; i < aln; ++i){ sabuf.array[i] = i; }    
    if(msgsnd(msqid, &sabuf, abufsize, IPC_NOWAIT) < 0) {        
        perror("clie::msgsnd failed");
        return -1;
    }
    std::cout << "Send array to queue success" << std::endl;

    // Изъятие сообщения из очереди
    if (msgrcv(msqid, &smbuf, mbufsize, 1, 0) < 0) {
        perror("clie::msgrcv");
        return -1;
    }
    std::cout << "Get message from queue success" << std::endl;

    if (msgrcv(msqid, &sabuf, abufsize, 3, 0) < 0) {
        perror("clie::msgrcv");
        return -1;
    }
    std::cout << "Get array from queue success" << std::endl;

    // Вывод полученного текста на экран
    Show(smbuf); 
    Show(sabuf);

    sleep(3);

    return 0;
}