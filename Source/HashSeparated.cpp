//
// Created by edson on 13/04/18.
//

#include "../Headers/HashSeparated.h"


HashSeparated::~HashSeparated()
{
    delete []collisionTable;
}

void HashSeparated::insert(unsigned int value)
{
    unsigned int key = keyFunction(value);
    if (hashTable[key] == 0 || hashTable[key] == value)
        hashTable[key] = value;
    if(frequenceTable != nullptr)
        ++frequenceTable[key];
    else
    {
        
        Vertex* vertex = &collisionTable[key];
        if (vertex->value == 0 || vertex->value == value)
            vertex->value = value;
        if(frequenceTable != nullptr)
            ++frequenceTable[key];
        else {
            while (vertex->next != nullptr && vertex->value != value)
                vertex = vertex->next;
            if (vertex->next == nullptr) {
                vertex->next = new Vertex(value, nullptr, 0);
            }
            if(frequenceTable != nullptr)
                ++vertex->next->frequence;
        }
    }
}

void HashSeparated::find(unsigned int value)
{
    
    
    unsigned int key = keyFunction(value);
    if (hashTable[key] == value)
        return;
    else
    {
        
        Vertex* vertex = &this->collisionTable[key];
        while (vertex->value != value)
        {
            vertex = vertex->next;
            
        }
    }
}

void HashSeparated::printElements()
{
    Vertex* vertex;
    for (int i = 0; i < 30; ++i)
    {
        cout << i+1 << ": ";
        if (hashTable[i] != 0) {
            cout << hashTable[i];
            cout << endl;
        }
        vertex = &collisionTable[i];
        if (vertex->value != 0) {
            cout << "colisoes: ";
            while (vertex != nullptr) {
                cout << vertex->valueStr << " ";
                vertex = vertex->next;
            }
            cout << endl;
        }
    }
}

void HashSeparated::insertElementsVector(vector<Vertex>& vertexVec)
{
    Vertex* vertex;
    for (int i = 0; i < size; ++i)
    {
        if (hashTable[i] != 0) {
            vertexVec.emplace_back(hashTable[i], nullptr, frequenceTable[i]);
        }
        vertex = &collisionTable[i];
        if (vertex != nullptr)
            if (!vertex->valueStr.empty()) {
                while (vertex != nullptr) {
                    vertexVec.emplace_back(vertex->valueStr, nullptr, vertex->frequence);
                    vertex = vertex->next;
                }
            }
    }
}