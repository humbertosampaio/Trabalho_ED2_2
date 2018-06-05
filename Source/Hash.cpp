//
// Created by edson on 13/04/18.
//

#include "../Headers/Hash.h"

Hash::Hash(unsigned int size, bool extraSize)
{
	if (extraSize)
		size *= 1.25;
	this->size = size;
	this->hashTable = new int[size];
	for (int i = 0; i < size; ++i)
		hashTable[i] = 0;
}

Hash::~Hash()
{
	delete[]hashTable;
}

/*
 * funcao djb2 de hash para strings com nossa adaptacao para inteiros
 * referencia: http://www.cse.yorku.ca/~oz/hash.html
 * */
unsigned int Hash::keyFunction(unsigned int value)
{
	unsigned long int key = 5381;
	//cria um vetor de caracteres em relacao ao valor a ser inserido
	string str;
	str = to_string(value);
	char c;
	int i = 0;
	while (i < str.size()) {
		c = (char)str.at(i);
		key = ((key << 5) + key) + (int)abs(c); // key * 33 + c
		++i;
	}
	return key % size;
}

void Hash::printElements()
{
	for (int i = 0; i < size; ++i)
	{
		cout << i << ":";
		if (hashTable[i] != 0)
			cout << " " << hashTable[i];
		cout << endl;
	}
}