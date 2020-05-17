#include "include.h"

int main(int argc, char*argv[]){
    // Объявление необходимых переменных 
    key_t key = atoi(argv[1]);   
    int msqid; 

    struct msqid_ds qstatus;

    message_buf rmbuf;
    stat_info ribuf;

    // Подключение к очереди
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("serv::msgget");
        return -1;
    }

    while(true){
        // Изъятие сообщения из очереди
        if(Pop::Get(rmbuf, msqid, 2, IPC_NOWAIT) == 0){
            Print::Show(rmbuf);
            // Запись ответа на запрос
            rmbuf.mtype = 1;
            strcpy(rmbuf.mes, "response");
            // Отправка сообщения с ответом
            Push::Send(rmbuf, msqid);
        }

        // Изъятие сообщения из очереди
        if(Pop::Get(ribuf, msqid, 6, IPC_NOWAIT) == 0){
            
            if(!(msgctl(msqid, IPC_STAT, &qstatus) < 0)){

                ribuf.mtype = 5;

                // Сбор статистики
                ribuf.msqid = msqid;
                ribuf.user_id = qstatus.msg_perm.cuid;
                ribuf.mes_count = qstatus.msg_qnum;
                strcpy(ribuf.time_last_request, ctime(& (qstatus.msg_stime)));

                // Отправка сообщения с ответом
                Push::Send(ribuf, msqid);
            }
        }
    }

    return 0;
}