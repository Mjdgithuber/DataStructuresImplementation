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

	for (int i = 0; i < emma; i++)
		std::cout << ages[i] << "\n";

	std::cout << "Hello Emma!\n";
}

int main() {
	test();
	
	_CrtDumpMemoryLeaks();

	std::cin.get();
	return 0;
}