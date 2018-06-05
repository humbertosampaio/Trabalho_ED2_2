//
// Created by viniman on 5/19/18.
//

/// AVL e uma arvore binaria balanceada
/// fb = fator de balanceamento
/// hd - he = {0, 1, -1}
/// Rotacoes simples e duplas

/** REMOCAO
 *  3 Tipos de rotacaoo:
 *  - no folha (sem filhos)
 *  - no com 1 filho
 *  - no com 2 filhos
 *  - Noo se pode remover de uma �rvore vazia
 *  - Removendo o ultimo no, a �rvore fica vazia
 *
 *  Balanceamento:
 *  - Remover um no de um lado equivale a "inserir" um no na outra subarvore
 *
 */


#include <iostream>
#include <CompareCount.h>
#include "../Headers/AvlTree.h"
#include "../Headers/AvlNode.h"

using namespace std;

/**
 * Construtor AVL padrão
 * @tparam T: Template
 */
template<class T>
AvlTree<T>::AvlTree()
{
	modifiedAvl = false;
	fatorBalancNormal = 1;
}

/**
 * Construtor AVL, com paramentro dizendo se é AVL modificada (true)
 * @tparam T: Template
 * @param modified: Informa se eh uma AVL Modificada
 */
template<class T>
AvlTree<T>::AvlTree(bool modified)
{
	if (modified)
	{
		this->modifiedAvl = true;
		fatorBalancNormal = 3;
	}
	else
	{
		this->modifiedAvl = false;
		fatorBalancNormal = 1;
	}
}

/**
 * Funcao para inserir um novo elemento na arvore
 * @param val: Elemento a inserir
 */
template<class T>
void AvlTree<T>::insert(T val)
{
	BinaryTree<T>::root = auxInsere(getRoot(), val);
	CompareCount::incrementCopia();
}

/**
 * Funcao auxiliar recursiva para insercao
 * @tparam T: Template
 * @param no: no atual da recursao
 * @param val: elemento a inserir
 * @return retorna um no, para reconstrucao da recursividade
 */
template<class T>
AvlNode<T>* AvlTree<T>::auxInsere(AvlNode<T>* no, T val)
{
    CompareCount::incrementComparison();
	if (no == nullptr)
    {
        CompareCount::incrementCopia();
        return new AvlNode<T>(val);
    }
	else
	{
        CompareCount::incrementComparison();
		if (val < no->getValue())
		{
			CompareCount::incrementCopia();
			no->setLeft(auxInsere(no->getLeft(), val));
		}
		else if (val > no->getValue())
        {
            CompareCount::incrementComparison();
			CompareCount::incrementCopia();
            no->setRight(auxInsere(no->getRight(), val));
        }
		else
		{
            CompareCount::incrementComparison();
			return no; /// Consideramos que a AvlTree nao admite nos com valores iguais
		}
	}

	/// Calcular as alturas da esq e dir
	no->setHeight(calcAltura(no));
	return balance(no);
}

/**
 *
 * @tparam T
 * @param val
 */
template<class T>
void AvlTree<T>::remove(T val)
{
	CompareCount::incrementCopia();
	BinaryTree<T>::root = auxRemove(getRoot(), val);
}

/**
 *
 * @tparam T
 * @param p
 * @param val
 * @return
 */
template<class T>
AvlNode<T>* AvlTree<T>::auxRemove(AvlNode<T>* p, T val)
{
    CompareCount::incrementComparison();
	if (p == nullptr)
	{
		return p;
	}

    CompareCount::incrementComparison();
	if (val < p->getValue())
	{
		CompareCount::incrementCopia();
		p->setLeft(auxRemove(p->getLeft(), val));
	}
	else if (val > p->getValue())
    {
        CompareCount::incrementComparison();
		CompareCount::incrementCopia();
        p->setRight(auxRemove(p->getRight(), val));
    }
	else
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
		CompareCount::incrementComparison();
		if (p->getLeft() == nullptr && p->getRight() == nullptr) //remove folha
		{
			delete p;
			return nullptr;
		}
		else if (p->getLeft() == nullptr || p->getRight() == nullptr) //remove 1 filho
		{
            CompareCount::incrementComparison();
			CompareCount::incrementComparison();
			AvlNode<T>*aux;
			if (p->getLeft() == nullptr)
			{
				CompareCount::incrementCopia();
				aux = p->getRight();
			}
			else
			{
				CompareCount::incrementCopia();
				aux = p->getLeft();
			}
			delete p;
			return aux;
		}
		else //remove 2 filhos
		{
            CompareCount::incrementComparison();
			CompareCount::incrementCopia();
			AvlNode<T>* aux = p->getRight(); // pega menorSubArvDireita
			while (aux->getLeft() != nullptr)
			{
				CompareCount::incrementCopia();
				aux = aux->getLeft(); //fim pega menorSubArvDireita
			}
			CompareCount::incrementComparison();

			CompareCount::incrementCopia();
			CompareCount::incrementCopia();
			CompareCount::incrementCopia();
			CompareCount::incrementCopia();
			T auxVal = aux->getValue();
			p->setValue(auxVal);
			aux->setValue(val);
			p->setRight(auxRemove(p->getRight(), val));
		}

	}
	CompareCount::incrementCopia();
	p = balance(p);
	p->setHeight(calcAltura(p));
	return p;


}


/**
 *
 * @tparam T
 * @param val
 * @return
 */
template<class T>
bool AvlTree<T>::search(T &val)
{
	return auxSearch(getRoot(), val);
}


/**
 *
 * @tparam T
 * @param p
 * @param val
 * @return
 */
