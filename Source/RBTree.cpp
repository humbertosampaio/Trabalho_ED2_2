//
// Created by edson on 24/05/18.
//

#include <CompareCount.h>
#include "../Headers/RBTree.h"


template<class T>
RBTree<T>::RBTree()
{
    root = nullptr;
}

template<class T>
void RBTree<T>::insert (T value)
{
    CompareCount::incrementCopia();
    NodeRB<T>* newNode = new NodeRB<T>(value);
    CompareCount::incrementCopia();
    root = auxInsert(root, newNode);
    fixInsert(root, newNode);
}

template<class T>
NodeRB<T>* RBTree<T>::auxInsert(NodeRB<T> *node, NodeRB<T>* newNode)
{
    CompareCount::incrementComparison();
    if(node == nullptr)
    {
        CompareCount::incrementCopia();
        node = newNode;
    }

    CompareCount::incrementComparison();
    if(newNode->getValue() < node->getValue()) {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        node->setLeft(auxInsert(node->getLeft(), newNode));
        node->getLeft()->setParent(node);
    }
    else if (newNode->getValue() > node->getValue()) {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        node->setRight(auxInsert(node->getRight(), newNode));
        node->getRight()->setParent(node);
    }

    return node;
}

template <class T>
void RBTree<T>::rotateLeft(NodeRB<T> *&root, NodeRB<T> *&pt)
{
    NodeRB<T> *pt_right = pt->getRight();
    CompareCount::incrementCopia();

    pt->setRight(pt_right->getLeft());
    CompareCount::incrementCopia();

    CompareCount::incrementComparison();
    if (pt->getRight() != nullptr)
    {
        pt->getRight()->setParent(pt);
        CompareCount::incrementCopia();
    }

    pt_right->setParent(pt->getParent());
    CompareCount::incrementCopia();

    CompareCount::incrementComparison();
    if (pt->getParent() == nullptr)
    {
        root = pt_right;
        CompareCount::incrementCopia();
    }

    else if (pt == pt->getParent()->getLeft())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        pt->getParent()->setLeft(pt_right);
    }
    else
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        pt->getParent()->setRight(pt_right);
    }

    pt_right->setLeft(pt);
    pt->setParent(pt_right);
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
}

template <class T>
void RBTree<T>::rotateRight(NodeRB<T> *&root, NodeRB<T> *&newNode)
{
    CompareCount::incrementCopia();
    NodeRB<T> *newNodeLeft = newNode->getLeft();

    CompareCount::incrementCopia();
    newNode->setLeft(newNodeLeft->getRight());

    CompareCount::incrementComparison();
    if (newNode->getLeft() != nullptr)
    {
        CompareCount::incrementCopia();
        newNode->getLeft()->setParent(newNode);
    }

    CompareCount::incrementCopia();
    newNodeLeft->setParent(newNode->getParent());

    CompareCount::incrementComparison();
    if (newNode->getParent() == nullptr)
    {
        CompareCount::incrementCopia();
        root = newNodeLeft;
    }
    else if (newNode == newNode->getParent()->getLeft())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        newNode->getParent()->setLeft(newNodeLeft);
    }
    else
    {
        CompareCount::incrementComparison();
        CompareCount::incrementCopia();
        newNode->getParent()->setRight(newNodeLeft);
    }

    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    newNodeLeft->setRight(newNode);
    newNode->setParent(newNodeLeft);
}

