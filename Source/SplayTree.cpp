#include "../Headers/SplayTree.h"
#include <iostream>
#include <iomanip>
#include <CompareCount.h>

using namespace std;

/* LL - Rotação a Direita:
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
*/
template <class T>
inline Node<T>* SplayTree<T>::LL_Rotate(Node<T>* k2)
{
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
	Node<T>* k1 = k2->getLeft();
	k2->setLeft(k1->getRight());
	k1->setRight(k2);
	return k1;
}


/* RR - Rotação a Esquerda:
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 */

template <class T>
inline Node<T>* SplayTree<T>::RR_Rotate(Node<T>* k2)
{
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
	Node<T>* k1 = k2->getRight();
	k2->setRight(k1->getLeft());
	k1->setLeft(k2);
	return k1;
}

template <class T>
Node<T>* SplayTree<T>::splay(Node<T>* p, T key)
{
    //Caso base onde ou a árvore é vazia ou a chave da árvore é a chave procurada
    CompareCount::incrementComparison();
    CompareCount::incrementComparison();
    if(p == nullptr || p->getValue() == key)
        return p;

    CompareCount::incrementComparison();
    //Neste caso a chave está na subárvore a esquerda
    if(p->getValue() > key)
    {
        CompareCount::incrementComparison();
        //Chave não está na árvore
        if(p->getLeft() == nullptr)
            return p;

        CompareCount::incrementComparison();
        //Zig-zig
        if(p->getLeft()->getValue() > key)
        {
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            p->getLeft()->setLeft(splay(p->getLeft()->getLeft(), key));
            p = LL_Rotate(p);
        }
        //Zig-zag
        else if(p->getLeft()->getValue() < key)
        {
            CompareCount::incrementComparison();
            CompareCount::incrementCopia();
            p->getLeft()->setRight(splay(p->getLeft()->getRight(), key));

            CompareCount::incrementComparison();
            if(p->getLeft()->getRight() != nullptr)
            {
                CompareCount::incrementCopia();
                p->setLeft(RR_Rotate(p->getLeft()));
            }
        }

        CompareCount::incrementComparison();
        if(p->getLeft() == nullptr)
            return p;
        return LL_Rotate(p);
    }

    //Neste caso a chave está na subárvore a direita
    else
    {
        //Chave não está na árvore
        CompareCount::incrementComparison();
        if(p->getRight() == nullptr)
            return p;

        CompareCount::incrementComparison();
        //Zig-zag
        if(p->getRight()->getValue() > key)
        {
            CompareCount::incrementCopia();
            p->getRight()->setLeft(splay(p->getRight()->getLeft(), key));

            CompareCount::incrementComparison();
            if(p->getRight()->getLeft() != nullptr)
            {
                CompareCount::incrementCopia();
                p->setRight(LL_Rotate(p->getRight()));
            }
        }
        //Zig-zig
        else if(p->getRight()->getValue() < key)
        {
            CompareCount::incrementComparison();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            p->getRight()->setRight(splay(p->getRight()->getRight(), key));
            p = RR_Rotate(p);
        }

        CompareCount::incrementComparison();
        if(p->getRight() == nullptr)
            return p;
        return RR_Rotate(p);

    }


}

template <class T>
Node<T>* SplayTree<T>::auxInsert(Node<T>* p, T key)
{
    CompareCount::incrementComparison();
    //Caso mais simples onde a árvore está vazia
    if(p == nullptr)
    {
        CompareCount::incrementCopia();
        p = new Node<T>(key);
        return p;
    }

    CompareCount::incrementCopia();
    p = splay(p, key);

    CompareCount::incrementComparison();
    //Se a chave já está presente então retorne
    if(p->getValue() == key)
        return p;

    CompareCount::incrementCopia();
    //Caso contrário um novo nó é criado pera armazenar o novo nó
    Node<T>* no = new Node<T>(key);


    CompareCount::incrementComparison();
    if(p->getValue() > key)
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        no->setRight(p);
        no->setLeft(p->getLeft());
        p->setLeft(nullptr);
    }

    else
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        no->setLeft(p);
        no->setRight(p->getRight());
        p->setRight(nullptr);
    }

    //Novo nó se torna a raiz
    return no;
}

template <class T>
void SplayTree<T>::insert(T key)
{
    CompareCount::incrementCopia();
    BinaryTree<T>::root = auxInsert(BinaryTree<T>::root, key);
}

template <class T>
Node<T>* SplayTree<T>::auxRemove(Node<T>* p, T key)
{
    CompareCount::incrementCopia();
    Node<T>* no = new Node<T>;

    CompareCount::incrementComparison();
    //Caso mais simples onde a árvore está vazia
    if(p == nullptr)
        return nullptr;

    CompareCount::incrementCopia();
    p = splay(p, key);

    CompareCount::incrementComparison();
    if(p->getValue() != key)
        return p;

    CompareCount::incrementComparison();
    //Se a raiz não possui filho a esquerda, seu filho a direita se torna a raiz
    if(p->getLeft() == nullptr)
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        no = p;
        p = p->getRight();
    }

    else
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        no = p;
        p = splay(p->getLeft(), key);
        p->setRight(no->getRight());
    }

    delete no;
    return p;
}

template <class T>
void SplayTree<T>::remove(T key)
{
    CompareCount::incrementCopia();
    BinaryTree<T>::root = auxRemove(BinaryTree<T>::root, key);
}

template <class T>
bool SplayTree<T>::search(T key)
{
    CompareCount::incrementCopia();
    //É feito o splay e caso o elemento procurado exista ele sobe para a raiz
    BinaryTree<T>::root = splay(BinaryTree<T>::root, key);
    CompareCount::incrementComparison();
    return (BinaryTree<T>::root->getValue() == key);
}