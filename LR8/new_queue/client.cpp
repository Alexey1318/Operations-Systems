#include "include.cpp"

int main(int argc, char* argv[]){

    // Объявление необходимых переменных
    key_t key = atoi(argv[1]);
    int msqid;
    message_buf sbuf;
    int bufsize = mln + sizeof(int) * 11;

    // Подключение к очереди
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("clie::msgget");
        return -1;
    }

    strcpy(sbuf.mes, "request");
    for(int i = 0; i < 10; ++i) sbuf.array[i] = i;

    // Отправка сообщения на сервер
    sbuf.mtype = 2;
    if(msgsnd(msqid, &sbuf, bufsize, IPC_NOWAIT) < 0) {        
        perror("clie::msgsnd failed");
        return -1;
    }

    // Изъятие сообщения из очереди
    if (msgrcv(msqid, &sbuf, bufsize, 1, 0) < 0) {
        perror("clie::msgrcv");
        return -1;
    }

    // Вывод полученного текста на экран
    Show(sbuf); 

    sleep(3);

    return 0;
}