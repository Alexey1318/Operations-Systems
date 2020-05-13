#include "include.cpp"

int main(int argc, char*argv[]){

    // Объявление необходимых переменных    
    int msqid; 
    message_buf rbuf;
    key_t key = atoi(argv[1]);

    int bufsize = mln + sizeof(int)*11;

    // Подключение к очереди
    if ((msqid = msgget(key, 0666|IPC_CREAT)) < 0) {
        perror("serv::msgget");
        return -1;
    }

    // Изъятие сообщения из очереди
    if (msgrcv(msqid, &rbuf, bufsize, 2, 0) < 0) {
        perror("serv::msgrcv");
        return -1;
    }
    
    Show(rbuf);
    
    // Запись ответа на запрос
    strcpy(rbuf.mes, "response");
    for(int i = 0; i < 10; ++i) rbuf.array[i] *= -1;

    // Отправка сообщения с ответом
    rbuf.mtype = 1;
    if(msgsnd(msqid, &rbuf, bufsize, IPC_NOWAIT) < 0) {        
        perror("serv::msgsnd failed");
        return -1;
    }

    sleep(3);    

    return 0;
}