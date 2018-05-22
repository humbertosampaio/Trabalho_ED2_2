//
// Created by viniman on 5/19/18.
//

#ifndef TRABALHO_ED2_2_AVLTREE_H
#define TRABALHO_ED2_2_AVLTREE_H

#define PRE_ORDER 1
#define IN_ORDER 2
#define POST_ORDER 3

#include "NodeAvl.h"
#include "../Source/BinaryTree.cpp"

template <class T> class AvlTree : public BinaryTree<T> {
public:
    AvlTree();
    virtual ~AvlTree();

    void clear();
    /*
    void insert(int val);
    void remove(int val);
    bool busca(int val);
    void printByLevel();
    void printByOrder(int caseOrder);
    //NodeAvl* getRaiz() { return raiz; }
    */
private:

    NodeAvl* raiz;
    /*
    NodeAvl* auxInsere(NodeAvl *no, int val);
    NodeAvl *auxRemove(NodeAvl *no, int val);
    bool auxBusca(NodeAvl *p, int val);
    NodeAvl* leftRotate(NodeAvl *raiz);
    NodeAvl* rightRotate(NodeAvl *y);
    NodeAvl *rightLeftRotate(NodeAvl *y);
    NodeAvl *leftRightRotate(NodeAvl *y);
    int max(int &x, int &y);
    int calcAltura(NodeAvl *p);
    int calcFB(NodeAvl *no);
    NodeAvl *balance(NodeAvl *no);
    void imprimePorNivel(NodeAvl *p, int nivel);
    void postOrder(NodeAvl *p);
    void inOrder(NodeAvl *p);
    void preOrder(NodeAvl *p);
     */
    NodeAvl * clear(NodeAvl *raiz);

};


#endif //TRABALHO_ED2_2_AVLTREE_H
