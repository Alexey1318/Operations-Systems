#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "interrupt.cpp"
int main (int argc, char*argv[]) {
    using namespace std;
    signal(SIGALRM, signalHandler);
    int k = 1;
    while(true){
        cout << argv[0] << " " << k << endl;
        sleep(1);
        ++k;
    }
    return 0;
}