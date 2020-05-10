#include <iostream>
extern "C" __declspec(dllimport) int TestFunction(int w, int h);
int main(int argc, char* argv[]) {
	std::cout << TestFunction(2, 45) << std::endl;
	return 0;
}