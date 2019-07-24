// For memory leaks
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include <iostream>
#include "vec.h"

class tester {
private:
	int* m_data;
	int m_i;
	double m_b;
public:
	tester(int i, double b) {
		std::cout << "Tester Constructor Called: " << i << "\n";
		m_data = new int[i];
		m_i = i;
		m_b = b;
	}

	void print() {
		std::cout << m_b << "\n";
	}

	//tester(const tester& t) = default;

	
	tester(const tester& t) {
		m_i = t.m_i;
		std::cout << "Copy constructor called: " << m_i << "\n";
		m_data = new int[t.m_i];
	}

	tester(tester&& t) {
		m_i = t.m_i;
		std::cout << "Move constructor called: " << m_i << "\n";
		m_data = t.m_data;
		t.m_data = nullptr;
	}


	~tester() {
		delete[] m_data;
		std::cout << "Destructor called: " << m_i << "\n";
	}


};

void test() {
	vec<int> ages;

	int emma = 1000;
	for (int i = 0; i < emma; i++)
		ages.emplace_back(i);

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

void test2() {
	//tester t(4, 9.0);

	vec<tester> ts;
	//ts.push_back(t);
	//ts.push_back(t);
	//ts.push_back(t);
	ts.emplace_back(4, 9.0);
	ts.emplace_back(5, 9.0);
	ts.emplace_back(6, 9.0);
	ts.emplace_back(7, 9.0);
}

int main() {
	//test();
	test2();

	
	_CrtDumpMemoryLeaks();

	std::cin.get();
	return 0;
}