template<class T>
bool AvlTree<T>::auxSearch(AvlNode<T>* p, T &val)
{
	if (p == nullptr)
    {
        CompareCount::incrementComparison();
        return false;
    }
	else if (p->getValue() == val)
	{
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        return true;
    }
	else if (val < p->getValue())
    {
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        return auxSearch(p->getLeft(), val);
    }
	else
    {
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        CompareCount::incrementComparison();
        return auxSearch(p->getRight(), val);
    }
}

/**
 *
 * @tparam T
 * @param p
 * @return
 */
template<class T>
int AvlTree<T>::calcAltura(AvlNode<T>* p)
{
	int he, hd;
    CompareCount::incrementComparison();
	if (p == nullptr)
		return 0;
	else
	{
		he = calcAltura(p->getLeft());
		hd = calcAltura(p->getRight());
		return 1 + max(he, hd);
	}
}

/**
 * Funcao que retorna valor maximo entre dois elementos
 * @param x e y: elementos para verificar o maior
 * @return o elemento maior
 */
template<class T>
int AvlTree<T>::max(int &x, int &y)
{
    CompareCount::incrementComparison();
	return x > y ? x : y;
}

/**
 * Funcao para calcular Fator de Balanceamento de determinado
 * no passado como paramentro
 * @return: valor calculado do Fator de Balanceamento
 */
template<class T>
int AvlTree<T>::calcFB(AvlNode<T>* no)
{
    CompareCount::incrementComparison();
	if (no == nullptr)
		return 0;
	return no->getLeft()->getHeight() - no->getRight()->getHeight();
}

/**
 * Funcao que verifica o balancemento de uma subarvore com raiz no
 * @return no balanceado
 */
template<class T>
AvlNode<T>* AvlTree<T>::balance(AvlNode<T>* no)
{
	/// Calcular o fator de balanceamento(alt_esq - alt_dir)
	int fb = calcFB(no);

    CompareCount::incrementComparison();
    CompareCount::incrementComparison();
	if (fb < (-1)*fatorBalancNormal || fb > fatorBalancNormal)
	{
        CompareCount::incrementComparison();
		if (fb == (1+fatorBalancNormal))
		{
			int fbEsq = calcFB(no->getLeft());
            CompareCount::incrementComparison();
			if (fbEsq == fatorBalancNormal)
            {
            	CompareCount::incrementCopia();
                no = rightRotate(no);
            }
			else if (fbEsq == (-1)*fatorBalancNormal)
            {
                CompareCount::incrementComparison();
				CompareCount::incrementCopia();
                no = leftRightRotate(no);
            }
		}
		else if (fb == (-1)*(1+fatorBalancNormal))
		{
            CompareCount::incrementComparison();
			int fbDir = calcFB(no->getRight());

            CompareCount::incrementComparison();
			if (fbDir == (-1)*fatorBalancNormal)
            {
                no = leftRotate(no);
				CompareCount::incrementCopia();
            }
			else if (fbDir == fatorBalancNormal)
            {
                CompareCount::incrementComparison();
				CompareCount::incrementCopia();
                no = rightLeftRotate(no);
            }
		}
	}

	return no;
}


/**
 * Right Right Case (RotacaoRR) - Rotacao a esquerda (left)
 * @param raiz: no para rotacionar
 * @return no rotacionado e balanceado
 */
template<class T>
AvlNode<T>* AvlTree<T>::leftRotate(AvlNode<T>*raiz)
{
	CompareCount::incrementCopia();
	CompareCount::incrementCopia();
	CompareCount::incrementCopia();

	AvlNode<T>* no = raiz->getRight();
	raiz->setRight(no->getLeft());
	no->setLeft(raiz);

	/**Calcula a altura dos dois nos que foram manipulados,
	   pois suas alturas podem ter sido mudadas
	*/
	raiz->setHeight(calcAltura(raiz));
	no->setHeight(calcAltura(no));

	return no;
}


/**
 * Left Left Case (RotacaoLL) - Rotacao a direita (right)
 * @param y: no para rotacionar
 * @return no rotacionado e balanceado
 */
template<class T>
AvlNode<T>* AvlTree<T>::rightRotate(AvlNode<T>*y)
{
	CompareCount::incrementCopia();
	CompareCount::incrementCopia();
	CompareCount::incrementCopia();

	AvlNode<T>* x = y->getLeft();
	y->setLeft(x->getRight());
	x->setRight(y);

	/**Calcula a altura dos dois nos que foram manipulados,
	   pois suas alturas podem ter sido mudadas
	*/
	y->setHeight(calcAltura(y));
	x->setHeight(calcAltura(x));


	return x;
}


/**
 * Left Right Case (RotacaoLR)
 * Rotacao a esquerda(left) do filho esquerdo e depois rotacao a direita de y
 * @param y: no para rotacionar
 * @return no rotacionado e balanceado
 */
template<class T>
AvlNode<T>* AvlTree<T>::leftRightRotate(AvlNode<T>*y)
{
	CompareCount::incrementCopia();
	y->setLeft(leftRotate(y->getLeft()));
	return rightRotate(y);

}


/**
 * Right Left Case (RotacaoRL)
 * Rotacao a direita do filho direito e depois rotacao a esquerdade y
 * @param y: no para rotacionar
 * @return no rotacionado e balanceado
 */
template<class T>
AvlNode<T>* AvlTree<T>::rightLeftRotate(AvlNode<T>*y)
{
	CompareCount::incrementCopia();
	y->setRight(rightRotate(y->getRight()));
	return leftRotate(y);
}

