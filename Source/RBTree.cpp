//
// Created by edson on 24/05/18.
//

#include "../Headers/RBTree.h"


template<class T>
RBTree<T>::RBTree()
{
    root = nullptr;
}

template<class T>
void RBTree<T>::insert (T value)
{
    NodeRB<T>* newNode = new NodeRB<T>(value);
    root = auxInsert(root, newNode);
    fixInsert(root, newNode);
}

template<class T>
NodeRB<T>* RBTree<T>::auxInsert(NodeRB<T> *node, NodeRB<T>* newNode)
{
    if(node == nullptr)
        node = newNode;

    if(newNode->getValue() < node->getValue()) {
        node->setLeft(auxInsert(node->getLeft(), newNode));
        node->getLeft()->setParent(node);
    }

    else if (newNode->getValue() > node->getValue()) {
        node->setRight(auxInsert(node->getRight(), newNode));
        node->getRight()->setParent(node);
    }

    return node;
}

template <class T>
void RBTree<T>::rotateLeft(NodeRB<T> *&root, NodeRB<T> *&pt)
{
    NodeRB<T> *pt_right = pt->getRight();

    pt->setRight(pt_right->getLeft());

    if (pt->getRight() != nullptr)
        pt->getRight()->setParent(pt);

    pt_right->setParent(pt->getParent());

    if (pt->getParent() == nullptr)
        root = pt_right;

    else if (pt == pt->getParent()->getLeft())
        pt->getParent()->setLeft(pt_right);

    else
        pt->getParent()->setRight(pt_right);

    pt_right->setLeft(pt);
    pt->setParent(pt_right);
}

template <class T>
void RBTree<T>::rotateRight(NodeRB<T> *&root, NodeRB<T> *&newNode)
{
    NodeRB<T> *newNodeLeft = newNode->getLeft();

    newNode->setLeft(newNodeLeft->getRight());

    if (newNode->getLeft() != nullptr)
        newNode->getLeft()->setParent(newNode);

    newNodeLeft->setParent(newNode->getParent());

    if (newNode->getParent() == nullptr)
        root = newNodeLeft;

    else if (newNode == newNode->getParent()->getLeft())
        newNode->getParent()->setLeft(newNodeLeft);

    else
        newNode->getParent()->setRight(newNodeLeft);

    newNodeLeft->setRight(newNode);
    newNode->setParent(newNodeLeft);
}

