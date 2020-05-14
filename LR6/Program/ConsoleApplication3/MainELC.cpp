#include <iostream>
#include "DynamicLinkLibrary.h"

#pragma comment (lib, "DynamicLinkLibrary.lib")

int main(int argc, char* argv[]) {

	// Use library class
	Foo* obj = new Foo(5);
	std::cout << obj->Get() << std::endl;

	obj->Set(12);
	std::cout << obj->Get() << std::endl;

	// Use library function
	std::cout << Func(4, 5) << std::endl;
	std::cout << var << std::endl;

	// Show and change library variable
	var = 14;
	std::cout << var << std::endl;

	std::cin.get();

	return 0;
}
