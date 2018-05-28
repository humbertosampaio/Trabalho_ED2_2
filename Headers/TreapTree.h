#ifndef TRABALHO_ED2_2_TREAPTREE_H
#define TRABALHO_ED2_2_TREAPTREE_H

#include <vector>
#include "TreapNode.h"
#include "../Source/BinaryTree.cpp"

template <class T> class TreapTree : public BinaryTree<T>
{
	public:
	void insert(T val);
	void insert(vector<T> values);
	void remove(T val);
	void remove(vector<T> values);
	TreapNode<T>* search(T val);

	private:
	TreapNode<T>* getRoot() { return (TreapNode<T>*)BinaryTree<T>::root; }

	TreapNode<T>* auxInsert(TreapNode<T>* p, T val);
	TreapNode<T>* auxRemove(TreapNode<T>* p, T val);
	
	TreapNode<T>* leftRotate(TreapNode<T>* y);
	TreapNode<T>* rightRotate(TreapNode<T>* y);
};

#endif //TRABALHO_ED2_2_TREAPTREE_H