template<class T>
void RBTree<T>::fixInsert(NodeRB<T> *&root, NodeRB<T> *&newNode)
{
    //pai e avo do novo no inserido, respectivamente
    NodeRB<T> *parent_newNode = nullptr;
    NodeRB<T> *grand_parent_newNode = nullptr;

    while ((newNode != root) && (newNode->isRed()) &&
           (newNode->getParent()->isRed()))
    {

        parent_newNode = newNode->getParent();
        grand_parent_newNode = newNode->getParent()->getParent();

        /*  Case : A
            Parent of newNode is left child of Grand-parent of newNode */
        if (parent_newNode == grand_parent_newNode->getLeft())
        {

            NodeRB<T> *uncle_newNode = grand_parent_newNode->getRight();

            /* Case : 1
               The uncle of newNode is also red
               Only Recoloring required */
            if (uncle_newNode != nullptr && uncle_newNode->isRed())
            {
                grand_parent_newNode->setRed(true);
                parent_newNode->setRed(false);
                uncle_newNode->setRed(false);
                newNode = grand_parent_newNode;
            }

            else
            {
                /* Case : 2
                   newNode is right child of its parent
                   Left-rotation required */
                if (newNode == parent_newNode->getRight())
                {
                    rotateLeft(root, parent_newNode);
                    newNode = parent_newNode;
                    parent_newNode = newNode->getParent();
                }

                /* Case : 3
                   newNode is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_newNode);
                swapColors(parent_newNode, grand_parent_newNode);
                newNode = parent_newNode;
            }
        }
            /* Case : B
               Parent of newNode is right child of Grand-parent of newNode */
        else
        {
            NodeRB<T> *uncle_newNode = grand_parent_newNode->getLeft();

            /*  Case : 1
                The uncle of newNode is also red
                Only Recoloring required */
            if ((uncle_newNode != nullptr) && (uncle_newNode->isRed()))
            {
                grand_parent_newNode->setRed(true);
                parent_newNode->setRed(false);
                uncle_newNode->setRed(false);
                newNode = grand_parent_newNode;
            }
            else
            {
                /* Case : 2
                   newNode is left child of its parent
                   Right-rotation required */
                if (newNode == parent_newNode->getLeft())
                {
                    rotateRight(root, parent_newNode);
                    newNode = parent_newNode;
                    parent_newNode = newNode->getParent();
                }

                /* Case : 3
                   newNode is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_newNode);
                swapColors(parent_newNode, grand_parent_newNode);
                newNode = parent_newNode;
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
    if (root == nullptr || root->getValue() == value)
        return root;

    // value menor que valor de root
    if (root->getValue() < value)
        return auxSearch(root->getRight(), value);

    //value maior que valor de root
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
    NodeRB<T> *aux;
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
    while(aux->getLeft() != nullptr)
        aux = aux->getLeft();
    return aux;
}

template <class T>
NodeRB<T>* RBTree<T>::maiorSubArvEsq(NodeRB<T> *node)
{
    NodeRB<T> *aux = node->getLeft();
    while(aux->getRight() != nullptr)
        aux = aux->getRight();
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
    if(node == nullptr)
        return nullptr;
    else if(value < node->getValue())
        node->setLeft(auxRemove(node->getLeft(), value));
    else if(value > node->getValue())
        node->setRight(auxRemove(node->getRight(), value));
    else if(node != nullptr)
    {
        if(node->getLeft() == nullptr && node->getRight() == nullptr) {
            NodeRB<T>* parent = node->getParent();
            bool nodeColor = node->isRed();
            node = removeLeaf(node);
            node->setParent(parent);

            if (!nodeColor && !node->isRed())
                fixRemove(node, parent);
                //caso 1 em que o filho ou o no deletado eh vermelho, nao eh necessario chamar fixRemove
            else node->setRed(false);
        }
        else if((node->getLeft() == nullptr) || (node->getRight() == nullptr)) {
            NodeRB<T>* parent = node->getParent();
            bool nodeColor = node->isRed();
            node = remove1Son(node);
            node->setParent(parent);

            if (!nodeColor && !node->isRed())
                fixRemove(node, parent);
            //caso 1 em que o filho ou o no deletado eh vermelho, nao eh necessario chamar fixRemove
            else node->setRed(false);
        }
        else
        {
            //NodeRB<T> *aux = menorSubArvDireita(node);
            NodeRB<T> *aux = maiorSubArvEsq(node);
            node->setValue(aux->getValue());
            aux->setValue(value);
            node->setRight(auxRemove(node->getRight(), value));
        }
    }
    return node;
}

template <class T>
void RBTree<T>::removeCase1(NodeRB<T> *&node, NodeRB<T> *& parent)
{
    /*  Case : A
           caso em que irmao de node eh filho a esquerda de parent*/
    if (node == parent->getRight())
    {
        NodeRB<T>* brother = parent->getLeft();
        NodeRB<T>* sobrinho = (brother->getLeft()->isRed() ? brother->getLeft() :brother->getRight());
        sobrinho->setRed(false);

        if (sobrinho == brother->getRight())
        {
            cout << "a";
            rotateLeft(root, brother);
            sobrinho = brother;
            brother = sobrinho->getParent();
        }

        rotateRight(root, parent);
    }
        /* Case : B
           Parent of newNode is right child of Grand-parent of newNode */
    else
    {
        NodeRB<T>* brother = parent->getRight();
        NodeRB<T>* sobrinho = (brother->getRight()->isRed() ? brother->getRight() :brother->getLeft());
        sobrinho->setRed(false);

        {

            if (sobrinho == brother->getLeft())
            {
                cout << "b";
                rotateRight(root, brother);
                sobrinho = brother;
                brother = sobrinho->getParent();
            }

            rotateLeft(root, parent);
        }
    }
}


template <class T>
void RBTree<T>::fixRemove(NodeRB<T> *&node, NodeRB<T>*& parent) {
    NodeRB<T>* brother = (node == parent->getRight() ? parent->getLeft() : parent->getRight());
    while (node != root)
    {
        if (!brother->isRed())
        {
            if (brother->getRight()->isRed() || brother->getLeft()->isRed())
            {
                removeCase1(node, parent);
                break;
            }
            else
            {

            }
        }
        else
        {

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

