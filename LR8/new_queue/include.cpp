#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <signal.h>
#include <cstring>
#include <unistd.h>

#define mln 1024

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
    int array[10];
    int ch;
} message_buf;

void Show(message_buf &m){

    using namespace std;

    cout << "ch: " << m.ch << endl;
    cout << "type: " << m.mtype << endl;
    cout << "mes: " << m.mes << endl;
    cout << "array: ";
    for(int i = 0; i < 10; ++i){
        cout << m.array[i] << " ";
    }
    cout << endl;
}