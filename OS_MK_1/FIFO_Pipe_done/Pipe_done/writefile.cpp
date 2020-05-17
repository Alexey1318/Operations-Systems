#include <string>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
void Write(std::string mfc){
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int file = creat("myfile.txt", mode);
    file = open("myfile.txt", O_RDWR);
    write(file, mfc.c_str(), strlen(mfc.c_str()));
    close(file);
}
