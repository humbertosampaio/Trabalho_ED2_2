#ifndef TRABALHO_ED2_2_AVLNODE_CPP
#define TRABALHO_ED2_2_AVLNODE_CPP

#include "../Headers/AvlNode.h"

//template<class T> AvlNode<T>::Node(T data)
//{
//	this->value = data;
//	this->right = nullptr;
//	this->left = nullptr;
//}

template<class T>
int AvlNode<T>::getHeight()
{
	if (this == nullptr)
		return 0;
	else
		return height;
}

#endif
