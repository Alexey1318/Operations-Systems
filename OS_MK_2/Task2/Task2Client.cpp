#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char** argv) {

    using namespace std;

    cout << "debug message" << endl;

    int clientSocket = atoi(argv[0]);
    cout << clientSocket << endl;

    // While receiving - display message, echo message
    char buf[4096];
    while(true){
        
        // Clear the buffer
        memset(buf, 0, 4096);

        // Wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if(bytesRecv == -1){
            cerr << "There was a connection issue" << endl;
            break;
        }
        if(bytesRecv == 0){
            cout << "The client disconnected" << endl;
            break;
        }

        // Display message
        cout << "Received: " << string(buf, 0, bytesRecv) << endl;

        // Enter lines of text
        string userInput;
        cout << "> ";
        getline(cin, userInput);

        // Resend message
        send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
    }

    return 0;
}