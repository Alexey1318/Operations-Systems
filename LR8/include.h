#include <iostream>
#include <signal.h>
#include <sys/msg.h>
#include <signal.h>
#include <cstring>
#include <unistd.h>

#define mln 1024
#define aln 10

#define abufsize aln*sizeof(int)
#define mbufsize mln

#define FLAG 0666|IPC_CREAT

typedef struct _msgbuf {
    long mtype;
    char mes[mln];
} message_buf;

typedef struct msgbuf_{
    long mtype;
    int array[aln];
} array_buf;

void Show(message_buf &m){

    using namespace std;

    cout << "type: " << m.mtype << endl;
    cout << "mes: " << m.mes << endl;    
    cout << endl;
}

void Show(array_buf &a){
    
    using namespace std;

    cout << "type: " << a.mtype << endl;
    cout << "array: ";
    for(int i = 0; i < aln; ++i){
        cout << a.array[i] << "\t";
    }
    cout << endl;
}