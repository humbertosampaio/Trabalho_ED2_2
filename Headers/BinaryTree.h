//
// Created by edson on 15/05/18.
//

#ifndef TREES_BINARYTREE_H
#define TREES_BINARYTREE_H

#include "Node.h"

template <class T> class BinaryTree {

public:
    BinaryTree<T>();
    virtual void insert (Node<T>* value);
    Node<T>* search(T value);
    void remove (T value);
    void print ();

protected:
    Node<T>* root;
    Node<T>* leftRotate(Node<T> *y);
    Node<T>* rightRotate(Node<T> *y);
    Node<T>* rightLeftRotate(Node<T> *y);
    Node<T>* leftRightRotate(Node<T> *y);

private: //funcoes auxiliares
    Node<T>* auxInsert(Node<T>* node, Node<T>* value);
    Node<T>* auxSearch(Node<T>* root, T value);
    Node<T>* auxRemove(Node<T>* node, T value);
    Node<T>* removeLeaf(Node<T>* node);
    Node<T>* remove1Son(Node<T>* node);
    Node<T>* menorSubArvDireita(Node<T>* node);
    void printByLevel(Node<T>* node, int level);

};

#endif //TREES_BINARYTREE_H
