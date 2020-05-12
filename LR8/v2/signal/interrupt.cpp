#include <iostream>
#include <signal.h>
void signalHandler(int signum) {
    using namespace std;
    cout << "Interrupt signal (" << signum << ") received.\n";

    // cleanup and close up stuff here  
    // terminate program  

    exit(signum);  
}