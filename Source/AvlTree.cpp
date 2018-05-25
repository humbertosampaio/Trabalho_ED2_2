//
// Created by viniman on 5/19/18.
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
#include "../Headers/AvlNode.h"

using namespace std;

//AvlTree::AvlTree()
//{
//    raiz = nullptr;
//}

//template<class T>
//AvlTree<T>::AvlTree()
//{
//	raiz = nullptr;
//}

//AvlTree::~AvlTree()
//{
//    clear();//raiz = clear(raiz);
//}

//template<class T>
//AvlTree<T>::~AvlTree()
//{
//	clear();//raiz = clear(raiz);
//}

//void AvlTree::clear()
//{
//    raiz = clear(raiz);
//}

template<class T>
AvlNode<T>* AvlTree<T>::clear(AvlNode<T>* raiz)
{
	if (raiz != nullptr)
	{
		raiz->setLeft(clear(raiz->getLeft()));
		raiz->setRight(clear(raiz->getRight()));
		delete raiz;
		raiz = nullptr;
	}
	return raiz;
}

template<class T>
void AvlTree<T>::clear()
{
	root = clear(root);
}

////void AvlTree::clear(AvlNode<T>*raiz)
//AvlNode<T>* AvlTree::clear(AvlNode<T>*raiz)
//{
//	if(raiz != nullptr)
//	{
//		raiz->setEsq(clear(raiz->getEsq()));
//		raiz->setDir(clear(raiz->getDir()));
//		delete raiz;
//		raiz = nullptr;
//	}
//	return raiz;
//	/*if(raiz != nullptr)
//	{
//	libera(raiz->getEsq());
//	clear(raiz->getDir());
//	delete raiz;
//	}*/
//}

