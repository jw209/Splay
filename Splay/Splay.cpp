#include "Splay.h"

void Splay::insert(int data) {

	// initialize a new node
	Node* node = new Node;
	node->parent = nullptr;
	node->leftChild = nullptr;
	node->rightChild = nullptr;
	node->value = data;

	// for temporarily storing parent
	Node* y = nullptr;
	// for traversal
	Node* x = this->root;

	// traverse through tree until x is null
	while (x != nullptr) {
		y = x;
		if (node->value < x->value) {
			x = x->leftChild;
		}
		else {
			x = x->rightChild;
		}
	}

	// y is parent of x
	node->parent = y;
	if (y == nullptr) root = node;
	else if (node->value < y->value) y->leftChild = node;
	else y->rightChild = node;

	// splay the node
	splay(node);
}

Node* Splay::max(Node* node) {
	while (node->rightChild != nullptr) node = node->rightChild;
	return node;
}

Node* Splay::min(Node* node) {
	while (node->leftChild != nullptr) node = node->leftChild;
	return node;
}
