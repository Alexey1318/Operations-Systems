
// Написати серверну програму, 
// яка реєструється слухачем порту
// та обробляє підключення в режимі «запит-відповідь» 
// з використанням дочірніх процесів (створених за допомогою fork()).

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

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
    hint.sin_port = htons(1235);
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

        if(fork()){
            execl("./task2client",  std::to_string(client_socket).c_str(), NULL);
        }
    }

    if(client_socket < 0){
        cerr <<  "Accept failed" << endl;
        return -5;
    }

    close(listening);

    return 0;
}

