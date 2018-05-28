//
// Created by viniman on 5/19/18.
//

/// AVL � uma �rvore bin�ria balanceada
/// fb = fator de balanceamento
/// hd - he = {0, 1, -1}
/// Rotacoes simples e duplas

/** REMOCAO
 *  3 Tipos de rota��o:
 *  - n� folha (sem filhos)
 *  - n� com 1 filho
 *  - n� com 2 filhos
 *  - N�o se pode remover de uma �rvore vazia
 *  - Removendo o �ltimo n�, a �rvore fica vazia
 *
 *  Balanceamento:
 *  - Remover um n� de um lado equivale a "inserir" um n� na outra subarvore
 *
 */


#include <iostream>
#include "../Headers/AvlTree.h"
#include "../Headers/AvlNode.h"

using namespace std;

template<class T>
AvlTree<T>::AvlTree()
{
	modifiedAvl = false;
	fatorBalanc = 1;
}

template<class T>
AvlTree<T>::AvlTree(bool modified)
{
	if (modified)
	{
		this->modifiedAvl = true;
		fatorBalanc = 3;
	}
	else
	{
		this->modifiedAvl = false;
		fatorBalanc = 1;
	}
}

template<class T>
void AvlTree<T>::insert(T val)
{
	BinaryTree<T>::root = auxInsere(getRoot(), val);
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
	BinaryTree<T>::root = auxRemove(getRoot(), val);
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
bool AvlTree<T>::search(T val)
{
	return auxSearch(BinaryTree<T>::root, val);
}

template<class T>
bool AvlTree<T>::auxSearch(AvlNode<T>* p, T val)
{
	if (p == nullptr)
		return false;
	else if (p->getValue() == val)
		return true;
	else if (val < p->getValue())
		return auxSearch(p->getLeft(), val);
	else
		return auxSearch(p->getRight(), val);
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

	if (fb < (-1)*fatorBalanc || fb > fatorBalanc)
	{
		if (fb == (1+fatorBalanc))
		{
			int fbEsq = calcFB(no->getLeft());
			if (fbEsq == fatorBalanc)
				no = rightRotate(no);
			else if (fbEsq == (-1)*fatorBalanc)
				no = leftRightRotate(no);
		}
		else if (fb == (-1)*(1+fatorBalanc))
		{
			int fbDir = calcFB(no->getRight());
			if (fbDir == (-1)*fatorBalanc)
				no = leftRotate(no);
			else if (fbDir == fatorBalanc)
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

