#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

// Рекурсивный обход по файловому дереву
void ShowFilesInDirectory(const char* dirName){
    std::cout << dirName << std::endl;
    DIR* refDir;
    
    // Открыть директорию
    if ((refDir = opendir(dirName)) == NULL) {
        perror(dirName);
        exit(1);
    }

    // Структуры для хранения данных о директории/файле
    struct dirent *dirInfo;
    struct stat fileBuf;

    // Пока директория не пуста
    while((dirInfo = readdir(refDir))!=NULL){

        std::cout << dirInfo->d_name << std::endl;
        // Если при получении информации о файле -1 - ошибка
        if(stat(dirInfo->d_name, &fileBuf)==-1){
            perror(dirInfo->d_name);
            return;
        }

        // Если это обычный файл - вывести о нем информацию
        if((fileBuf.st_mode & S_IFMT) == S_IFREG){            
            printf("%-14.*s  %ld bytes\n", dirInfo->d_reclen, dirInfo->d_name, fileBuf.st_size);
        }

        // Если это директория - запуск рекурсии
        if((fileBuf.st_mode & S_IFMT) == S_IFDIR) {
            if (strcmp(dirInfo->d_name, ".") == 0 || strcmp(dirInfo->d_name, "..") == 0){
					continue;
            }
            printf("[%-14.*s]\n", dirInfo->d_reclen, dirInfo->d_name);
            ShowFilesInDirectory(dirInfo->d_name);
        }
    }

    closedir(refDir);   
} 

int main(int argc, const char** argv) {
    ShowFilesInDirectory(argv[1]);
    return 0;
}