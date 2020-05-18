#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h> 
#include <iostream>
int main(int argc, char*argv[]){
    
    // Дескриптор трубы
    int fd_fifo;

    // Имя пайпа и параметры доступа к нему
    const char* path = "fifo0001.1";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // Если файл с таким именем существует - "отвязываем" его
    unlink(path);

    // Создание FIFO
    fd_fifo = mkfifo(path, mode);
    if(fd_fifo == -1){
        printf("can't vreate fifo");
        return -1;
    }

    // Запуск двух независимых потоков, которые обмениваются информацией через именованный канал
    std::string id;
    id += fd_fifo;
    if(fork() == 0){
        execl("./thread1", id.c_str(), "Welcome to the club, buddy!\n");
    }
    execl("./thread2", id.c_str());

    return 0;
}