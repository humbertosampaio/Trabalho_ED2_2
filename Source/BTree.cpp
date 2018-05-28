//
// Created by viniman on 5/26/18.
//

#include "../Headers/BTree.h"

using namespace std;

template<class T>
BTree<T>::BTree() : raiz(nullptr) {}

template<class T>
BTree<T>::~BTree<T>()
{
    deletaArvore(raiz);
}

template<class T>
void BTree<T>::deletaArvore(NodeB<T> *no)
{
    if(no == nullptr)
        return;
    for(int i = 0; i <= no->tamanho; i++)
    {
        deletaArvore(no->filho[i]);
        delete no->filho[i];
    }
}

template<class T>
NodeB<T>** BTree<T>::getRaiz(){

    return &raiz;

}

template<class T>
void BTree<T>::insert(T valor)
{
    if(raiz == nullptr) ///Se a arvore esta vazia, cria a raiz
    {
        raiz = new NodeB<T>();
        insereNo(raiz, valor);
    }
    else
    {
        insereRecursivo(raiz, valor);
        if(raiz->tamanho == MAX+1) ///Verifica se a raiz tem overflow, para fazer o split
        {
            NodeB<T>* novoNo;
            NodeB<T>* auxRaiz = new NodeB<T>();
            T s = split(raiz, &novoNo);
            auxRaiz->filho[0] = raiz;
            auxRaiz->filho[1] = novoNo;
            auxRaiz->chave[0] = s;
            auxRaiz->tamanho++; ///Aumenta a quantidade de chaves na pagina
            raiz = auxRaiz;
        }
    }
}

template<class T>
NodeB<T> * BTree<T>::insereNo(NodeB<T> *no, T valor) ///Insere no 'no' o valor da variavel 'valor'
{
    int k = 0;
    while(k < no->tamanho && no->chave[k] < valor) ///Encontra a posicao do vetor de chaves que 'valor' sera inserido
    {
        k++;
    }
    for(int i = no->tamanho-1; i >= k; i--)///Desloca todos os valores a direita de k uma posicao, incluindo k, liberando espaco para valor ser inserido em k
    {
        no->chave[i+1] = no->chave[i];
    }
    for(int i = no->tamanho; i >= k; i--) ///Desloca todos os filhos a direita de k uma posicao, incluindo k, liberando espaco para outro filho ser inserido em k
    {
        no->filho[i+1] = no->filho[i];
    }
    no->chave[k] = valor;
    no->tamanho++;
}

template<class T>
void BTree<T>::insereRecursivo(NodeB<T>* no, T valor)
{
    int k = 0;
    while(k < no->tamanho){///Encontra a posicao do vetor de chaves que 'valor' sera inserido

        if(no->chave[k] < valor)
            k++;
        else if(no->chave[k] == valor)
            return; //nao insert elementos de chaves iguais
        else
            break;

    }
    if(no->filho[k]== nullptr){///Verifica se o no eh folha, se for, insere, caso contrario continua descendo na arvore

        insereNo(no,valor);

    }else{

        insereRecursivo(no->filho[k], valor);
        if(no->filho[k]->tamanho == MAX+1) ///Verifica se houve overflow na insersao
        {

            NodeB<T>* novoNo;///No que sera criado no split
            T s = split(no->filho[k],&novoNo);///Valor de retorno do split, ou seja, o valor que será adicionado no 'no'
            insereNo(no,s);
            no->filho[no->getPos(s)] = no->filho[no->getPos(s)+1];///Coloco o ponteiro para o filho 'n' usado no split na posicao correta
            no->filho[no->getPos(s)+1] = novoNo;///Adiciona o 'novoNo' criado como filho maior de 's'

        }

    }

}

template<class T>
bool BTree<T>::find(T valor)
{
    return find(raiz, valor) != nullptr;
    //return buscar(valor, raiz) != nullptr;
}

template<class T>
NodeB<T>* BTree<T>::find(NodeB<T>* n, T valor)
{
    NodeB<T>* aux;

    if(n == nullptr)
    {
        return nullptr;
    }
    else //if(n->chave[k] == valor) ///Verifica se o valor esta no No 'n', se estiver, retona a posicao de memoria de 'n', caso nao esteja, verifica nos seus filhos
    {
        if(n->getPos(valor) != -1)
            return n;
    }

    for (int i = 0; i <= n->tamanho; i++)
    {//Verifica se encontra o valor nos filhos de 'n'
        aux = find(n->filho[i], valor);
        if (aux != nullptr) {
            return aux;
        }
    }

    return nullptr;

}

template<class T>
T BTree<T>::split(NodeB<T>* n, NodeB<T>** novoNo)///Reparte os valores de 'n' para o 'novoNo' e retorna o valor mediano;
{
    *novoNo = new NodeB<T>();

    int MID = MIN; /// Encontra o valor mediano no No 'n'
    int k = 0;
    T sobressalente;

    for(int i=MID+1; i <= MAX; i++)
    {
        (*novoNo)->chave[k] = n->chave[i];
        //n->chave[i] = 0;
        (*novoNo)->filho[k] = n->filho[i];
        n->filho[i] = nullptr;
        (*novoNo)->tamanho++;
        n->tamanho--;
        k++;
    }

    (*novoNo)->filho[k] = n->filho[MAX+1];
    n->filho[MAX+1] = nullptr;//n->filho[MAX+1] = nullptr;
    sobressalente = n->chave[MID]; ///Guardo o No que ira subir para o pai
    //n->chave[MID] = 0;
    n->tamanho--;

    return sobressalente; ///Retorna o No sobressalente da funcao split
}


template<class T>
void BTree<T>::imprime()
{
    imprimePorNivel(raiz, 0);
}



template<class T>
void BTree<T>::imprimePorNivel(NodeB<T>* p, int nivel)
{
    if (p != nullptr)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        for(int i = 0; i < p->tamanho; i++)
        {
            cout << p->chave[i] << " ";
        }
        cout << endl;
        for(int i = 0; i <= p->tamanho; i++)
        {
            imprimePorNivel(p->filho[i], nivel+1);
        }
    }
}

template<class T>
void BTree<T>::inOrder()
{
    inOrder(raiz);
    cout << endl;
}

template<class T>
void BTree<T>::inOrder(NodeB<T>* p)
{
    if(p != nullptr)
    {
        for(int i = 0; i <= p->tamanho; i++)
        {

            inOrder(p->filho[i]);
            if(i != p->tamanho)
                cout << p->chave[i] << " ";
        }

    }
}


