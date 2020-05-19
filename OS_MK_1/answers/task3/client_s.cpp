#include "includes.h"

int main(int argc, const char** argv) {

    using namespace std;
    srand(time(NULL));

    // Define variables for queue work
    key_t key = atoi(argv[0]);
    int msqid;
    stat_info sibuf;

    // Connect to the queue
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("client::msgget");
        return -1;
    }
    std::cout << "Client #3 connected" << std::endl;
    while (true){
        // Send request
        sibuf.mtype = 6;
        Push::Send(sibuf, msqid);
        // Got it
        Pop::Get(sibuf, msqid, 5, 0);
        // Show info
        Print::Show(sibuf);

        sleep(3);
    }
    return 0;
}