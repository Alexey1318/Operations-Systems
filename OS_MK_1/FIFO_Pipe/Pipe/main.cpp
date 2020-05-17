#include "parent.cpp"
#include "child.cpp"
int main(){
    int myPipe[2];
    if(pipe(myPipe) == -1){
        std::cerr<<"Error creating pipe"<<std::endl;
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();    
    switch(pid){
        case -1:
            std::cerr<<"Error calling fork()"<<std::endl;
            exit(EXIT_FAILURE);
        case 0:
            Child(myPipe);
    }
    Parent(myPipe);
    return 0;
}
