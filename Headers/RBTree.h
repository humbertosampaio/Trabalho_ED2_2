//
// Created by edson on 24/05/18.
//

#ifndef ARVORES_ED2_RBTREE_H
#define ARVORES_ED2_RBTREE_H

#include "../Source/NodeRB.cpp"
//#include "NodeRB.h"
#include <iostream>

using namespace std;

template <class T> class RBTree {
public:
    RBTree<T>();
    void insert (T value);
    NodeRB<T>* search(T value);
    void remove (T value);
    void print ();

private:
    NodeRB<T>* root;

private: //funcoes auxiliares
    NodeRB<T>* auxInsert(NodeRB<T>* node, NodeRB<T>* newNode);
    NodeRB<T>* auxSearch(NodeRB<T>* root, T value);
    NodeRB<T>* auxRemove(NodeRB<T>* node, T value);
    NodeRB<T>* removeLeaf(NodeRB<T>* node);
    NodeRB<T>* remove1Son(NodeRB<T>* node);
    NodeRB<T>* menorSubArvDireita(NodeRB<T>* node);
    NodeRB<T>* maiorSubArvEsq(NodeRB<T>* node);
    void printByLevel(NodeRB<T>* node, int level);
    void fixInsert(NodeRB<T> *&root, NodeRB<T> *&newNode);
    void fixRemove(NodeRB<T> *&node, NodeRB<T> *& parent);
    void removeCase1 (NodeRB<T> *&node, NodeRB<T> *& parent);

    void rotateRight(NodeRB<T> *&root, NodeRB<T> *&newNode);
    void rotateLeft(NodeRB<T> *&root, NodeRB<T> *&pt);

    void swapColors(NodeRB<T>* node1, NodeRB<T>* node2);
};


#endif //ARVORES_ED2_RBTREE_H
