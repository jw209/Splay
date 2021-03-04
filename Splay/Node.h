/*
*	Node.hpp
* 
*	Declaration file for Node class.
*/
#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
	int value;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
};

#endif //NODE_HPP_INCLUDED