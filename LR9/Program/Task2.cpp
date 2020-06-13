#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <iostream>

// Fill text string with data of file rights
std::string CheckRights(struct stat &file){
    
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

// Recursive bypass file tree
void ShowFilesInDirectory(char* dirName){

    DIR* refDir;
    
    // Open directory
    if ((refDir = opendir(dirName)) == NULL) {
        perror(dirName);
        return;
    }

    // Structure for keeping data of current directory and file 
    struct dirent *dirInfo;
    struct stat fileBuf;

    // While directory isn't empty
    while((dirInfo = readdir(refDir))!=NULL){
        
        // Getting info about file
        stat(dirInfo->d_name, &fileBuf);

        // Check that this file haven't "." or ".." in name
        if (strcmp(dirInfo->d_name, ".") == 0 || strcmp(dirInfo->d_name, "..") == 0){
			continue;
        }

        // If only current user have rights for read-write - show info about file/directory
        if(!(fileBuf.st_mode & (S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH))){    

            // File name - File size - B (bytes) - User ID - Group ID - Rights          
            printf("%10s\t%10d B\tUID: %-10d\tGID: %-10d\t", dirInfo->d_name, fileBuf.st_size, fileBuf.st_uid, fileBuf.st_gid);
            std::cout << CheckRights(fileBuf) << std::endl;
        }

        // If directory - start recursive bypass
        if(dirInfo->d_type == DT_DIR){         

            // Create full path to file - for right work stat()
            strcat(dirName, "/");
            strcat(dirName, dirInfo->d_name);

            // Start recursive
            ShowFilesInDirectory(dirName);

            // Delete name of last directory from path
            std::string helpPath = dirName;
            std::string helpName = dirInfo->d_name;
            std::string::size_type it = helpPath.find(helpName);
            if(it != std::string::npos){
                helpPath.erase(it, helpName.length());
            }

            strcpy(dirName, helpPath.c_str());
        } 
    }

    // Close current directory
    closedir(refDir);   
} 

int main(int argc, char* argv[]) {
    ShowFilesInDirectory(argv[1]);
    return 0;
}