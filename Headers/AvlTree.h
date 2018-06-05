//
// Created by viniman on 5/19/18.
//

#ifndef TRABALHO_ED2_2_AVLTREE_H
#define TRABALHO_ED2_2_AVLTREE_H

#include "AvlNode.h"
#include "../Source/BinaryTree.cpp"

template <class T> class AvlTree : public BinaryTree<T>
{
	public:
	AvlTree<T>();
	AvlTree<T>(bool modified);
	void insert(T val);
	void remove(T val);
	bool search(T &val);

	private:
	/// Variáveis para setar a AVL Modificada
	unsigned short fatorBalancNormal;
	bool modifiedAvl;

	AvlNode<T>* getRoot() { return (AvlNode<T>*)BinaryTree<T>::root; }
	AvlNode<T>* auxInsere(AvlNode<T> *no, T val);
	AvlNode<T>* auxRemove(AvlNode<T> *no, T val);
	bool auxSearch(AvlNode<T> *p, T &val);
	AvlNode<T>* leftRotate(AvlNode<T> *raiz);
	AvlNode<T>* rightRotate(AvlNode<T> *y);
	AvlNode<T>* rightLeftRotate(AvlNode<T> *y);
	AvlNode<T>* leftRightRotate(AvlNode<T> *y);

	int max(int &x, int &y);
	int calcAltura(AvlNode<T> *p);
	int calcFB(AvlNode<T> *no);
	AvlNode<T>* balance(AvlNode<T> *no);
};

#endif //TRABALHO_ED2_2_AVLTREE_H
