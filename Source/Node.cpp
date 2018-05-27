//
// Created by edson on 18/05/18.
//

#ifndef NODE_CPP
#define NODE_CPP

#include "../Headers/Node.h"

template<class T> Node<T>::Node()
{
    this->left = nullptr;
    this->right = nullptr;
}

template<class T> Node<T>::Node(T data)
{
    this->value = data;
    this->right = nullptr;
    this->left = nullptr;
}

template<class T>
Node<T>* Node<T>::getRight()
{
	return right;
}

template<class T>
void Node<T>::setRight(Node<T>* node)
{
    this->right = node;
}

template<class T>
Node<T>* Node<T>::getLeft()
{
	return left;
}

template<class T>
void Node<T>::setLeft(Node<T>* node)
{
    this->left = node;
}

template<class T> 
T Node<T>::getValue()
{
    return value;
}

template<class T>
void Node<T>::setValue(T value)
{
	Node::value = value;
}

#endif