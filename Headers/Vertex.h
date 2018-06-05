//
// Created by edson on 18/04/18.
//

#ifndef TRABALHO_ED2_VERTEX_H
#define TRABALHO_ED2_VERTEX_H

#include <iostream>

using namespace std;

class Vertex
{
	public:
	Vertex() { valueStr = ""; next = nullptr; frequence = 0; };
	Vertex(string valueStr, Vertex* next, unsigned int frequence)
	{
		this->valueStr = valueStr;
		this->next = next;
		this->frequence = frequence;
	};
	Vertex(int value, Vertex* next, unsigned int frequence)
	{
		this->value = value;
		this->next = next;
		this->frequence = frequence;
	};
	;

	//operadores ao contrario para ordenar de forma decrescente
	bool operator>(const Vertex &rhs) const {
		return frequence < rhs.frequence;
	}

	bool operator<(const Vertex &rhs) const {
		return rhs.frequence < this->frequence;
	}

	bool operator>=(const Vertex &rhs) const {
		return !(rhs.frequence < this->frequence);
	}

	bool operator<=(const Vertex &rhs) const {
		return !(this->frequence < rhs.frequence);
	};

	bool operator==(const Vertex &rhs) const {
		return frequence == rhs.frequence;
	}

	bool operator!=(const Vertex &rhs) const {
		return !(rhs.frequence == this->frequence);
	}

	int value;
	string valueStr;
	Vertex* next;
	unsigned int frequence;
};



#endif //TRABALHO_ED2_VERTEX_H
