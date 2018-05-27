//
// Created by edson on 15/05/18.
//

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <class T> class Node
{
	protected:
	T value;
	Node<T>* right;
	Node<T>* left;

	public:
	Node<T>();
	Node<T>(T data);
	~Node<T>() = default;
	void setRight(Node<T>* right);
	void setLeft(Node<T>* left);
	T getValue();

    virtual Node<T> *getRight();

	virtual Node<T> *getLeft();

	void setValue(T value);


};

#include "../Source/Node.cpp"

#endif //TREES_NODE_H
