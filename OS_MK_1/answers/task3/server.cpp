/* 
 * Написати програму, яка створює дочірні потоки, 
 * які в паралельному режимі відправляють батьківському потоку повідомлення в чергу повідомлень 
 * і отримують свою персональну відповідь. 
 * Використовувати загальну на всі потоки чергу повідомлень.
 */

#include "includes.h"
#include <vector>
#include <algorithm>

int main(int argc, const char** argv) {
    
    int pid;

    // Define variables for work with queue
    key_t key = atoi(argv[1]);   
    int msqid; 

    // For pull info about queue
    struct msqid_ds qstatus;

    // First thread send ang give text message
    message_buf rmbuf;
    // Second thread send array and give sorted array
    array_buf rabuf;    
    //Third thread send request for issuing info about queue and got it
    stat_info ribuf;

    // Create and run 3 threads
    if((pid = fork()) == 0){
        execl("./client_m", argv[1], NULL);
    }
    else if((pid = fork()) == 0){
        execl("./client_a", argv[1], NULL);
    }
    else if((pid = fork()) == 0){
        execl("./client_s", argv[1], NULL);
    }
    else{
        // Connect to the queue
        if ((msqid = msgget(key, FLAG)) < 0) {
            perror("serv::msgget");
            return -1;
        }
        std::cout << "Server connected to queue" << std::endl;

        while(true){
            // Get message from queue
            if(Pop::Get(rmbuf, msqid, 2, IPC_NOWAIT) == 0){
                Print::Show(rmbuf);
                // Write answer 
                rmbuf.mtype = 1;
                strcpy(rmbuf.mes, "response");
                // Send it
                Push::Send(rmbuf, msqid);
            }

            // Get array
            if(Pop::Get(rabuf, msqid, 4, IPC_NOWAIT) == 0){
                Print::Show(rabuf);
                // Sort array
                rabuf.mtype = 3;
                {
                    std::vector<int> array(rabuf.array, rabuf.array + aln);
                    std::sort(array.begin(), array.end());
                    for(int i = 0; i < aln; ++i){
                        rabuf.array[i] = array[i];
                    }
                }
                // Send it
                Push::Send(rabuf, msqid);
            }

            // Get request 
            if(Pop::Get(ribuf, msqid, 6, IPC_NOWAIT) == 0){
            
                if(!(msgctl(msqid, IPC_STAT, &qstatus) < 0)){

                    ribuf.mtype = 5;

                    // Loot statistics
                    ribuf.msqid = msqid;
                    ribuf.user_id = qstatus.msg_perm.cuid;
                    ribuf.mes_count = qstatus.msg_qnum;
                    strcpy(ribuf.time_last_request, ctime(& (qstatus.msg_stime)));

                    // Send it
                    Push::Send(ribuf, msqid);
                }
            }
        }
    }
    return 0;
}