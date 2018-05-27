//
// Created by edson on 24/05/18.
//

#include "../Headers/NodeRB.h"

template<class T>
NodeRB<T>::NodeRB(T data)
{
    this->value = data;
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
    this->red = true;
}

template<class T>
void NodeRB<T>::setRight(NodeRB<T>* right)
{
    this->right = right;
}

template<class T>
void NodeRB<T>::setLeft(NodeRB<T>* left)
{
    this->left = left;
}

template<class T> T NodeRB<T>::getValue()
{
    return value;
}

template<class T>
NodeRB<T> *NodeRB<T>::getRight() const {
    return right;
}

template<class T>
NodeRB<T> *NodeRB<T>::getLeft() const {
    return left;
}

template<class T>
void NodeRB<T>::setValue(T value) {
    this->value = value;
}

template<class T>
NodeRB<T> *NodeRB<T>::getParent() const {
    return parent;
}

template<class T>
void NodeRB<T>::setParent(NodeRB<T> *parent) {
    this->parent = parent;
}

template<class T>
bool NodeRB<T>::isRed() const {
    if(this == nullptr)
        return false;
    return red;
}

template<class T>
void NodeRB<T>::setRed(bool red) {
    this->red = red;
}
