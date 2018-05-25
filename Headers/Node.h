//
// Created by edson on 15/05/18.
//

#ifndef TREES_NODE_H
#define TREES_NODE_H

#include <iostream>

using namespace std;

template <class T> class Node
{
	protected:
	T value;
	Node<T>* right;
	Node<T>* left;

	public:
	Node<T>() = default;
	Node<T>(T data);
	~Node<T>() = default;
	void setRight(Node<T>* right);
	void setLeft(Node<T>* left);
	T getValue();

	Node<T> *getRight();

	Node<T> *getLeft();

	void setValue(T value);
};
#endif //TREES_NODE_H
