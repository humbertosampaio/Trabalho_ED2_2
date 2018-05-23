//
// Created by edson on 18/05/18.
//

#include "../Headers/Node.h"

template<class T>
Node<T>::Node(T data)
{
    this->value = data;
    this->right = nullptr;
    this->left = nullptr;
}

template<class T>
void Node<T>::setRight(Node<T>* right)
{
    this->right = right;
}

template<class T>
void Node<T>::setLeft(Node<T>* left)
{
    this->left = left;
}

template<class T> T Node<T>::getValue()
{
    return value;
}

template<class T>
void Node<T>::setValue(T value) {
    Node::value = value;
}
