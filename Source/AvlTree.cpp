//
// Created by viniman on 5/19/18.
//

#include "../Headers/AvlTree.h"


//
// Created by viniman on 5/8/18.
//


/// AVL é uma árvore binária balanceada
/// fb = fator de balanceamento
/// hd - he = {0, 1, -1}
/// Rotacoes simples e duplas

/** REMOCAO
 *  3 Tipos de rotação:
 *  - nó folha (sem filhos)
 *  - nó com 1 filho
 *  - nó com 2 filhos
 *  - Não se pode remover de uma árvore vazia
 *  - Removendo o último nó, a árvore fica vazia
 *
 *  Balanceamento:
 *  - Remover um nó de um lado equivale a "inserir" um nó na outra subarvore
 *
 */


#include <iostream>
#include "../Headers/AvlTree.h"

using namespace std;

AvlTree::AvlTree()
{
    raiz = nullptr;
}

AvlTree::~AvlTree()
{
    clear();//raiz = clear(raiz);
}

void AvlTree::clear()
{
    raiz = clear(raiz);
}


void AvlTree::printByLevel()
{
    imprimePorNivel(raiz, 0);
}

void AvlTree::printByOrder(int caseOrder)
{
    switch (caseOrder)
    {
        case PRE_ORDER:
            preOrder(raiz);
            break;
        case IN_ORDER:
            inOrder(raiz);
        case POST_ORDER:
            postOrder(raiz);
        default:
            cout << "Nao existe esse codigo de operacao" << endl;
    }
    cout << endl;
}

