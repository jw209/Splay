/*
	Splay.h

	Declaration file for splay class.
*/
#ifndef SPLAY_HPP
#define SPLAY_HPP

#include "Node.h"
#include <iostream>

class Splay {
protected:
	// the root of the splay tree
	Node* root;
	// removes a node with given int value of 'data'
	void removeHelp(Node* node, int data) {
		Node* x = nullptr;
		// 
		Node* a, * b;
		while (node != nullptr) {
			if (node->value == data) x = node;
			if (node->value <= data) node = node->rightChild;
			else node = node->leftChild;
		}

		if (x == nullptr) {
			std::cout << "Value does not exist in splay tree" << std::endl;
			return;
		}
		split(x, a, b);
		if (a->leftChild) a->leftChild->parent = nullptr;
		root = join(a->leftChild, b);
		delete(a);
		a = nullptr;
	}
	// splits tree into two nodes 'a' and 'b'
	void split(Node*& x, Node*& a, Node*& b) {
		splay(x);
		if (x->rightChild) {
			b = x->rightChild;
			b->parent = nullptr;
		}
		else b = nullptr;
		a = x;
		a->rightChild = nullptr;
		x = nullptr;
	}
	// joins two nodes 'a' and 'b'
	Node* join(Node* a, Node* b) {
		if (!a) return b;
		if (!b) return a;
		Node* x = max(a);
		splay(x);
		x->rightChild = b;
		b->parent = x;
		return x;
	}
	// used for 'zag' operations (rotating node left)
	void leftRotate(Node* x) {
		Node* y = x->rightChild;
		x->rightChild = y->leftChild;
		if (y->leftChild != nullptr) y->leftChild->parent = x;
		y->parent = x->parent;
		if (!x->parent) this->root = y;
		else if (x == x->parent->leftChild) x->parent->leftChild = y;
		else x->parent->rightChild = y;
		y->leftChild = x;
		x->parent = y;
	}
	// used for 'zig' operations (rotating node right)
	void rightRotate(Node* x) {
		Node* y = x->leftChild;
		x->leftChild = y->rightChild;
		if (y->rightChild != nullptr) y->rightChild->parent = x;
		y->parent = x->parent;
		if (!x->parent) this->root = y;
		else if (x == x->parent->rightChild) x->parent->rightChild = y;
		else x->parent->leftChild = y;
		y->rightChild = x;
		x->parent = y;
	}
	// Splay operation (ADD MORE OF A COMMENT)
	void splay(Node* x) {
		while (x->parent) {
			if (!x->parent->parent) {  // if x's grandparent is null
				if (x == x->parent->leftChild) rightRotate(x->parent); // zig
				else leftRotate(x->parent); // zag
			}  // if x is the left child and its parent is the left child of its parent
			else if (x == x->parent->leftChild && x->parent == x->parent->parent->leftChild) {
				// zig-zig
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			}  // if x is the right child and its parent is the right child of its parent
			else if (x == x->parent->rightChild && x->parent == x->parent->parent->rightChild) {
				// zag-zag
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			}  // if x is the right child and its parent is the left child of its parent
			else if (x == x->parent->rightChild && x->parent == x->parent->parent->leftChild) {
				// zig-zag
				leftRotate(x->parent);
				rightRotate(x->parent);
			}  // if x is the left child and its parent is the right child of its parent
			else {
				//zag-zig
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}
	// traverse the tree in pre-order fashion
	void preOrderHelp(Node* node) {
		if (node != nullptr) {
			std::cout << node->value << std::endl;
			preOrderHelp(node->leftChild);
			preOrderHelp(node->rightChild);
		}
	}
	// traverse the tree in in-order fashion
	void inOrderHelp(Node* node) {
		if (node != nullptr) {
			inOrderHelp(node->leftChild);
			std::cout << node->value << std::endl;
			inOrderHelp(node->rightChild);
		}
	}
	// traverse the tree in post-order fashion
	void postOrderHelp(Node* node) {
		if (node != nullptr) {
			postOrderHelp(node->leftChild);
			postOrderHelp(node->rightChild);
			std::cout << node->value << std::endl;
		}
	}
public:
	// default constructor
	Splay() { root = nullptr; }
	// insert a new node into the splay tree
	void insert(int);
	// public method to call for deletion of a node
	void remove(int data) { removeHelp(this->root, data); }
	// returns 'this' root
	Node* Root() { return this->root; }
	// public method to call for pre-order traversal
	void preOrder() { preOrderHelp(this->root); }
	// public method to call for in-order traversal
	void inOrder() { inOrderHelp(this->root); }
	// public method to call for post-order traversal
	void postOrder() { postOrderHelp(this->root); }
	// returns a node with the maximum value
	Node* max(Node*);
	// returns a node with the minimum value
	Node* min(Node*);
};

#endif SPLAY_HPP