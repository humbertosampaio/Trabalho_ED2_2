//
// Created by edson on 15/05/18.
//

#include "../Headers/BinaryTree.h"

template<class T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}

template<class T>
void BinaryTree<T>::insert(Node<T>* value)
{
    root = auxInsert(root, value);
}

template<class T>
Node<T>* BinaryTree<T>::auxInsert(Node<T>* node, Node<T>* value)
{
    if(node == nullptr)
        node = value;

    else if(value->getValue() < node->getValue())
        node->setLeft(auxInsert(node->getLeft(), value));
    else if (value->getValue() > node->getValue())
        node->setRight(auxInsert(node->getRight(), value));
    return node;
}

template<class T>
Node<T>* BinaryTree<T>::search(T value)
{
    return auxSearch(root, value);
}

template<class T>
Node<T>* BinaryTree<T>::auxSearch(Node<T>* root, T value)
{
    if (root == nullptr || root->getValue() == value)
        return root;

    // value menor que valor de root
    if (root->getValue() < value)
        return auxSearch(root->getRight(), value);

    //value maior que valor de root
    return auxSearch(root->getLeft(), value);
}

template <class T>
void BinaryTree<T>::remove (T value)
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
    if(p->getLeft() == nullptr)
        aux = p->getRight();
    else
        aux = p->getLeft();
    delete p;
    return aux;
}

template <class T>
Node<T>* BinaryTree<T>::menorSubArvDireita(Node<T>* node)
{
    Node<T> *aux = node->getRight();
    while(aux->getLeft() != nullptr)
        aux = aux->getLeft();
    return aux;
}

template<class T>
Node<T>* BinaryTree<T>::auxRemove(Node<T>* node, T value)
{
    if(node == nullptr)
        return nullptr;
    else if(value < node->getValue())
        node->setLeft(auxRemove(node->getLeft(), value));
    else if(value > node->getValue())
        node->setRight(auxRemove(node->getRight(), value));
    else
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr)
            node = removeLeaf(node);
        else if((node->getLeft() == nullptr) || (node->getRight() == nullptr))
            node = remove1Son(node);
        else
        {
            Node<T> *aux = menorSubArvDireita(node);
            node->setValue(aux->getValue());
            aux->setValue(value);
            node->setRight(auxRemove(node->getRight(), value));
        }
    }
    return node;
}

template  <class T>
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
            cout << "--";
        cout << " ";
        cout << p->getValue() << endl;
        printByLevel(p->getLeft(), level+1);
        printByLevel(p->getRight(), level+1);
    }
}

// Left Left Case (RotacaoRR)
template <class T>
Node<T>* BinaryTree<T>::leftRotate(Node<T> *raiz)
{
    Node<T>* no = raiz->getRight();
    raiz->setRight(no->getLeft());
    no->setLeft(raiz);
    return no;

}

// Left Left Case (RotacaoLL)
template <class T>
Node<T>* BinaryTree<T>::rightRotate(Node<T> *y)
{
    Node<T>* x = y->getLeft();
    y->setLeft(x->getRight());
    x->setRight(y);
    return x;
}

// Left Right Case (RotacaoLR)
template <class T>
Node<T>* BinaryTree<T>::leftRightRotate(Node<T> *y)
{
    y->setLeft(leftRotate(y->getLeft()));
    return rightRotate(y);
}

// Right Left Case (RotacaoRL)
template <class T>
Node<T>* BinaryTree<T>::rightLeftRotate(Node<T> *y)
{
    y->setRight(rightRotate(y->getRight()));
    return leftRotate(y);
}