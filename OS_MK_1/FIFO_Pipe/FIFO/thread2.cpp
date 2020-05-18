#include <iostream>
#include <unistd.h>
#include <cstring>

// [0] - integer, id of FIFO

int main(int argc, char*argv[]){

    int fifo_id = atoi(argv[0]);

    // Считывание строки из пайпа
    std::string buf;
    if(read(fifo_id, &buf, buf.length()) == -1){
        printf("can't read from fifo");
        return -1;
    } else {
        std::cout << buf << std::endl;
    }

    sleep(1);

    // Запись строки в пайп
    std::string text = "Hello you too, boychick!";
    write(fifo_id, text.c_str(), text.length());

    return 0;
}