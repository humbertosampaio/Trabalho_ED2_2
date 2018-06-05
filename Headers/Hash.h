//
// Created by edson on 13/04/18.
//

#ifndef TRABALHO_ED2_HASH_H
#define TRABALHO_ED2_HASH_H

#include <cmath>
#include <string>
#include <iostream>

using namespace std;

class Hash {
	protected:
	unsigned int size;
	int* hashTable;
	bool extraSize;

	public:
	unsigned int keyFunction(unsigned int value);
	void printElements();
	virtual void insert(unsigned int value) {};
	virtual void find(unsigned int value) {};
	Hash(unsigned int size, bool extraSize);
	~Hash();
};


#endif //TRABALHO_ED2_HASH_H
