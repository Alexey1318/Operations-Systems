#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

using namespace std;

void *Connection(void*socket_desc){

    int clientSocket = *(int*)socket_desc;
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

int main(int argc, const char** argv) {
    
    int count = 1;

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        cerr << "Can't create socket!" << endl;
        return -1;
    }
    cout << "Socket created" << endl;
    
    // Bind tho socket to an IP/port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(4321);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); 

    if(bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1){
        cerr << "Can't bind to IP/port" << std::endl;
        return -2;
    }
    cout << "Bind success" << endl;

    // Mark the socket for listening in
    if(listen(listening, SOMAXCONN) == -1){
        cerr << "Can't listen!" << endl;
        return -3;
    }
    cout << "Waiting for incoming connections..." << endl;

    int c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    int client_socket;
    sockaddr_in client;

    while((client_socket = accept(listening, (sockaddr*)&client, (socklen_t*)&c))){

        cout << "Client #" << count << " connected" << endl; 
        ++count;

        if(pthread_create(&thread_id, NULL, Connection, (void*)&client_socket) < 0){
            cerr << "Can't create thread" << endl;
            return -3;
        }

        //pthread_join(thread_id, NULL);
    }

    if(client_socket < 0){
        cerr <<  "Accept failed" << endl;
        return -5;
    }

    close(listening);

    return 0;
}

