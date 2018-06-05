//
// Created by edson on 13/04/18.
//

#ifndef TRABALHO_ED2_HASHING_H
#define TRABALHO_ED2_HASHING_H

#include <iostream>
#include <vector>
#include "Hash.h"
#include "Vertex.h"

using namespace std;

class HashSeparated : public Hash{
public:
    //construtor e destrutor
    HashSeparated(unsigned int size, bool frequenceCounter):Hash(size, false)
    {
        collisionTable = new Vertex[size];
        if (frequenceCounter)
        {
            frequenceTable = new int[size];
            for (int i = 0; i < size; ++i)
                frequenceTable[i] = 0;
        }
        else frequenceTable = nullptr;
    };
    ~HashSeparated();

    //metodos
    void insert (unsigned int value)override ;
    void find (unsigned int value)override ;
    void printElements();
    void insertElementsVector(vector<Vertex>& vertexVec);

    //classe auxiliar para a lista de colisoes
private:
    Vertex* collisionTable;
    int* frequenceTable;
};

#endif //TRABALHO_ED2_HASHING_H
