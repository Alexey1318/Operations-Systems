#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
int main (int argc, char*argv[]) {
    using namespace std;
    int pid = fork();
    switch(pid){
        case 0:
            execl("./gets", "Waiting signals...", NULL);
        break;
        default:
            cout << "default fork" << endl;
            sleep(3);
            kill(pid, SIGALRM);
        break;
    }
    return 0;
}