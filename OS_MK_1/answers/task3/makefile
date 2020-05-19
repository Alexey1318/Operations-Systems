# use makefile for simple compile program 
all:
	# clear console
	clear
	# compile server part
	g++ -o server server.cpp
	# compile threads applications
	g++ -o client_m client_m.cpp
	g++ -o client_a client_a.cpp
	g++ -o client_s client_s.cpp
	#run server with queue key in argument
	./server 1
