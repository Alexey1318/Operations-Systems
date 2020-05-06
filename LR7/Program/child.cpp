#include <fcntl.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>

int main(int argc, char*argv[]){
    // Открытие файла с именем, полученным как параметр при вызове программы из процесса; режим дозаписи
    int file = open(argv[0], O_WRONLY | O_APPEND);
    std::string mfc = std::strcat(argv[1], argv[2]);
    // Запись сообщения в файл и его закрытие
    write(file, mfc.c_str(), strlen(mfc.c_str()));
    close(file);
    return 0;
}