template<class T>
void AvlTree<T>::printByOrder(int caseOrder)
{
	switch (caseOrder)
	{
		case PRE_ORDER:
			preOrder(root);
			break;
		case IN_ORDER:
			inOrder(root);
		case POST_ORDER:
			postOrder(root);
		default:
			cout << "Nao existe esse codigo de operacao" << endl;
	}
	cout << endl;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
template<class T>
void AvlTree<T>::preOrder(AvlNode<T>* p)
{
	if (p != nullptr)
	{
		cout << p->getValue() << "(" << p->getHeight() << ") ";
		preOrder(p->getLeft());
		preOrder(p->getRight());
	}
}


// A utility function to print inorder traversal
// of the tree.
// The function also prints height of every node
template<class T>
void AvlTree<T>::inOrder(AvlNode<T>* p)
{
	if (p != nullptr)
	{
		inOrder(p->getLeft());
		cout << p->getValue() << "(" << p->getHeight() << ") ";
		inOrder(p->getRight());
	}
}


// A utility function to print postorder traversal
// of the tree.
// The function also prints height of every node
template<class T>
void AvlTree<T>::postOrder(AvlNode<T>* p)
{
	if (p != nullptr)
	{
		postOrder(p->getLeft());
		postOrder(p->getRight());
		cout << p->getValue() << "(" << p->getHeight() << ") ";
	}
}

template<class T>
void AvlTree<T>::insert(T val)
{
	root = auxInsere(getRoot(), val);
}

template<class T>
AvlNode<T>* AvlTree<T>::auxInsere(AvlNode<T>* no, T val)
{
	if (no == nullptr)
		return new AvlNode<T>(val);
	else
	{
		if (val < no->getValue())
			no->setLeft(auxInsere(no->getLeft(), val));
		else if (val > no->getValue())
			no->setRight(auxInsere(no->getRight(), val));
		else
		{
			cout << val << " ja esta na arv\n";
			return no; /// Consideramos que a AvlTree nao admite nos com valores iguais
		}
	}

	/// Calcular as alturas da esq e dir
	no->setHeight(calcAltura(no));

	return balance(no);
}

template<class T>
void AvlTree<T>::remove(T val)
{
	root = auxRemove(getRoot(), val);
}

template<class T>
AvlNode<T>* AvlTree<T>::auxRemove(AvlNode<T>* p, T val)
{
	if (p == nullptr)
	{
		cout << "Valor " << val << " nao existe!" << endl;
		return p;
	}

	if (val < p->getValue())
		p->setLeft(auxRemove(p->getLeft(), val));
	else if (val > p->getValue())
		p->setRight(auxRemove(p->getRight(), val));
	else
	{

		if (p->getLeft() == nullptr && p->getRight() == nullptr) //remove folha
		{
			delete p;
			return nullptr;
		}
		else if (p->getLeft() == nullptr || p->getRight() == nullptr) //remove 1 filho
		{
			AvlNode<T>*aux;
			if (p->getLeft() == nullptr)
				aux = p->getRight();
			else
				aux = p->getLeft();
			delete p;
			return aux;
		}
		else //remove 2 filhos
		{
			AvlNode<T>* aux = p->getRight(); // pega menorSubArvDireita
			while (aux->getLeft() != nullptr)
				aux = aux->getLeft(); //fim pega menorSubArvDireita

			T auxVal = aux->getValue();
			p->setValue(auxVal);
			aux->setValue(val);
			p->setRight(auxRemove(p->getRight(), val));
		}

	}
	p = balance(p);
	p->setHeight(calcAltura(p));
	return p;


}


template<class T>
bool AvlTree<T>::busca(T val)
{
	return auxBusca(root, val);
}

template<class T>
bool AvlTree<T>::auxBusca(AvlNode<T>* p, T val)
{
	if (p == nullptr)
		return false;
	else if (p->getValue() == val)
		return true;
	else if (val < p->getValue())
		return auxBusca(p->getLeft(), val);
	else
		return auxBusca(p->getRight(), val);
}


template<class T>
int AvlTree<T>::calcAltura(AvlNode<T>* p)
{
	int he, hd;
	if (p == nullptr)
		return 0;
	else
	{
		he = calcAltura(p->getLeft());
		hd = calcAltura(p->getRight());
		return 1 + max(he, hd);
	}
}

template<class T>
int AvlTree<T>::max(int &x, int &y)
{
	return x > y ? x : y;
}

template<class T>
int AvlTree<T>::calcFB(AvlNode<T>* no)
{
	if (no == nullptr)
		return 0;
	//  return calcAltura(no->getDir()) - calcAltura(no->getEsq());
	return no->getLeft()->getHeight() - no->getRight()->getHeight();
}

template<class T>
AvlNode<T>* AvlTree<T>::balance(AvlNode<T>* no)
{
	/// Calcular o fator de balanceamento(alt_esq - alt_dir)
	int fb = calcFB(no);

	if (fb < -1 || fb > 1)
	{
		if (fb == 2)
		{
			int fbEsq = calcFB(no->getLeft());
			if (fbEsq == 1)
				no = rightRotate(no);
			else if (fbEsq == -1)
				no = leftRightRotate(no);
		}
		else if (fb == -2)
		{
			int fbDir = calcFB(no->getRight());
			if (fbDir == -1)
				no = leftRotate(no);
			else if (fbDir == 1)
				no = rightLeftRotate(no);
		}
	}

	return no;
}



// Right Right Case (RotacaoRR)
template<class T>
AvlNode<T>* AvlTree<T>::leftRotate(AvlNode<T>*raiz)
{
	AvlNode<T>* no = raiz->getRight();
	raiz->setRight(no->getLeft());
	no->setLeft(raiz);
	raiz->setHeight(calcAltura(raiz));
	no->setHeight(calcAltura(no));

	return no;
}

// Left Left Case (RotacaoLL)
template<class T>
AvlNode<T>* AvlTree<T>::rightRotate(AvlNode<T>*y)
{
	AvlNode<T>* x = y->getLeft();
	y->setLeft(x->getRight());
	x->setRight(y);
	y->setHeight(calcAltura(y));
	x->setHeight(calcAltura(x));


	return x;
}

// Left Right Case (RotacaoLR)
template<class T>
AvlNode<T>* AvlTree<T>::leftRightRotate(AvlNode<T>*y)
{
	y->setLeft(leftRotate(y->getLeft()));
	return rightRotate(y);

}

// Right Left Case (RotacaoRL)
template<class T>
AvlNode<T>* AvlTree<T>::rightLeftRotate(AvlNode<T>*y)
{
	y->setRight(rightRotate(y->getRight()));
	return leftRotate(y);
}

