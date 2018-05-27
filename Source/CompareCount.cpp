//
// Created by vinic on 4/16/2018.
//

#include "../Headers/CompareCount.h"

using namespace std;

std::string CompareCount::nameOfAlgorithm;
unsigned long CompareCount::sizeVector;
int CompareCount::countNumComparisons;
int CompareCount::countNumCopias;
clock_t CompareCount::timeStart;
double CompareCount::runtime;
bool CompareCount::runtimeCalc = true;

/**
 * Método resposável por inicializar os contadores para uma nova contagem
 * Responsável também por limpar os contadores não pegando lixo do ultimo algoritmo contabilizado
 * Seu código só executado se o tempo de execução (runtime) foi calculado (isso indica que já foi salvo os dados anteriores)
 * @param name: recebe uma string com o nome do algoritmo a salvar os dados
 */
void CompareCount::initializeCounters(std::string name, unsigned long size)
{
	if (runtimeCalc)
	{
	    nameOfAlgorithm = name;
	    sizeVector = size;
		countNumComparisons = 0;
		countNumCopias = 0;
		timeStart = 0;
		runtime = 0;
		runtimeCalc = false;
	}
}

/**
 * Incrementa +1 na variável de contagem de Comparações
 */
void CompareCount::incrementComparison()
{
	countNumComparisons++;
}

/**
 * Incrementa +1 na variável de contagem de Cópias
 */
void CompareCount::incrementCopia()
{
	countNumCopias++;
}

/**
 * Determina tempo inicial de execução do algoritmo
 */
void CompareCount::setTimeStart()
{
	timeStart = clock();
}

/**
 * Finaliza tempo de execução e calcula tempo decorrido, salvando em runtime
 */
void CompareCount::timeEnd()
{
	runtimeCalc = true;
	runtime = (double) (clock() - timeStart) / CLOCKS_PER_SEC;
}

/**
 * Imprime os dados de execução do algoritmo na tela do terminal
 */
void CompareCount::printData()
{
	std::cout << "Comparacoes: " << countNumComparisons << std::endl;
	std::cout << "Copias: " << countNumCopias << std::endl;
	std::cout << "Tempo de Execução: ";
	runtimeCalc ? std::cout << runtime << std::endl : std::cout << "Nao foi calculado" << std::endl;
}

/**
 *  retorna string com os dados de execução do algoritmo
 * @return
 */
string CompareCount::getDataString()
{
	string data = "Algoritmo: " + nameOfAlgorithm + "\n";
	data += "Quantidade de elementos a ordenar: " + to_string(sizeVector) + "\n";
	data += "Comparacoes: " + to_string(countNumComparisons) + "\nCopias: " +
			to_string(countNumCopias) + "\nTempo de Execução: ";
	data += runtimeCalc ? (to_string(runtime) + "\n") : "Nao foi calculado\n";

	return data;
}
