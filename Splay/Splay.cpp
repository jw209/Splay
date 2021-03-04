/*
*	Splay.cpp
*
*	Implementation file for the Splay class
*/
#include "Splay.h"

void Splay::insert(int data) {

	// initialize a new node
	Node* node = new Node;
	node->parent = nullptr;
	node->leftChild = nullptr;
	node->rightChild = nullptr;
	node->value = data;

	// for temporarily storing parent (will stay null if x is null)
	Node* y = nullptr;
	// for traversal
	Node* x = this->root;

	// traverse through until an available space
	// on the tree is found
	while (x != nullptr) {
		// y is being set the equal to the current node which
		// will be the parent when the while loop exits
		y = x;
		if (node->value < x->value) {
			x = x->leftChild;
		}
		else {
			x = x->rightChild;
		}
	}

	// set the parent of the node equal to y
	node->parent = y;
	// perform the insertion of node to the appropriate position
	if (y == nullptr) root = node;
	else if (node->value < y->value) y->leftChild = node;
	else y->rightChild = node;

	// splay the node
	splay(node);
}

// traverses to the far right of the tree to return the largest value
Node* Splay::max(Node* node) {
	while (node->rightChild != nullptr) node = node->rightChild;
	return node;
}

// traverses to the far left of the tree to return the smallest value
Node* Splay::min(Node* node) {
	while (node->leftChild != nullptr) node = node->leftChild;
	return node;
}

bool Splay::isFound(int i) {

	Node* temp = searchHelp(this->root, i);
	if (temp == nullptr) return 0;
	else if (temp->value == i) return 1;
	else return 0;
}