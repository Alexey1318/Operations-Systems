#include <sys/wait.h>
#include "writefile.cpp"
void Parent( int* mypipe){
    std::string mfc;
    char buf;
    wait(NULL);
    close(mypipe[1]);
    while(read(mypipe[0], &buf, 1) > 0){
        mfc += buf;
    }
    close(mypipe[0]);
    Write(mfc + " Hi!\n");
    exit(EXIT_SUCCESS);
}
