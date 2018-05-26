//
// Created by viniman on 5/26/18.
//

#ifndef TRABALHO_ED2_2_NODEB_H
#define TRABALHO_ED2_2_NODEB_H

const int d = 2; /// Ordem da árvore
const int MAX = 2*d;/// Número máximo de chaves
const int MIN = d; /// Número mínimo de filhos



template <class T> class NodeB
{
public:
    NodeB<T>()
    {
        for(int i = 0; i <= MAX; ++i){

            chave[i] = 0;
            filho[i] = nullptr;

        }
        filho[MAX+1] = nullptr; /// O numero de filhos é 1 a mais que de chaves, pois temos também os maiores que a chave
        tamanho = 0;
    }
    ~NodeB<T>() = default;

    int getPos(int valor)
    {

        for(int i = 0; i < tamanho; i++){

            if(chave[i] == valor)
                return i; ///Retorna a posicao do 'valor' no vetor chave.
        }
        return -1; ///Retorna -1 se não achar
    }


    int tamanho=0;
    int chave[MAX+1]; /// Cada nó possui 2*d chaves + a chave de overflow
    NodeB<T>* filho[MAX + 2]; /// Cada nó possui 2d+1 filhos + 1 filho de buffer para o overflow
    //: (2*d) - Para facilitar, os nós permitem uma chave a mais (buffer na posição MAX).
};


#endif //TRABALHO_ED2_2_NODEB_H
