#include "includes.h"

int main(int argc, const char** argv) {

    // Define variables for queue work
    key_t key = atoi(argv[0]);
    int msqid;
    message_buf smbuf;

    // Connect to the queue
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("client::msgget");
        return -1;
    }
    std::cout << "Client #1 connected" << std::endl;
    while(true){
        // Send message to the server
        smbuf.mtype = 2;
        strcpy(smbuf.mes, "request");
        Push::Send(smbuf, msqid);
        // Get response
        Pop::Get(smbuf, msqid, 1, 0);
        // Show it
        Print::Show(smbuf);

        sleep(3);
    }
    return 0;
}