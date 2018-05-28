
#ifndef TRABALHO_ED2_2_TREAPNODE_H
#define TRABALHO_ED2_2_TREAPNODE_H

#define RANDOM_SEED std::chrono::system_clock::now().time_since_epoch().count()
#include "Node.h"

template <class T> class TreapNode : public Node<T>
{
	public:
	explicit TreapNode(T val)
	{
		this->value = val;
		this->priority = (int)RANDOM_SEED % 100;
	}
	TreapNode<T>* getLeft() { return (TreapNode<T>*)(Node<T>::left); }
	TreapNode<T>* getRight() { return (TreapNode<T>*)(Node<T>::right); }
	void setLeft(TreapNode<T>* node) { (TreapNode<T>*)(Node<T>::left = node); }
	void setRight(TreapNode<T>* node) { (TreapNode<T>*)(Node<T>::right = node); }
	int getPriority() { return this->priority; }
	void setPriority(int newPriority) { this->priority = new newPriority; }

	private:
	int priority;
};

//#include "../Source/TreapNode.cpp"

#endif //TRABALHO_ED2_2_TREAPNODE_H
