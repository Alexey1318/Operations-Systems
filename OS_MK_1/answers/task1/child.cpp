#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, const char** argv) {
    printf("Child: parent pid=%d, pid=%d\n", getppid(), getpid());
    kill(getppid(), SIGCHLD);
    return 0;
}