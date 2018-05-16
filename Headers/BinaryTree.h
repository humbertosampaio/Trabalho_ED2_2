//
// Created by edson on 15/05/18.
//

#ifndef TREES_BINARYTREE_H
#define TREES_BINARYTREE_H

#include "Node.h"

template <class T> class BinaryTree {
private:
    Node<T>* root;

public:
    BinaryTree<T>();
    virtual void insert(Node<T> node);
    virtual void remove(T value);
};

#endif //TREES_BINARYTREE_H
