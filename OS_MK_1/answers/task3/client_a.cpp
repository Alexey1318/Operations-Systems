#include "includes.h"
#include <cstdlib>

int main(int argc, const char** argv) {

    using namespace std;
    srand(time(NULL));

    // Define variables for queue work
    key_t key = atoi(argv[0]);
    int msqid;
    array_buf sabuf;

    // Connect to the queue
    if ((msqid = msgget(key, FLAG)) < 0) {
        perror("client::msgget");
        return -1;
    }
    std::cout << "Client #2 connected" << std::endl;

    while(true){
        // Send array
        sabuf.mtype = 4;
        cout << "Array: ";
        for(int i = 0; i < aln; ++i){ 
            sabuf.array[i] = rand() % 100;
        }   
        cout << endl;
        Push::Send(sabuf, msqid);
        // Got it
        Pop::Get(sabuf, msqid, 3, 0);
        // Show it
        Print::Show(sabuf);

        sleep(3);
    }
    return 0;
}