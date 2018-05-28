#ifndef SPLAYSTREE_H
#define SPLAYSTREE_H

#include "Node.h"
#include "../Source/BinaryTree.cpp"

template <class T> class SplayTree : public BinaryTree<T>
{
	private:
	Node<T>* auxInsert(Node<T>* p, T key);
	Node<T>* auxRemove(Node<T>* p, T key);
	inline Node<T>* LL_Rotate(Node<T>* k2);
	inline Node<T>* RR_Rotate(Node<T>* k2);
	Node<T>* splay(Node<T>* p, T key);

	public:
	void insert(T key);
	bool search(T key);
	void remove(T key);
};

#endif // SPLAYSTREE_H
