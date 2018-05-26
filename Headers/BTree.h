//
// Created by viniman on 5/26/18.
//

#ifndef TRABALHO_ED2_2_BTREE_H
#define TRABALHO_ED2_2_BTREE_H


#include <iostream>
#include "NodeB.h"

template <class T> class BTree {
private:
    NodeB<T>* raiz;
    void deletaArvore(NodeB<T>* no);

public:
    BTree<T>();
    ~BTree<T>();
    void insere(T valor);
    bool find(T valor);
    NodeB<T>* insereNo(NodeB<T> *no, T valor);
    void insereRecursivo(NodeB<T> *no, T valor);
    T split(NodeB<T> *n, NodeB<T> **novoNo);
    NodeB<T>* find(NodeB<T> *n, T valor);
    NodeB<T>** getRaiz();
    void imprime();
    void imprimePorNivel(NodeB<T> *p, int nivel);
    void inOrder();
    void inOrder(NodeB<T> *p);


};


#endif //TRABALHO_ED2_2_BTREE_H
