#ifndef SPLAYSTREE_H
#define SPLAYSTREE_H
#include "Node.h"


template <class T> class SplayTree
{

private:
    Node<T>* root;
    Node<T>* auxInsert(Node<T>* p, T key);
    Node<T>* auxRemove(Node<T>* p, T key);
    inline Node<T>* LL_Rotate(Node<T>* k2);
    inline Node<T>* RR_Rotate(Node<T>* k2);
    Node<T>* splay(Node<T>* p, T key);
    void printByLevel(Node<T>* node, int level);

public:

    SplayTree();
    ~SplayTree();

    void insert(T key);
    bool search(T key);
    void remove(T key);
    void print ();


};

#endif // SPLAYSTREE_H
