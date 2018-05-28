//
// Created by viniman on 11/04/18.
//

#include "../Headers/QuickSort.h"

/**
 *
 * @tparam T
 * @param vect
 * @param codigAlgorithm
 */
template<class T> void QuickSort::quickSort(vector<T> &vect)
{
        quickSort(vect, 0, vect.size());
}

/**
 *
 * @tparam T
 * @param vect
 * @param ini
 * @param fim
 */
template<class T> void QuickSort::quickSort(vector<T> &vect, int ini, int fim) {
    int i, j;
    i = ini;
    j = fim - 1;
    T pivo = vect[(ini + fim) / 2];
    ///Inicio Particionamento
    while (i <= j) {
        while (vect[i] < pivo && i < fim) {
            i++;
        }
        while (vect[j] > pivo && j > ini) {
            j--;
        }
        if (i <= j) {
            T aux = vect[i];
            vect[i] = vect[j];
            vect[j] = aux;
            i++;
            j--;
        }
    }
    ///Fim Particionamento

    ///Chamadas recursivas
    if (j > ini)
        quickSort(vect, ini, j + 1);
    if (i < fim)
        quickSort(vect, i, fim);
}

