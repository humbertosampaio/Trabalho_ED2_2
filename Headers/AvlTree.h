//
// Created by viniman on 5/19/18.
//

#ifndef TRABALHO_ED2_2_AVLTREE_H
#define TRABALHO_ED2_2_AVLTREE_H

#define PRE_ORDER 1
#define IN_ORDER 2
#define POST_ORDER 3

#include "AvlNode.h"
#include "../Source/BinaryTree.cpp"

template <class T> class AvlTree : public BinaryTree<T>
{
	public:
	//AvlTree();
	//virtual ~AvlTree();s

	void clear();
	void insert(T val);
	void remove(T val);
	bool busca(T val);
	void printByOrder(int caseOrder);

	private:
	// Methods
	AvlNode<T>* getRoot() { return (AvlNode<T>*)BinaryTree<T>::root; }
	AvlNode<T>* clear(AvlNode<T> *raiz);
	AvlNode<T>* auxInsere(AvlNode<T> *no, T val);
	AvlNode<T>* auxRemove(AvlNode<T> *no, T val);
	bool auxBusca(AvlNode<T> *p, T val);
	AvlNode<T>* leftRotate(AvlNode<T> *raiz);
	AvlNode<T>* rightRotate(AvlNode<T> *y);
	AvlNode<T>* rightLeftRotate(AvlNode<T> *y);
	AvlNode<T>* leftRightRotate(AvlNode<T> *y);

	int max(int &x, int &y);
	int calcAltura(AvlNode<T> *p);
	int calcFB(AvlNode<T> *no);
	AvlNode<T> *balance(AvlNode<T> *no);
	void postOrder(AvlNode<T> *p);
	void inOrder(AvlNode<T> *p);
	void preOrder(AvlNode<T> *p);
};

#endif //TRABALHO_ED2_2_AVLTREE_H
