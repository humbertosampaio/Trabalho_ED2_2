//
// Created by viniman on 11/04/18.
//

#ifndef TRABALHO_ED2_QUICKSORT_H
#define TRABALHO_ED2_QUICKSORT_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <ctime>
#include <set>
#include <random>
#include <chrono>
#include <string>
#include "Question.h"

class QuickSort {
public:
    template<class T> static void quickSort(vector<T> &vect);

private:
    template<class T> static void quickSort(vector<T> &vet, int began, int fim);
};


#endif //TRABALHO_ED2_QUICKSORT_H
