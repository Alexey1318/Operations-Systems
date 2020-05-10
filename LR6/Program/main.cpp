#include <iostream>
#include <Windows.h>
#include <tchar.h>

typedef int (*TESTFUNCTION)(int, int);

int main(int argc, char* argv[]) {
    int w = atoi(argv[1]), h = atoi(argv[2]);
    int multi;
    DWORD err;
    HINSTANCE hDll = LoadLibrary(_T("Dll.dll"));
    if (hDll != NULL) {
        std::cout << "Library was loaded" << std::endl;
    }
    else {
        err = GetLastError();
        std::cerr << "Couldn't load DLL. Error #" << err << std::endl;
        return -1;
    }
    TESTFUNCTION lpTestFunction = (TESTFUNCTION)GetProcAddress(hDll, "TestFunction");
    if (lpTestFunction != NULL) {
        multi = (*lpTestFunction)(w, h);
        std::cout << multi << std::endl;
    }
    else {
        std::cerr << "Couldn't call TestFunction(int, int)" << std::endl;
    }
    FreeLibrary(hDll);
    std::cin.get();
    return 0;
}