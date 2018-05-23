
#include "../Headers/AvlTree.h"

template <class T>
void AvlTree<T>::insert(T val)
{
    BinaryTree<T>::insert(new NodeAvl<T>(val));
}

template <class T>
int AvlTree<T>::calcFB(NodeAvl<T> *no)
{
    if(no == nullptr)
        return 0;
    return no->getRight()->getHeight() - no->getRight()->getAltura();
}

template <class T>
NodeAvl<T> * AvlTree<T>::balance(NodeAvl<T>* no)
{
    /// Calcular o fator de balanceamento(alt_esq - alt_dir)
    int fb = calcFB(no);

    if(fb < -1 || fb > 1)
    {
        if (fb == 2) {
            int fbEsq = calcFB(no->getLeft());
            if (fbEsq == 1)
                no = rightRotate(no);
            else if (fbEsq == -1)
                no = leftRightRotate(no);
        } else if (fb == -2) {
            int fbDir = calcFB(no->getRight());
            if (fbDir == -1)
                no = leftRotate(no);
            else if (fbDir == 1)
                no = rightLeftRotate(no);
        }
    }
    return no;
}

