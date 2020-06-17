
// Написати програму, яка відміняє дію термінальних сигналів для термінала 
// та дозволяє перевірити роботу режимів введення символів  з  відлунням та без.

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>

struct termios saved_attributes;
struct termios term;

// After program is interrupt, make terminal in canonical mode back
void ResetInputMode(){    
    tcsetattr(0, TCSANOW, &saved_attributes);
}

void NonCanonical(bool echo){
    if(!isatty(0)){
        perror("isatty()");
        exit(1);
    }
    tcgetattr(0, &saved_attributes);
    term = saved_attributes;
	// On non-canonical mode for off signals
    term.c_lflag &= ~(ICANON);
	// If echo-flag is true - off it
	if(echo){
    	term.c_lflag &= ~(ECHO);
	}
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &term);
}

// For correct exit from program
void ExitProgram(int sig){
    exit(0);
}

int main(int argc, char*argv[]){

	char c;
	bool echo_flag;
	std::cout << "Enter \"1\" for Non-echo mode or \"2\" for Echo mode: ";
    std::cin >> c;
	echo_flag = (c=='1')?true:false;
	NonCanonical(echo_flag);
    atexit(ResetInputMode);
    signal(SIGINT,ExitProgram);
    signal(SIGTERM,ExitProgram);
    while(true)
    {
        read(0,&c,term.c_cc[VMIN]);
        write(1,&c,term.c_cc[VMIN]);
    }
    return 0;

	return 0;
}