void AvlTree::imprimePorNivel(NodeAvl* p, int nivel)
{
    if (p != nullptr)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getChave() << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void AvlTree::preOrder(NodeAvl* p)
{
    if(p != nullptr)
    {
        cout << p->getChave() << "(" << p->getAltura() << ") ";
        preOrder(p->getEsq());
        preOrder(p->getDir());
    }
}


// A utility function to print inorder traversal
// of the tree.
// The function also prints height of every node
void AvlTree::inOrder(NodeAvl* p)
{
    if(p != nullptr)
    {
        inOrder(p->getEsq());
        cout << p->getChave() << "(" << p->getAltura() << ") ";
        inOrder(p->getDir());
    }
}


// A utility function to print postorder traversal
// of the tree.
// The function also prints height of every node
void AvlTree::postOrder(NodeAvl* p)
{
    if(p != nullptr)
    {
        postOrder(p->getEsq());
        postOrder(p->getDir());
        cout << p->getChave() << "(" << p->getAltura() << ") ";
    }
}




//void AvlTree::clear(NodeAvl *raiz)
NodeAvl * AvlTree::clear(NodeAvl *raiz)
{
    if(raiz != nullptr)
    {
        raiz->setEsq(clear(raiz->getEsq()));
        raiz->setDir(clear(raiz->getDir()));
        delete raiz;
        raiz = nullptr;
    }
    return raiz;
    /*if(raiz != nullptr)
    {
        libera(raiz->getEsq());
        clear(raiz->getDir());
        delete raiz;
    }*/
}


void AvlTree::insert(int val)
{
    raiz = auxInsere(raiz, val);
}

NodeAvl * AvlTree::auxInsere(NodeAvl *no, int val)
{
    if(no == nullptr)
        return new NodeAvl(val);
    else
    {
        if (val < no->getChave())
            no->setEsq(auxInsere(no->getEsq(), val));
        else if (val > no->getChave())
            no->setDir(auxInsere(no->getDir(), val));
        else
        {
            cout << val << " ja esta na arv\n";
            return no; /// Consideramos que a AvlTree nao admite nos com valores iguais
        }
    }

    /// Calcular as alturas da esq e dir
    no->setAltura(calcAltura(no));

    return balance(no);
}

void AvlTree::remove(int val)
{
    raiz = auxRemove(raiz, val);
}

NodeAvl* AvlTree::auxRemove(NodeAvl *p, int val)
{
    if(p == nullptr)
    {
        cout << "Valor " << val << " nao existe!" << endl;
        return p;
    }

    if(val < p->getChave())
        p->setEsq(auxRemove(p->getEsq(), val));
    else if(val > p->getChave())
        p->setDir(auxRemove(p->getDir(), val));
    else
    {

        if(p->getEsq() == nullptr && p->getDir() == nullptr) //remove folha
        {
            delete p;
            return nullptr;
        }
        else if(p->getEsq() == nullptr || p->getDir() == nullptr) //remove 1 filho
        {
            NodeAvl *aux;
            if(p->getEsq() == nullptr)
                aux = p->getDir();
            else
                aux = p->getEsq();
            delete p;
            return aux;
        }
        else //remove 2 filhos
        {
            NodeAvl *aux = p->getDir(); // pega menorSubArvDireita
            while(aux->getEsq() != nullptr)
                aux = aux->getEsq(); //fim pega menorSubArvDireita

            int auxVal = aux->getChave();
            p->setChave(auxVal);
            aux->setChave(val);
            p->setDir(auxRemove(p->getDir(), val));
        }

    }
    p = balance(p);
    p->setAltura(calcAltura(p));
    return p;


}


bool AvlTree::busca(int val)
{
    return auxBusca(raiz, val);
}

bool AvlTree::auxBusca(NodeAvl *p, int val)
{
    if(p == nullptr)
        return false;
    else if(p->getChave() == val)
        return true;
    else if(val < p->getChave())
        return auxBusca(p->getEsq(), val);
    else
        return auxBusca(p->getDir(), val);
}


int AvlTree::calcAltura(NodeAvl *p)
{
    int he, hd;
    if(p == nullptr)
        return 0;
    else
    {
        he = calcAltura(p->getEsq());
        hd = calcAltura(p->getDir());
        return 1 + max(he, hd);
    }
}

int AvlTree::max(int &x, int &y)
{
    return x > y ? x : y;
}

int AvlTree::calcFB(NodeAvl *no)
{
    if(no == nullptr)
        return 0;
    //  return calcAltura(no->getDir()) - calcAltura(no->getEsq());
    return no->getEsq()->getAltura() - no->getDir()->getAltura();
}




NodeAvl * AvlTree::balance(NodeAvl* no)
{
    //if(no == nullptr)
    //return nullptr;


    /// Calcular o fator de balanceamento(alt_esq - alt_dir)
    int fb = calcFB(no);




    if(fb < -1 || fb > 1)
    {
        if (fb == 2) {
            int fbEsq = calcFB(no->getEsq());
            if (fbEsq == 1)
                no = rightRotate(no);
            else if (fbEsq == -1)
                no = leftRightRotate(no);
        } else if (fb == -2) {
            int fbDir = calcFB(no->getDir());
            if (fbDir == -1)
                no = leftRotate(no);
            else if (fbDir == 1)
                no = rightLeftRotate(no);
        }
    }

    /*
    if(fb == 2)
    {
        if(calcFB(no->getEsq()) == -1)
            no->setEsq(leftRotate(no->getEsq()));
        no = rightRotate(no);
    }
    else if(fb == -2)
    {
        if(calcFB(no->getDir()) == 1)
            no->setDir(rightRotate(no->getDir()));
        no = leftRotate(no);
    }

*/

    /*
    if(fb>=2)
    {
        if(val < no->getEsq()->getChave())//(fb == 2 && no->getDir()->getDir()->getEsq() == nullptr)//no->getDir()->getDir()->getChave() > no->getDir()->getEsq()->getChave())
            no = rightRotate(no);
        else
            no = leftRightRotate(no);
    }
    else
    {
        if(val > no->getDir()->getChave())//(fb == -2 && no->getEsq()->getEsq()->getDir() == nullptr)
            no = leftRotate(no);
        else
            no = rightLeftRotate(no);
    }
    */






    /* GEEKS FOR GEEKS
     // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
     */

    return no;
}



// Right Right Case (RotacaoRR)
NodeAvl* AvlTree::leftRotate(NodeAvl *raiz)
{
    NodeAvl* no = raiz->getDir();
    raiz->setDir(no->getEsq());
    no->setEsq(raiz);
    raiz->setAltura(calcAltura(raiz));
    no->setAltura(calcAltura(no));

    return no;

}

// Left Left Case (RotacaoLL)
NodeAvl* AvlTree::rightRotate(NodeAvl *y)
{
    NodeAvl* x = y->getEsq();
    y->setEsq(x->getDir());
    x->setDir(y);
    y->setAltura(calcAltura(y));
    x->setAltura(calcAltura(x));


    return x;
}

// Left Right Case (RotacaoLR)
NodeAvl* AvlTree::leftRightRotate(NodeAvl *y)
{
    y->setEsq(leftRotate(y->getEsq()));
    return rightRotate(y);

}

// Right Left Case (RotacaoRL)
NodeAvl* AvlTree::rightLeftRotate(NodeAvl *y)
{
    y->setDir(rightRotate(y->getDir()));
    return leftRotate(y);
}

