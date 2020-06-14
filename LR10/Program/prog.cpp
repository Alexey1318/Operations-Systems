#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <cstring>
#include <iostream>

/*
    Заменить символы управления - EOF, KILL, QUIT
    Значения параметров в неканоническом режиме - MIN=10, TIME=0
*/

struct termios saved_attributes;
struct termios term;

void ResetInputMode()
{    
    tcsetattr(0, TCSANOW, &saved_attributes);
}

bool Canonical()
{
    std::cout << "Canonical mode" << std::endl;
    struct termios term;
    if(!isatty(0)){
        perror("isatty()");
        return false;
    }
    tcgetattr(0, &saved_attributes);
    memcpy(&term, &saved_attributes, sizeof(saved_attributes));
    term.c_cc[VEOF] = '\001'; // Символ EOF, Ctrl-D заменяем на Ctrl-A
    term.c_cc[VKILL] = '\002'; // Вся текущая вводимая строка уничтожается, Ctrl-U заменяем на Ctrl-B
    term.c_cc[VINTR] = 0; // Отключаем прерывание программы по Ctrl-C
    term.c_cc[VQUIT] = '\003'; // Ввод символа QUIT вызывает посылку сигнала SIGQUIT всем процессам основной группы процессов, Ctrl-\ заменяем на Ctrl-C
    tcsetattr(0, TCSAFLUSH, &term);
    return true;
}

bool NonCanonical()
{
    std::cout << "Non-canonical mode" << std::endl;
    if(!isatty(0)){
        perror("isatty()");
        return false;
    }
    tcgetattr(0, &saved_attributes);
    term = saved_attributes;
    term.c_lflag &= ~(ICANON);
    term.c_lflag &= ~(ECHO);
    term.c_cc[VMIN] = 10;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &term);
    return true;
}

void ExitProgram(int sig)
{
    exit(0);
}

int main(int argc, const char** argv) 
{
    char c;

    do{
        std::cout << "Enter \"1\" for Non-canonical mode or \"2\" for Canonical mode: ";
        std::cin >> c;
        switch(c){
            case '1':
                NonCanonical();
            break;
            case '2':
                Canonical();
            break;
            default:
                std::cout << "You enter wrong value! Try again" << std::endl;
        }
    }while(c != '1' && c != '2');

    atexit(ResetInputMode);
    signal(SIGINT,ExitProgram);
    signal(SIGTERM,ExitProgram);
    while(true)
    {
        read(0,&c,term.c_cc[VMIN]);
        write(1,&c,term.c_cc[VMIN]);
    }
    return 0;
}