#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <iostream>

// Заполняем права на файл
std::string CheckAccess(struct stat &file){
    
    char access[11];
    
    (file.st_mode & S_IFDIR)?strcat(access,"d"):strcat(access,"-");
    // Owner
    (file.st_mode & S_IRUSR)?strcat(access,"r"):strcat(access,"-");
    (file.st_mode & S_IWUSR)?strcat(access,"w"):strcat(access,"-");
    (file.st_mode & S_IXUSR)?strcat(access,"x"):strcat(access,"-");
    // Group
    (file.st_mode & S_IRGRP)?strcat(access,"r"):strcat(access,"-");
    (file.st_mode & S_IWGRP)?strcat(access,"w"):strcat(access,"-");
    (file.st_mode & S_IXGRP)?strcat(access,"x"):strcat(access,"-");
    // Other
    (file.st_mode & S_IROTH)?strcat(access,"r"):strcat(access,"-");
    (file.st_mode & S_IWOTH)?strcat(access,"w"):strcat(access,"-");
    (file.st_mode & S_IXOTH)?strcat(access,"x"):strcat(access,"-");
    
    std::string s_access = access;
    return s_access;
}

// Рекурсивный обход по файловому дереву
void ShowFilesInDirectory(char* dirName){

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
        
        // Получить информацию о файле
        stat(dirInfo->d_name, &fileBuf);

        // Проверка что это не файлы с именами . или ..
        if (strcmp(dirInfo->d_name, ".") == 0 || strcmp(dirInfo->d_name, "..") == 0){
			continue;
        }

        // Если на данный файл права чтения-записи имеет ТОЛЬКО владелец - показать о нем информацию
        
        // !!! Чтобы поулчилось задание №4 убери ! из условного оператора !!!
        
        if(!(fileBuf.st_mode & (S_IXGRP|S_IXUSR|S_IXOTH))){      
            //std::string access = CheckAccess(fileBuf);            
            printf("%10s\t%10d B\tUID: %-10d\tGID: %-10d\t", dirInfo->d_name, fileBuf.st_size, fileBuf.st_uid, fileBuf.st_gid);
            std::cout << CheckAccess(fileBuf) << std::endl;
        }

        // Если это директория - запуск рекурсии
        if(dirInfo->d_type == DT_DIR){                    
            
            // Формирование полного пути к файлу - для работы функции stat()
            strcat(dirName, "/");
            strcat(dirName, dirInfo->d_name);

            // Вход в рекурсию
            ShowFilesInDirectory(dirName);

            // Удаление имени последней директории из переменной для хранения пути к начальной директории
            std::string helpPath = dirName;
            std::string helpName = dirInfo->d_name;
            std::string::size_type it = helpPath.find(helpName);
            if(it != std::string::npos){
                helpPath.erase(it, helpName.length());
            }

            strcpy(dirName, helpPath.c_str());
        } 
    }

    // Закрыть текущую директорию
    closedir(refDir);   
} 

int main(int argc, const char** argv) {
    char path[256];
    strcpy(path, argv[1]);
    ShowFilesInDirectory(path);
    return 0;
}