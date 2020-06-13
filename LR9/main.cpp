#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>

// Рекурсивный обход по файловому дереву
void ShowFilesInDirectory(char* dirName){

    printf("%s\n", dirName);

    DIR* refDir;
    
    // Открыть директорию
    if ((refDir = opendir(dirName)) == NULL) {
        perror(dirName);
        return;
    }

    // Структуры для хранения данных о директории/файле
    struct dirent *dirInfo;
    struct stat fileBuf;

    // Пока директория не пуста
    while((dirInfo = readdir(refDir))!=NULL){
        
        // Если это директория - запуск рекурсии
        if(dirInfo->d_type == DT_DIR){
            if (strcmp(dirInfo->d_name, ".") == 0 || strcmp(dirInfo->d_name, "..") == 0){
				continue;
            }            
            printf("\n[%s]\n",dirInfo->d_name);
            strcat(dirName, "/");
            strcat(dirName, dirInfo->d_name);
            ShowFilesInDirectory(dirName);
        } 

        // Если файл - показать данные о нем
        else {
            stat(dirInfo->d_name, &fileBuf);
            if(!(fileBuf.st_mode & (S_IXGRP|S_IXUSR|S_IXOTH))){
                printf("[%s]%-14.*s\t%d\n", dirName, dirInfo->d_reclen, dirInfo->d_name, fileBuf.st_size);
            }
        }
    }
    printf("\n");
    closedir(refDir);   
} 

int main(int argc, const char** argv) {
    char path[256];
    strcpy(path, argv[1]);
    ShowFilesInDirectory(path);
    return 0;
}