
#include "../Headers/TreapTree.h"

using namespace std;

template<class T>
void TreapTree<T>::insert(T val)
{
    CompareCount::incrementCopia();
	BinaryTree<T>::root = auxInsert(getRoot(), val);
}

template<class T>
void TreapTree<T>::insert(vector<T> values)
{
	for (T val : values)
		insert(val);
}

template<class T>
TreapNode<T>* TreapTree<T>::auxInsert(TreapNode<T>* p, T val)
{
    CompareCount::incrementComparison();
	if (p == nullptr)
    {
        CompareCount::incrementCopia();
        return new TreapNode<T>(val);
    }

    CompareCount::incrementComparison();
	if (val <= p->getValue())
	{
        CompareCount::incrementCopia();
		// Insere na sub-arvore da esquerda
		p->setLeft(auxInsert(p->getLeft(), val));


        CompareCount::incrementComparison();
		// Rotaciona se a Heap for violada
		if (p->getLeft()->getPriority() > p->getPriority())
        {
            CompareCount::incrementCopia();
            p = rightRotate(p);
        }
	}
	else
	{
        CompareCount::incrementCopia();
		// Insere na sub-arvore da direita
		p->setRight(auxInsert(p->getRight(), val));

        CompareCount::incrementComparison();
		// Rotaciona se a Heap for violada
		if (p->getRight()->getPriority() > p->getPriority())
        {
            CompareCount::incrementCopia();
            p = leftRotate(p);
        }
	}
	return p;
}

template<class T>
void TreapTree<T>::remove(T val)
{
    CompareCount::incrementCopia();
	BinaryTree<T>::root = auxRemove(getRoot(), val);
}

template<class T>
void TreapTree<T>::remove(vector<T> values)
{
	for(T value : values)
    {
        CompareCount::incrementComparison();
        remove(value);
    }
    CompareCount::incrementComparison();
}

template<class T>
TreapNode<T>* TreapTree<T>::auxRemove(TreapNode<T>* p, T val)
{
    CompareCount::incrementComparison();
	if (p == nullptr)
		return p;

    CompareCount::incrementComparison();
	// Procurando val...
	if (val < p->getValue())
    {
        CompareCount::incrementCopia();
        p->setLeft(auxRemove(p->getLeft(), val));
    }
	else if (val > p->getValue())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        p->setRight(auxRemove(p->getRight(), val));
    }

	// val encontrado
	// Se filho da esquerda for nulo
	else if (p->getLeft() == nullptr)
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
		TreapNode<T>* temp = p->getRight();
		delete(p);
		p = temp;  // Filho da direita substitui p
	}

	// Se filho da direita for nulo
	else if (p->getRight() == nullptr)
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
		TreapNode<T>* temp = p->getLeft();
		delete(p);
		p = temp;  // Filho da esquerda substitui p
	}

	// Se o no de val tem dois filhos, chama recursivamente 
	// descendo o no ate um dos casos anteriores
	else if (p->getLeft()->getPriority() < p->getRight()->getPriority())
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
		p = leftRotate(p);
		p->setLeft(auxRemove(p->getLeft(), val));
	}
	else
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
		p = rightRotate(p);
		p->setRight(auxRemove(p->getRight(), val));
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
	}

	return p;
}


template<class T>
TreapNode<T>* TreapTree<T>::search(T val)
{
	return (TreapNode<T>*)BinaryTree<T>::search(val);
}

/** T1, T2 and T3 are subtrees of the tree rooted with y
   (on left side) or x (on right side)
       y                               x
      / \        Right Rotation       / \
     x   T3      � � � � � � � >     T1  y
    / \          < - - - - - - -        / \
   T1  T2        Left Rotation        T2  T3		 */

template<class T>
TreapNode<T>* TreapTree<T>::leftRotate(TreapNode<T>* y)
{
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
	TreapNode<T>* x = y->getRight();
	y->setRight(x->getLeft());
	x->setLeft(y);

	return x;
}

template<class T>
TreapNode<T>* TreapTree<T>::rightRotate(TreapNode<T>* y)
{
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
	TreapNode<T>* x = y->getLeft();
	y->setLeft(x->getRight());
	x->setRight(y);

	return x;
}