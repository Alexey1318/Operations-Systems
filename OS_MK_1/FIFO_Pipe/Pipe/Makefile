all: start
start: clear parent.o child.o writefile.o makelib main.o launch
clear:
	clear
parent.o:
	g++ -c parent.cpp
child.o:
	g++ -c child.cpp
writefile.o: 
	g++ -c writefile.cpp 
makelib:
	ar rc lib.a parent.o child.o writefile.o
	ranlib lib.a
main.o:
	g++ main.cpp -o final
launch:
	./final
