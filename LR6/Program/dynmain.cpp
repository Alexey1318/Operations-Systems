// dynamic link

#include <iostream>
#include <Windows.h>
#include <tchar.h>

typedef int (*func)(int, int);

int main(int argc, char* argv[]) {
    int w = atoi(argv[1]),
        h = atoi(argv[2]);
    int multi;

    DWORD err;
    HINSTANCE hDll = LoadLibrary(_T("mydll.dll"));

    if (hDll != NULL) {
        std::cout << "Library was loaded" << std::endl;
    }
    else {
        err = GetLastError();
        std::cerr << "Couldn't load DLL. Error #" << err << std::endl;
        return -1;
    }

    func lpTestFunction = (func)GetProcAddress(hDll, "foobar");
    if (lpTestFunction != NULL) {
        multi = (*lpTestFunction)(w, h);
        std::cout << multi << std::endl;
    }
    else {
        err = GetLastError();
        std::cerr << "Couldn't call foo(int, int). Error #" << err << std::endl;
    }

    FreeLibrary(hDll);
    std::cin.get();
    return 0;
}