#include <sys/sem.h>
#include <stdio.h>

// Функция открытия существующего семафора
void open_sem(int *sid, key_t key){
    if((*sid = semget(key, 0, 0666)) == -1){
        printf("Семафор не существует\n");
        return;
    }
}

int main(int argc, char*argv[]){
    
    return 0;
}
