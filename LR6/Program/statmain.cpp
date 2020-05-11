// static link

#include <iostream>
//#pragma comment (lib, "lib.a")
extern "C" __declspec(dllimport) int TestFunction(int w, int h);
int main(int argc, char*argv[]){
    std::cout << TestFunction(atoi(argv[1]), atoi(argv[2])) << std::endl;
    return 0;
}