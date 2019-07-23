// For memory leaks
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "vec.h"

void test();

void test() {
	vec<int> ages;

	int emma = 1000;
	for (int i = 0; i < emma; i++)
		ages.push_back(i);

	for (unsigned int i = 0; i < ages.size(); i++)
		std::cout << ages[i] << "\n";

	vec<int>::iterator femma = ages.begin();
	std::cout << "\nIterator Tests--------------------\n";
	std::cout << *femma << "\n";
	std::cout << *(femma++) << "\n";
	std::cout << *(femma) << "\n";
	std::cout << *(femma) << "\n";
	std::cout << *(++femma) << "\n";
	std::cout << *(--femma) << "\n";
	std::cout << *(femma--) << "\n";
	std::cout << *(femma) << "\n";
	std::cout << (femma == ages.begin()) << "\n";
	std::cout << (++femma == ages.begin()) << "\n";

	std::cout << "Hello Emma!\n";
}

int main() {
	test();
	
	_CrtDumpMemoryLeaks();

	std::cin.get();
	return 0;
}