all: start
# Порядок действий Makefile
start: clear child parent.o makelib launch
clear:
	# Очистка консоли
	clear
child:
	# Создание исполняемого файла из child.cpp, нужен для вызова execl()
	g++ child.cpp -o child
parent.o:
	# Создание объектного файла, нужен для дальнейшей работы main-a
	g++ -c parent.cpp
makelib:
	# Создание библиотеки, содержащей объектные файлы
	ar rc lib.a parent.o
	ranlib lib.a
launch:	
	# Компилириуем main.cpp в исполняемый файл main
	g++ main.cpp -o main
	# Запускаем его
	clear
	./main mf.txt
	
