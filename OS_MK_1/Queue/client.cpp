#include "include.h"

int main(int argc, char*argv[]){

    using namespace std;

    // Объявление необходимых переменных
    key_t key = atoi(argv[1]);
    int msqid;

    message_buf smbuf;
    stat_info sibaf;

    // Подключение к очереди
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("client::msgget");
        return -1;
    }

    int choice;
    while(true){
        cin >> choice;
        switch(choice){
            case 1:
                // Отправка сообщения на сервер
                smbuf.mtype = 2;
                strcpy(smbuf.mes, "request");
                Push::Send(smbuf, msqid);
                // Изъятие сообщения из очереди
                Pop::Get(smbuf, msqid, 1, 0);
                // Вывод полученного cообщения на экран
                Print::Show(smbuf);
            break;
                
            case 2:
                // Запрос на получение статистики
                sibaf.mtype = 6;
                Push::Send(sibaf, msqid);
                // Изъятие сообщения из очереди
                Pop::Get(sibaf, msqid, 5, 0);
                // Вывод полученного cообщения на экран
                Print::Show(sibaf);
            break;

            case -1:
                return 0;
        }
    }
}