//
// Created by edson on 15/05/18.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"

template <class T> class BinaryTree
{
	public:
	BinaryTree<T>();
	virtual void insert(T value);
	Node<T>* search(T value);
	void remove(T value);
	void print();

	protected:
	Node<T>* root;

	private: //funcoes auxiliares
	Node<T>* auxInsert(Node<T>* node, T value);
	Node<T>* auxSearch(Node<T>* root, T value);
	Node<T>* auxRemove(Node<T>* node, T value);
	Node<T>* removeLeaf(Node<T>* node);
	Node<T>* remove1Son(Node<T>* node);
	Node<T>* menorSubArvDireita(Node<T>* node);
	void printByLevel(Node<T>* node, int level);

};

#include "../Source/BinaryTree.cpp"

#endif //TREES_BINARYTREE_H
