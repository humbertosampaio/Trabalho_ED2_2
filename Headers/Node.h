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
    unsigned int height;
public:
    Node<T>();
    Node<T>(T data);
    void setRight(Node<T>* right);
    void setLeft(Node<T>* left);
    T getValue();

    Node<T> *getRight() const;

    Node<T> *getLeft() const;

    void setValue(T value);
};
#endif //TREES_NODE_H
