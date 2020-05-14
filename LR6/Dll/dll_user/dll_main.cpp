#include <Windows.h>
#include <iostream>
#include <tchar.h>

typedef int (*FUNC)(int, int);

int main(int argc, char* argv[]) {
    int w = 10, h = 10;
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

    FUNC lpTestFunction = (FUNC)GetProcAddress(hDll, "Func");

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