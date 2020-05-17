#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
int main(int argc, char*argv[]){
    int file = open(argv[0], O_WRONLY|O_APPEND);    
    std::string line;
    int c = 1;
    while(c != 4){
        line += argv[c];
        ++c;
    }
    write(file, line.c_str(), strlen(line.c_str()));
    close(file);
    return 0;
}