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
		// x will help us traverse through the tree
		Node* x = nullptr;
		// a and b will store the position of x's children
		Node* a, * b;
		while (node != nullptr) {	// traverse until value is found
			if (node->value == data) x = node;
			if (node->value <= data) node = node->rightChild;
			else node = node->leftChild;
		}

		// if x is nullptr tree is either empty or it reached the end without finding value
		if (x == nullptr) {
			std::cout << "Tree is empty or value does not exist within the tree." << std::endl;
			return;
		}

		// split x
		split(x, a, b);
		// if a has a left child, make its parent null
		if (a->leftChild) a->leftChild->parent = nullptr;
		// joins a's left child and b at the root and then delete a
		root = join(a->leftChild, b);
		delete(a);
		a = nullptr;
	}
	// 
	void split(Node*& x, Node*& a, Node*& b) {
		// splay the node (bring it to the top)
		splay(x);
		// if x has a right child, assign it to be and make its parent null
		if (x->rightChild) {
			b = x->rightChild;
			b->parent = nullptr;
		} // else, set b itself to null
		else b = nullptr;
		// set a equal to the node
		a = x;
		// a's right child become null
		a->rightChild = nullptr;
		// x becomes null
		x = nullptr;
	}
	// joins two nodes 'a' and 'b'
	Node* join(Node* a, Node* b) {
		// check if either node does not exist
		if (!a) return b;
		if (!b) return a;
		// temp node x stores the max of subtree 'a'
		Node* x = max(a);
		// bring x to the top
		splay(x);
		// x's right child is set to 'b'
		x->rightChild = b;
		// b's parent is set equal to x
		b->parent = x;
		return x;
	}
	// used for 'zag' operations (rotating node left)
	void leftRotate(Node* x) {
		
		// assign x's right child to a temp node 'y'
		Node* y = x->rightChild;
		// x's (remember this is the parent of the inserted node)
		// right child is assigned y's left child (y became the node of insertion)
		x->rightChild = y->leftChild;
		// if y has a left child, assign its parent the node x
		if (y->leftChild != nullptr) y->leftChild->parent = x;
		// y's parent (x) is assigned x's parent
		y->parent = x->parent;

		// perform insertion
		if (!x->parent) this->root = y;
		else if (x == x->parent->leftChild) x->parent->leftChild = y;
		else x->parent->rightChild = y;
		y->leftChild = x;
		x->parent = y;
	}
	// used for 'zig' operations (rotating node right)
	// *for comments on this method, see leftRotate method. Process is the same,
	// except the logic is slightly changed to work as a right rotation.
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
		// while x has a parent that is not null
		while (x->parent) {
			if (!x->parent->parent) {  // if x does not have a grandparent 
				// if x is left child perform a zig rotation, else, perform a zag rotation
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
	// generalized search method that will return the node being searched for
	Node* searchHelp(Node* node, int i) {
		
		if (node == nullptr || i == node->value) return node;
		if (i < node->value) return searchHelp(node->leftChild, i);
		return searchHelp(node->rightChild, i);
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
	// public method to call for a search of a particular node
	bool isFound(int);
};

#endif SPLAY_HPP