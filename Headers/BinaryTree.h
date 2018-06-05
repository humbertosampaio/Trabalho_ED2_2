//
// Created by edson on 15/05/18.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#define PRE_ORDER 1
#define IN_ORDER 2
#define POST_ORDER 3

#include "Node.h"

template <class T> class BinaryTree
{
	public:
	BinaryTree<T>();
	~BinaryTree<T>();
	void clear();
	virtual void insert(T value);
	Node<T>* search(T &value);
    virtual void remove(T value);
	void print();
	void printByOrder(int caseOrder);

	protected:
	Node<T>* root;

	private:
	Node<T>* auxClear(Node<T>* root);
	Node<T>* auxInsert(Node<T>* node, T value);
	Node<T>* auxSearch(Node<T>* root, T value);
	Node<T>* auxRemove(Node<T>* node, T value);
	Node<T>* removeLeaf(Node<T>* node);
	Node<T>* remove1Son(Node<T>* node);
	Node<T>* menorSubArvDireita(Node<T>* node);
	void printByLevel(Node<T>* p, int level);

    void preOrder(Node<T> *p);
	void inOrder(Node<T> *p);
	void postOrder(Node<T> *p);
};

#endif //TREES_BINARYTREE_H
