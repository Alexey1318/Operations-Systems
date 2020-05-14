#ifndef __HEADER_H
#define __HEADER_H
extern "C" __declspec(dllexport) int var = 10;
extern "C" __declspec(dllexport) int Func(int, int);
class _declspec(dllexport) Foo {
public:
	Foo(int);
	~Foo();
	int Get();
	void Set(int);
private:
	int a;
};
#endif