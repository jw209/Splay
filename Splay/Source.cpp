#include "Splay.h"
#include <iostream>

int main() {
	Splay x;
	x.insert(10);
	std::cout << "\n";
	x.preOrder();

	x.insert(12);
	std::cout << "\n";
	x.preOrder();

	x.insert(8);
	std::cout << "\n";
	x.preOrder();

	x.insert(20);
	std::cout << "\n";
	x.preOrder();

	return 0;
}