//
// Created by edson on 15/05/18.
//

#ifndef TREES_NODE_H
#define TREES_NODE_H

#include <iostream>

using namespace std;

template <class T> class Node {
protected:
    T value;
    Node<T>* right;
    Node<T>* left;
public:
    Node<T>(T data);
    void setRight(Node<T>* right);
    void setLeft(Node<T>* left);
    T getValue();

    virtual Node<T> *getRight() = 0;
    virtual Node<T> *getLeft() = 0;

    void setValue(T value);
};
#endif //TREES_NODE_H
