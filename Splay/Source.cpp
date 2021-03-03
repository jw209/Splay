#include "Splay.h"
#include <iostream>

int main() {
	Splay x;
	x.insert(10);
	std::cout << "\nInserted 10\n";
	x.preOrder();
	x.insert(12);
	std::cout << "\nInserted 12\n";
	x.preOrder();
	x.insert(8);
	std::cout << "\nInserted 8\n";
	x.preOrder();
	x.insert(15);
	std::cout << "\nInserted 15\n";
	x.preOrder();
	x.insert(17);
	std::cout << "\nInserted 17\n";
	x.preOrder();
	x.insert(5);
	std::cout << "\nInserted 5\n";
	std::cout << "\npreOrder\n";
	x.preOrder();
	std::cout << "\nInorder\n";
	x.inOrder();
	std::cout << "\nPostOrder\n";
	x.postOrder();

	return 0;
}