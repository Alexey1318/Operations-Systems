#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>

// Рекурсивный обход по файловому дереву
void ShowFilesInDirectory(const char* dirName){

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
            printf("[%s]\n",dirInfo->d_name);
            ShowFilesInDirectory(dirInfo->d_name);
        } 
        // Если файл - показать данные о нем
        else {
            stat(dirInfo->d_name, &fileBuf);
            printf("%-14.*s\t%d\n", dirInfo->d_reclen, dirInfo->d_name, fileBuf.st_size);
        }
    }

    closedir(refDir);   
} 

int main(int argc, const char** argv) {
    ShowFilesInDirectory(argv[1]);
    return 0;
}