#include <stdlib.h>
#include <unistd.h>
#include <cstring>
void Child(int *mypipe){
    const char*message = "Hi daddy, I'm your child!";
    close(mypipe[0]);
    write(mypipe[1], message, strlen(message));
    close(mypipe[1]);
    exit(EXIT_SUCCESS);
}
