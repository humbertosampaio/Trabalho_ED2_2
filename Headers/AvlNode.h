//
// Created by viniman on 5/19/18.
//

#include "Node.h"

#ifndef TRABALHO_ED2_2_AVLNODE_H
#define TRABALHO_ED2_2_AVLNODE_H

template <class T> class AvlNode : public Node<T>
{
	public:
	AvlNode(T val) : Node<T>(val) { };
	int getHeight();
	AvlNode<T>* getLeft() { return (AvlNode<T>*)(Node<T>::left); }
	AvlNode<T>* getRight() { return (AvlNode<T>*)(Node<T>::right); }
	void setHeight(int height) { this->height = height; }
	void setLeft(AvlNode<T> *node) { (AvlNode<T>*)(Node<T>::left = node); }
	void setRight(AvlNode<T> *node) { (AvlNode<T>*)(Node<T>::right = node); }

	private:
	int height;
};

#include "../Source/AvlNode.cpp"

#endif //TRABALHO_ED2_2_AVLNODE_H