template<class T>
void RBTree<T>::fixInsert(NodeRB<T> *&root, NodeRB<T> *&newNode)
{
    CompareCount::incrementCopia();
    CompareCount::incrementCopia();
    //pai e avo do novo no inserido, respectivamente
    NodeRB<T> *parent_newNode = nullptr;
    NodeRB<T> *grand_parent_newNode = nullptr;

    while ((newNode != root) && (newNode->isRed()) &&
           (newNode->getParent()->isRed()))
    {

        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        parent_newNode = newNode->getParent();
        grand_parent_newNode = newNode->getParent()->getParent();

        CompareCount::incrementComparison();
        //pai de newNode eh filho a esquerda do avo de newNode
        if (parent_newNode == grand_parent_newNode->getLeft())
        {

            CompareCount::incrementCopia();
            NodeRB<T> *uncle_newNode = grand_parent_newNode->getRight();

            CompareCount::incrementComparison();
            //tio vermelho, apenas recoloracao
            if (uncle_newNode != nullptr && uncle_newNode->isRed()) {
                grand_parent_newNode->setRed(true);
                parent_newNode->setRed(false);
                uncle_newNode->setRed(false);
                CompareCount::incrementCopia();
                newNode = grand_parent_newNode;
            }
            else
            {
                CompareCount::incrementComparison();
                if (newNode == parent_newNode->getRight())
                {
                    rotateLeft(root, parent_newNode);
                    CompareCount::incrementCopia();
                    CompareCount::incrementCopia();
                    newNode = parent_newNode;
                    parent_newNode = newNode->getParent();
                }

                rotateRight(root, grand_parent_newNode);
                swapColors(parent_newNode, grand_parent_newNode);
                CompareCount::incrementCopia();
                newNode = parent_newNode;
            }
        }
        //pai de newNode eh filho a direita do avo de newNode
        else
        {
            CompareCount::incrementCopia();
            NodeRB<T> *uncle_newNode = grand_parent_newNode->getLeft();

            CompareCount::incrementComparison();
            //tio vermelho, apenas recoloracao
            if ((uncle_newNode != nullptr) && (uncle_newNode->isRed()))
            {
                grand_parent_newNode->setRed(true);
                parent_newNode->setRed(false);
                uncle_newNode->setRed(false);
                newNode = grand_parent_newNode;
                CompareCount::incrementCopia();
            }
            else
            {
                CompareCount::incrementComparison();
                if (newNode == parent_newNode->getLeft())
                {
                    rotateRight(root, parent_newNode);
                    newNode = parent_newNode;
                    parent_newNode = newNode->getParent();
                    CompareCount::incrementCopia();
                    CompareCount::incrementCopia();
                }

                rotateLeft(root, grand_parent_newNode);
                swapColors(parent_newNode, grand_parent_newNode);
                newNode = parent_newNode;
                CompareCount::incrementCopia();
            }
        }
    }
    root->setRed(false);
}

template <class T>
void RBTree<T>::swapColors(NodeRB<T> *node1, NodeRB<T> *node2)
{
    bool auxColor = node1->isRed();
    node1->setRed(node2->isRed());
    node2->setRed(auxColor);
}

template<class T>
NodeRB<T>* RBTree<T>::search(T value)
{
    return auxSearch(root, value);
}

template<class T>
NodeRB<T>* RBTree<T>::auxSearch(NodeRB<T>* root, T value)
{
    CompareCount::incrementComparison();
    if (root == nullptr || root->getValue() == value)
        return root;

    CompareCount::incrementComparison();
    // value menor que valor de root
    if (root->getValue() < value)
    {
        CompareCount::incrementCopia();
        return auxSearch(root->getRight(), value);
    }

    //value maior que valor de root
    CompareCount::incrementCopia();
    return auxSearch(root->getLeft(), value);
}



template<class T>
NodeRB<T>* RBTree<T>::removeLeaf(NodeRB<T> *p)
{
    delete p;
    return nullptr;
}

template<class T>
NodeRB<T>* RBTree<T>::remove1Son(NodeRB<T> *p)
{
    CompareCount::incrementComparison();
    NodeRB<T> *aux;
    CompareCount::incrementCopia();
    if(p->getLeft() == nullptr)
        aux = p->getRight();
    else
        aux = p->getLeft();
    delete p;
    return aux;
}

template <class T>
NodeRB<T>* RBTree<T>::menorSubArvDireita(NodeRB<T>* node)
{
    NodeRB<T> *aux = node->getRight();
    CompareCount::incrementCopia();
    CompareCount::incrementComparison();
    while(aux->getLeft() != nullptr)
    {
        CompareCount::incrementCopia();
        aux = aux->getLeft();
    }
    return aux;
}

template <class T>
NodeRB<T>* RBTree<T>::maiorSubArvEsq(NodeRB<T> *node)
{
    NodeRB<T> *aux = node->getLeft();
    CompareCount::incrementCopia();
    CompareCount::incrementComparison();
    while(aux->getRight() != nullptr)
    {
        CompareCount::incrementCopia();
        aux = aux->getRight();
    }
    return aux;
}

template <class T>
void RBTree<T>::remove (T value)
{
    auxRemove(root, value);
}

