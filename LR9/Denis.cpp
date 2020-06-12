#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

class FileReader
{
public:

	FileReader()	// Конструктор по умолчанию
		: lower(0), higher(30000) // Инициализация пределов размера файлов
	{
	}
	
	FileReader(int argc, char* argv[])	// Конструктор с параметрами
		: FileReader() 	// Делегирующий конструктор, инициализация атрибутов командной строки
	{ 
		this->argc = argc;
		this->argv = argv;
	}
	
	bool OpenDir(const char* dirName = ".")
	{
		if(!(dir = opendir(dirName)))	// Открытие текущего каталога "."
		{
			perror("opendir");	// Ошибка открытия каталога
			return -1;
		}
		std::cout << argv[0] <<" - folder was openned successfuly\n\n";
		return dir;
	}
	
	void listdir(const char* name, int indent) // Рекурсивная функция чтения главного каталога и подкаталогов
	{
		DIR *dir;
		struct dirent *entry;
		
		
		if (!(dir = opendir(name)))
			return;

		while ((entry = readdir(dir)) != NULL) 
		{
			
			if (entry->d_type == DT_DIR) 
			{
				char path[1024];
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					continue;
               
				snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
				printf("%*s[%s]\n", indent, "", entry->d_name);
				listdir(path, indent + 2);
			} 
			else 
			{
				stat(ent->d_name, &sb);
				std::cout << "\n====================================\n";
				std::cout << "File name: " << entry->d_name << std::endl;	// Выводим имя файла
				std::cout << "File size: " << sb.st_size << "bytes\n";	// Размер файла
				std::cout << "Last status change: " << ctime(&sb.st_ctime) << std::endl; // Ласт изменение
				std::cout << "Last file access: " << ctime(&sb.st_atime) << std::endl; 	// Лайст открытие
				std::cout << "Last file modification: " << ctime(&sb.st_mtime)  << std::endl; // Ласт модификация
				std::cout << "Ownership: UID=" << sb.st_uid << " GID="<< sb.st_gid << std::endl; // Владелец
				std::cout << "Mode: " << sb.st_mode << std::endl;	// Режим
				std::cout << "====================================\n";
				//printf("%*s- %s\n", indent, "", entry->d_name);
			}
		}
		closedir(dir);
	}
	
	bool ReadMainDir()
	{
		errno = 0;	// Установить errno в 0, чтобы можно было выяснить, когда readdir() даст сбой
		while((ent = readdir(dir)))
		{
			if (stat(ent->d_name, &sb) == -1) 	// Получаем информацию о файле по имени
			{
				perror("stat");
				return -1; 		//exit(EXIT_FAILURE);
			}
			if(sb.st_size > lower && sb.st_size < higher) // Выводим файлы в диапазоне (размер файла)
			{
				std::cout << "\n====================================\n";
				std::cout << "File name: " << ent->d_name << std::endl;	// Выводим имя файла
				std::cout << "File size: " << sb.st_size << "bytes\n";	// Размер файла
				std::cout << "Last status change: " << ctime(&sb.st_ctime) << std::endl; // Ласт изменение
				std::cout << "Last file access: " << ctime(&sb.st_atime) << std::endl; 	// Лайст открытие
				std::cout << "Last file modification: " << ctime(&sb.st_mtime)  << std::endl; // Ласт модификация
				std::cout << "Ownership: UID=" << sb.st_uid << " GID="<< sb.st_gid << std::endl; // Владелец
				std::cout << "Mode: " << sb.st_mode << std::endl;	// Режим
				std::cout << "====================================\n";
			}
			errno = 0;	// Сбросить errno, поскольку std::cout() может модифицировать ее
		}
		if(errno)
		{
			perror("readdir");	// Ошибка чтения содержимого каталога
			return -1;
		}
		return 0;
	}
	
	bool CloseDir()
	{
		return closedir(this->dir); // Закрываем каталог
	}
	
	void SetLowerBreaket(int l)
	{
		this->lower = l;
	}
	void SetHigherBreaket(int h)
	{
		this->higher = h;
	}
	
private:
	DIR* dir;
	struct dirent* ent;
	struct stat sb;
	
	int argc;
	char** argv;
	
	int lower;	// Мин размер файла (file-size-byte)
	int higher; // Макс размер файла (file-size-byte)
};

int main(int argc, char* argv[])
{
	FileReader fReader(argc, argv);
	
	fReader.listdir(".", 0);	// Чтение главной и под директорий
	
	//fReader.OpenDir();
	
	
	int lower = 0, higher = 0;

	//	std::cout << "Enter the lower breaket of file-size (bytes): ";
		//std::cin >> lower;
		//std::cout << "Enter the higher breaket of file-size (bytes): ";
		//std::cin >> higher;

	//fReader.SetLowerBreaket(lower);
	//fReader.SetHigherBreaket(higher);
	
	//fReader.ReadDir();
	
	//fReader.CloseDir();
	
	return 0;
}