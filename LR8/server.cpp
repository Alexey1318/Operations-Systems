#include "include.h"

int main(int argc, char*argv[]){

    // Объявление необходимых переменных 
    key_t key = atoi(argv[1]);   
    int msqid; 

    message_buf rmbuf;
    array_buf rabuf;    

    // Подключение к очереди
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("serv::msgget");
        return -1;
    }
    std::cout << "Connect to queue success" << std::endl;

    // Изъятие сообщения из очереди
    if (msgrcv(msqid, &rmbuf, mbufsize, 2, 0) < 0) {
        perror("serv::msgrcv");
        return -1;
    }
    std::cout << "Get message from queue success" << std::endl;

    if (msgrcv(msqid, &rabuf, abufsize, 4, 0) < 0) {
        perror("serv::msgrcv");
        return -1;
    }
    std::cout << "Get array from queue success" << std::endl;

    Show(rmbuf);
    Show(rabuf);
    
    // Запись ответа на запрос
    strcpy(rmbuf.mes, "response");
    for(int i = 0; i < aln; ++i){ rabuf.array[i] *= -1; } 

    // Отправка сообщения с ответом
    rmbuf.mtype = 1;
    if(msgsnd(msqid, &rmbuf, mbufsize, IPC_NOWAIT) < 0) {        
        perror("serv::msgsnd failed");
        return -1;
    }
    std::cout << "Send message to queue success" << std::endl;

    rabuf.mtype = 3;
    if(msgsnd(msqid, &rabuf, abufsize, IPC_NOWAIT) < 0) {        
        perror("serv::msgsnd failed");
        return -1;
    }
    std::cout << "Send array to queue success" << std::endl;

    sleep(3);    

    return 0;
}