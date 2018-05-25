#include "../Headers/SplayTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
SplayTree<T>::SplayTree()
{
    root = nullptr;
}

template <class T>
SplayTree<T>::~SplayTree()
{
    //Destrutor
}

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
	Node<T>* k1 = k2->getRight();
	k2->setRight(k1->getLeft());
	k1->setLeft(k2);
	return k1;
}

template <class T>
Node<T>* SplayTree<T>::splay(Node<T>* p, T key)
{
    //Caso base onde ou a �rvore � vazia ou a chave da �rvore � a chave procurada
    if(p == nullptr || p->getValue() == key)
        return p;

    //Neste caso a chave est� na sub�rvore a esquerda
    if(p->getValue() > key)
    {
        //Chave n�o est� na �rvore
        if(p->getLeft() == nullptr)
            return p;

        //Rota��o left-left
        if(p->getLeft()->getValue() > key)
        {
            p->getLeft()->setLeft(splay(p->getLeft()->getLeft(), key));
            p = LL_Rotate(p);
        }
        //Rota��o left-right
        else if(p->getLeft()->getValue() < key)
        {
            p->getLeft()->setRight(splay(p->getLeft()->getRight(), key));

            if(p->getLeft()->getRight() != nullptr)
                p->setLeft(RR_Rotate(p->getLeft()));
        }

        if(p->getLeft() == nullptr)
            return p;
        return LL_Rotate(p);
        //return ((p->getLeft() == nullptr) ? p : LL_Rotate(p));
    }

    //Neste caso a chave est� na sub�rvore a direita
    else
    {
        //Chave n�o est� na �rvore
        if(p->getRight() == NULL)
            return p;

        //Rota��o right-left
        if(p->getRight()->getValue() > key)
        {
            p->getRight()->setLeft(splay(p->getRight()->getLeft(), key));

            if(p->getRight()->getLeft() != NULL)
                p->setRight(LL_Rotate(p->getRight()));
        }
        //Rota��o right-right
        else if(p->getRight()->getValue() < key)
        {
            p->getRight()->setRight(splay(p->getRight()->getRight(), key));
            p = RR_Rotate(p);
        }

        if(p->getRight() == nullptr)
            return p;
        return RR_Rotate(p);

        //return (p->getRight() == NULL) ? p : RR_Rotate(p);
    }


}

template <class T>
Node<T>* SplayTree<T>::auxInsert(Node<T>* p, T key)
{
    //Caso mais simples onde a �rvore est� vazia
    if(p == nullptr){
        p = new Node<T>(key);
        return p;
    }

    p = splay(p, key);

    if(p->getValue() == key)
        return p;

    Node<T>* no = new Node<T>(key);

    if(p->getValue() > key)
    {
        no->setRight(p);
        no->setLeft(p->getLeft());
        p->setLeft(nullptr);
    }

    else
    {
        no->setLeft(p);
        no->setRight(p->getRight());
        p->setRight(nullptr);
    }

    return no;
}

template <class T>
void SplayTree<T>::insert(T key)
{
    root = auxInsert(root, key);
}

template <class T>
Node<T>* SplayTree<T>::auxRemove(Node<T>* p, T key)
{
    Node<T>* no = new Node<T>;

    //Caso mais simples onde a �rvore est� vazia
    if(p == nullptr)
        return nullptr;

    p = splay(p, key);

    if(p->getValue() != key)
        return p;

    if(p->getLeft() == nullptr)
    {
        no = p;
        p = p->getRight();
    }

    else
    {
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
    root = auxRemove(root, key);
}

template <class T>
bool SplayTree<T>::search(T key)
{
    root = splay(root, key);
    return (root->getValue() == key);
}


template  <class T>
void SplayTree<T>::print()
{
    printByLevel(root, 0);
}

template <class T>
void SplayTree<T>::printByLevel(Node<T> *p, int level)
{
    if (p != nullptr)
    {
        cout << "(" << level << ")";
        for(int i = 1; i <= level; i++)
            cout << "--";
        cout << " ";
        cout << p->getValue() << endl;
        printByLevel(p->getLeft(), level+1);
        printByLevel(p->getRight(), level+1);
    }
}