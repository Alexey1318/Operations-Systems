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
#define statsize mln + 3*sizeof(int)

#define FLAG 0666|IPC_CREAT

struct message_buf {
    long mtype;
    char mes[mln];
};

struct array_buf {
    long mtype;
    int array[aln];
};

struct stat_info{
    long mtype;
    int msqid;
    int user_id;
    int mes_count;
    char time_last_request[mln];
};

namespace Print{

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

    void Show(stat_info &s){

        using namespace std;

        cout << "msqid: " << s.msqid << endl;
        cout << "user id: " << s.user_id << endl;
        cout << "message(s) in queue: " << s.mes_count << endl;
        cout << "time of last message: " << s.time_last_request << endl;
    }
}

namespace Push{
    int Send(message_buf &m, int id){

        if(msgsnd(id, &m, mbufsize, IPC_NOWAIT) < 0) { 
            return -1;
        } 
        return 0;
    }

    int Send(array_buf &a, int id){

        if(msgsnd(id, &a, abufsize, IPC_NOWAIT) < 0) {  
            return -1;
        } 
        return 0;
    }

    int Send(stat_info &s, int id){
        
        if(msgsnd(id, &s, statsize, IPC_NOWAIT) < 0) {   
            return -1;
        } 
        return 0;
    }
}

namespace Pop{
    int Get(message_buf& m, int id, int type, int msgflg){

        if (msgrcv(id, &m, mbufsize, type, msgflg) < 0) {
            return -1;
        }
        return 0;
    }

    int Get(array_buf& a, int id, int type, int msgflg){

        if (msgrcv(id, &a, abufsize, type, msgflg) < 0) {
            return -1;
        }
        return 0;
    }

    int Get(stat_info& s, int id, int type, int msgflg){
       
        if (msgrcv(id, &s, statsize, type, msgflg) < 0) {
            return -1;
        }
        return 0;
    }
}