#include <iostream>
extern "C" __declspec(dllimport) int var;
extern "C" __declspec(dllimport) int Func(int w, int h);
int main(int argc, char* argv[]) {
	
	std::cout << var << std::endl;
	std::cout << Func(2, 45) << std::endl;

	std::cin.get();

	return 0;
}