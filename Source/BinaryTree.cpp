//
// Created by edson on 15/05/18.
//

#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include <CompareCount.h>
#include "../Headers/BinaryTree.h"

template<class T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}

template<class T>
BinaryTree<T>::~BinaryTree<T>()
{
	clear();
}

template<class T>
void BinaryTree<T>::clear()
{
	root = auxClear(root);
}

template<class T>
Node<T>* BinaryTree<T>::auxClear(Node<T>* root)
{
	if (root != nullptr)
	{
		root->setLeft(auxClear(root->getLeft()));
		root->setRight(auxClear(root->getRight()));
		delete root;
		root = nullptr;
	}
	return root;
}

template<class T>
void BinaryTree<T>::insert(T value)
{
    CompareCount::incrementCopia();
    root = auxInsert(root, value);
}

template<class T>
Node<T>* BinaryTree<T>::auxInsert(Node<T> *node, T value)
{
    CompareCount::incrementComparison();
    if(node == nullptr)
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        node = new Node<T>(value);
        node->setLeft(nullptr);
        node->setRight(nullptr);
    }
    else if(value < node->getValue())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        node->setLeft(auxInsert(node->getLeft(), value));
    }
    else
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        node->setRight(auxInsert(node->getRight(), value));
    }

    return node;
}

template<class T>
Node<T>* BinaryTree<T>::search(T &value)
{
    CompareCount::incrementCopia();
	Node<T>* node = auxSearch(root, value);
	//if (node == nullptr)
		//cout << "No de valor " + to_string(value) + " nao encontrado na arvore." << endl;
	return node;
}

template<class T>
Node<T>* BinaryTree<T>::auxSearch(Node<T>* root, T value)
{
    CompareCount::incrementComparison();
    CompareCount::incrementComparison();
    if (root == nullptr || root->getValue() == value)
        return root;

    CompareCount::incrementComparison();
    /// value menor que valor de root
    if (root->getValue() < value)
    {
        CompareCount::incrementCopia();
        return auxSearch(root->getRight(), value);
    }

    CompareCount::incrementCopia();
    /// value maior que valor de root
    return auxSearch(root->getLeft(), value);
}

template <class T>
void BinaryTree<T>::remove(T value)
{
    auxRemove(root, value);
}

template<class T>
Node<T>* BinaryTree<T>::removeLeaf(Node<T> *p)
{
    delete p;
    return nullptr;
}

template<class T>
Node<T>* BinaryTree<T>::remove1Son(Node<T> *p)
{
    Node<T> *aux;
    CompareCount::incrementComparison();
    if(p->getLeft() == nullptr)
    {
        CompareCount::incrementCopia();
        aux = p->getRight();
    }
    else
    {
        CompareCount::incrementCopia();
        aux = p->getLeft();
    }
    delete p;
    return aux;
}

template <class T>
Node<T>* BinaryTree<T>::menorSubArvDireita(Node<T>* node)
{
    CompareCount::incrementCopia();
    Node<T> *aux = node->getRight();
    CompareCount::incrementComparison();
    while(aux->getLeft() != nullptr)
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        aux = aux->getLeft();
    }
    return aux;
}

template<class T>
Node<T>* BinaryTree<T>::auxRemove(Node<T>* node, T value)
{
    CompareCount::incrementComparison();
    if(node == nullptr)
        return nullptr;
    else if(value < node->getValue())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        node->setLeft(auxRemove(node->getLeft(), value));
    }
    else if(value > node->getValue())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        node->setRight(auxRemove(node->getRight(), value));
    }
    else
    {
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            CompareCount::incrementCopia();
            node = removeLeaf(node);
        }
        else if((node->getLeft() == nullptr) || (node->getRight() == nullptr))
        {
            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            CompareCount::incrementCopia();
            node = remove1Son(node);
        }
        else
        {
            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            Node<T> *aux = menorSubArvDireita(node);
            node->setValue(aux->getValue());
            aux->setValue(value);
            node->setRight(auxRemove(node->getRight(), value));
        }
    }
    return node;
}

template <class T>
void BinaryTree<T>::print()
{
    printByLevel(root, 0);
}

template <class T>
void BinaryTree<T>::printByLevel(Node<T> *p, int level)
{
    if (p != nullptr)
    {
        cout << "(" << level << ")";
        for(int i = 1; i <= level; i++)
			cout << "#";
        cout << p->getValue() << endl;
        printByLevel(p->getLeft(), level+1);
        printByLevel(p->getRight(), level+1);
    }
}



template<class T>
void BinaryTree<T>::printByOrder(int caseOrder)
{
    switch (caseOrder)
    {
        case PRE_ORDER:
            preOrder(BinaryTree<T>::root);
            break;
        case IN_ORDER:
            inOrder(BinaryTree<T>::root);
            break;
        case POST_ORDER:
            postOrder(BinaryTree<T>::root);
            break;
        default:
            cout << "Nao existe esse codigo de operacao" << endl;
    }
    cout << endl;
}


template<class T>
void BinaryTree<T>::preOrder(Node<T>* p)
{
    if (p != nullptr)
    {
        cout << p->getValue() << " ";
        preOrder(p->getLeft());
        preOrder(p->getRight());
    }
}


template<class T>
void BinaryTree<T>::inOrder(Node<T>* p)
{
    if (p != nullptr)
    {
        inOrder(p->getLeft());
        cout << p->getValue() << " ";
        inOrder(p->getRight());
    }
}

template<class T>
void BinaryTree<T>::postOrder(Node<T>* p)
{
    if (p != nullptr)
    {
        postOrder(p->getLeft());
        postOrder(p->getRight());
        cout << p->getValue() << " ";
    }
}

#endif