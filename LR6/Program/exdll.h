#ifndef __EXDLL_H
#define __EXDLL_H
#define MYDLL_API __declspec(dllexport)
extern "C" MYDLL_API int foobar(int a, int b);
#endif