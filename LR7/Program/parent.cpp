#include <iostream>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <unistd.h>

void Parent(std::string filename){
    // Открытие файла с именем, полученным как параметр при вызове программы из процесса в режиме "чтение и запись"
    int file = open(filename.c_str(), O_RDONLY);
    char buf;
    std::string mes;
    // Побайтово считываем содержимое файла в переменную
    while(read(file, &buf, 1) > 0){
        mes += buf;
    }
    // Выводим считанные данные на экран
    std::cout << "Parent: " << mes << std::endl;
    close(file);
}
