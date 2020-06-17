
// Написати серверну програму, 
// яка обробляє паралельні підключення без багатозадачності 
// з використанням мультиплексування (функція select()).

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

bool Check(int*arr, int size, fd_set &watchset){
    for(int i = 0; i < size; ++i){
        if(FD_ISSET(arr[i], &watchset)){
            return true;
        }
    }
    return false;
}

int main(int argc, const char** argv) {
    
    int count = 0;

    int fds[10];
    fd_set watchset; /* fds для чтения */
	fd_set inset; /* обновляется select() */

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
    hint.sin_port = htons(8888);
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

    char buf[4096];
    char bufSocket[4096];
	int maxfd;

    while((client_socket = accept(listening, (sockaddr*)&client, (socklen_t*)&c))){

        fds[count] = client_socket;
        cout << "Client #" << ++count << " connected" << endl; 

        /* начать чтение из дескрипторов */
	    FD_ZERO(&watchset);
        for(int i = 0; i < count + 1; ++i){
	        FD_SET(fds[i], &watchset);
        }
        int max = fds[0];

        for (int i = 0; i < 10; ++i) {
            if (fds[i] > max) {
                max = fds[i];
            }
        }

        while (Check(fds, count, watchset)) {

		    /* здесь копируем watchset, потому что select() обновляет его */
		    inset = watchset;

		    if (select(maxfd + 1, &inset, NULL, NULL, NULL) < 0) {
	    		perror("select");
    			return 1;
		    }

		    /* проверить, какой из файловых дескрипторов готов для чтения из него */
		    for (int i = 0; i < count; i++)  {
			    if (FD_ISSET(fds[i], &inset))  {
                    // Clear the buffer
                    memset(bufSocket, 0, 4096);
                    // Wait for a message
                    int bytesRecv = recv(fds[i], bufSocket, 4096, 0);

	    			if (bytesRecv < 0){
					    perror("read");
				    	return 1;
			    	}
		    		else if (!bytesRecv) {
    					/* этот канал закрыт, не пытаться читать из него снова */
					    close(fds[i]);
				    	FD_CLR(fds[i], &watchset);
			    	}
		    		else {                        
                        if(bytesRecv == -1){
                            cerr << "There was a connection issue" << endl;
                            break;
                        }
                        if(bytesRecv == 0){
                            cout << "The client disconnected" << endl;
                            break;
                        }

                        // Display message
                        cout << "Received: " << string(bufSocket, 0, bytesRecv) << endl;

                        // Resend message
                        send(fds[1], bufSocket, bytesRecv + 1, 0);
				    }
			    }
		    }
	    }
    }

    if(client_socket < 0){
        cerr <<  "Accept failed" << endl;
        return -5;
    }

    close(listening);

    return 0;
}