template<class T>
NodeRB<T>* RBTree<T>::auxRemove(NodeRB<T>* node, T value)
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
    else if(node != nullptr)
    {
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        if(node->getLeft() == nullptr && node->getRight() == nullptr) {
            CompareCount::incrementCopia();
            NodeRB<T>* parent = node->getParent();
            bool nodeColor = node->isRed();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            node = removeLeaf(node);
            node->setParent(parent);

            CompareCount::incrementComparison();
            if (!nodeColor && !node->isRed())
                fixRemove(node, parent);
                //caso em que o filho ou o no deletado eh vermelho, nao eh necessario chamar fixRemove
            else node->setRed(false);
        }
        else if((node->getLeft() == nullptr) || (node->getRight() == nullptr)) {
            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            NodeRB<T>* parent = node->getParent();
            bool nodeColor = node->isRed();
            node = remove1Son(node);
            node->setParent(parent);

            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            if (!nodeColor && !node->isRed())
                fixRemove(node, parent);
            //caso em que o filho ou o no deletado eh vermelho, nao eh necessario chamar fixRemove
            else node->setRed(false);
        }
        else
        {
            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            CompareCount::incrementComparison();
            //NodeRB<T> *aux = menorSubArvDireita(node);
            NodeRB<T> *aux = maiorSubArvEsq(node);
            CompareCount::incrementCopia();
            node->setValue(aux->getValue());
            aux->setValue(value);
            node->setRight(auxRemove(node->getRight(), value));
            CompareCount::incrementCopia();
        }
    }
    return node;
}

template <class T>
void RBTree<T>::removeCase1(NodeRB<T> *&node, NodeRB<T> *& parent)
{
    CompareCount::incrementComparison();
    /*  Case : A
           caso em que irmao de node eh filho a esquerda de parent*/
    if (node == parent->getRight())
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        NodeRB<T>* brother = parent->getLeft();
        NodeRB<T>* sobrinho = (brother->getLeft()->isRed() ? brother->getLeft() :brother->getRight());
        sobrinho->setRed(false);

        CompareCount::incrementComparison();
        if (sobrinho == brother->getRight())
        {
            cout << "a";
            rotateLeft(root, brother);
            CompareCount::incrementCopia();
            CompareCount::incrementCopia();
            sobrinho = brother;
            brother = sobrinho->getParent();
        }

        rotateRight(root, parent);
    }
        /* Case : B
           aso em que irmao de node eh filho a direita de parent*/
    else
    {
        CompareCount::incrementCopia();
        CompareCount::incrementCopia();
        NodeRB<T>* brother = parent->getRight();
        NodeRB<T>* sobrinho = (brother->getRight()->isRed() ? brother->getRight() :brother->getLeft());
        sobrinho->setRed(false);

        {

            CompareCount::incrementComparison();
            if (sobrinho == brother->getLeft())
            {
                cout << "b";
                rotateRight(root, brother);
                CompareCount::incrementCopia();
                CompareCount::incrementCopia();
                sobrinho = brother;
                brother = sobrinho->getParent();
            }

            rotateLeft(root, parent);
        }
    }
}


template <class T>
void RBTree<T>::fixRemove(NodeRB<T> *&node, NodeRB<T>* parent)
{
    CompareCount::incrementCopia();
    NodeRB<T> *brother = (node == parent->getRight() ? parent->getLeft() : parent->getRight());

    CompareCount::incrementComparison();
    if (node != root)
    {
        CompareCount::incrementComparison();
        if (!brother->isRed())
        {
            CompareCount::incrementComparison();
            if (brother->getRight()->isRed() || brother->getLeft()->isRed())
            {
                removeCase1(node, parent);
            }
            //caso 2, recursivo
            else
            {
                brother->setRed(!brother->isRed());

                CompareCount::incrementComparison();
                if (parent->isRed())
                    parent->setRed(false);
                else
                    fixRemove(parent, parent->getParent());
            }
        }
        //caso 3
        else
        {
            brother->setRed(!brother->isRed());
            parent->setRed(!parent->isRed());

            CompareCount::incrementComparison();
            if (brother == parent->getLeft())
            {
                rotateRight(root, parent);
            }
            else
            {
                rotateLeft(root, parent);
            }
            fixRemove(parent,parent->getParent());
        }
    }
    root->setRed(false);
}

template  <class T>
void RBTree<T>::print()
{
    printByLevel(root, 0);
    cout << endl;
}

template <class T>
void RBTree<T>::printByLevel(NodeRB<T> *p, int level)
{
    if (p != nullptr)
    {
        cout << "(" << level << ")";
        for(int i = 1; i <= level; i++)
            cout << "--";
        cout << " ";
        if (p->isRed())
            cout << p->getValue() << "R\n";
        else
            cout << p->getValue() << "B\n";
        printByLevel(p->getLeft(), level+1);
        printByLevel(p->getRight(), level+1);
    }
}

