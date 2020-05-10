#ifndef __EXDLL_H
#define __EXDLL_H
extern "C" __declspec(dllexport) int foo(int a, int b);
extern "C" __declspec(dllexport) int TestFunction(int w, int h);
#endif