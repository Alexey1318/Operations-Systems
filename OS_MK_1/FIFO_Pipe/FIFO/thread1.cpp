#include <iostream>
#include <unistd.h>
#include <cstring>

// [0] - integer, id of FIFO
// [1] - text for FIFO

int main(int argc, char*argv[]){
    
    int fifo_id = atoi(argv[0]);
    
    // Запись строки в пайп
    write(fifo_id, argv[1], strlen(argv[1]));
    
    sleep(1);

    // Считывание строки из пайпа
    std::string buf;
    if(read(fifo_id, &buf, buf.length()) == -1){
        printf("can't read from fifo");
        return -1;
    } else {
        std::cout << buf << std::endl;
    }
    
    return 0;
}