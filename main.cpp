#include <cstring>
#include <vector>
#include <set>

#include "Headers/CompareCount.h"
#include "Headers/FileUtils.h"
#include "Headers/Vertex.h"
#include "Headers/Hash.h"
#include "Headers/HashSeparated.h"

#include "Source/QuickSort.cpp"
#include "Source/BinaryTree.cpp"
#include "Source/SplayTree.cpp"
#include "Source/AvlTree.cpp"
#include "Source/RBTree.cpp"
#include "Source/BTree.cpp"
#include "Source/TreapTree.cpp"

#define RANDOM_SEED std::chrono::system_clock::now().time_since_epoch().count()

#define BUSCA_MAIS_FREQ 2
#define BUSCA_MENOS_FREQ 3
#define BUSCA_ALEATORIOS 4

/// ->>>>> Criar classe de impressao, para imprimir arvores, etc e tirar os metodos das classes arvores

using namespace std;


/// Variaveis utilizadas em toda a main(), afim de concentrar em uma só estrutura
struct Variables
{
	/// Vectors com os dados importados dos arquivos
	vector<Question> questionVector;
	vector<Answer> answerVector;

	/// Vector de frequencia de usuarios
	vector<Vertex> usersFrequency;

	string path;
	string questionPath;
	string answerPath;

	/// Usados para a leitura do arquivo de Entrada
	vector<int> Ns;
	unsigned long N;

	/// Usados na escolha dos menus
	short entry;
	short entryBusca;

	/// Identificador das arvores
	string trees[7];

	void entryPath(string _path)
	{
		path = _path;
		if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/' && !path.empty())
			path.push_back('/');
		if (!path.empty())
		{
			cout << "Path informado: " << path << endl;
			cout << "---------------------------------------------------------------------------------\n\n";
		}
		else
		{
			cout << "Como nao foi informado a path, consideraremos o diretorio do executavel como path\n";
			cout << "---------------------------------------------------------------------------------\n\n";
		}
		questionPath = path + "pythonquestions/Questions.csv";
		answerPath = path + "pythonquestions/Answers.csv";

		/**
		 * Preenchendo identificador de arvores, para facilitar a impressão
		 * Sendo que o indice é o mesmo da escolha do código do menu
		 */
		trees[0] = "Codigo Nao usado";
		trees[1] = "Arvore AVL";
		trees[2] = "Arvore AVL Modificada";
		trees[3] = "Arvore Vermelho e Preta";
		trees[4] = "Arvore Splay";
        trees[5] = "Arvore B";
        trees[6] = "Arvore Treap (Nossa arvore)";
	}
};

void openMenu(Variables &vars);
void insercao(Variables &vars);
void remocao(Variables &vars, bool ordenado);
void busca(Variables &vars);
void geraAVL(Variables &vars);
void geraAVLModificada(Variables &vars);
void geraVermelhoPreta(Variables &vars);
void geraSplay(Variables &vars);
void geraB(Variables &vars);
void geraNossaArvoreBalanc(Variables &vars);
void remocaoAVL(Variables &vars, bool ordenado);
void remocaoAVLModificada(Variables &vars, bool ordenado);
void remocaoVermelhoPreta(Variables &vars, bool ordenado);
void remocaoSplay(Variables &vars, bool ordenado);
void remocaoB(Variables &vars, bool ordenado);
void remocaoNossaArvoreBalanc(Variables &vars, bool ordenado);
void geraUserIdsBusca(Variables &vars, set<int> &userIds, int N);
void buscaUsersFrequency (Variables &vars);
void buscaAVL(Variables &vars);
void buscaAVLModificada(Variables &vars);
void buscaVermelhoPreta(Variables &vars);
void buscaSplay(Variables &vars);
void buscaB(Variables &vars);
void buscaNossaArvoreBalanc(Variables &vars);
vector<Question> getVetQuestionsRand(vector<Question> &vetQuestions, const int &n);

void testViniman()
{

    set<int> teste;
    teste.insert(10);
    teste.insert(2);
    teste.insert(2);
    teste.insert(12);
    teste.emplace(50);
    teste.emplace(50);
    teste.emplace(3);

    cout << "INICIO" << endl;
    for(auto it : teste)
    {
        cout << " " << it;
    }
    cout << "FIM PRINT" << endl;


	AvlTree<int> avl(true);
	avl.insert(9);
	avl.insert(8);
	avl.insert(10);
	avl.insert(11);
	avl.insert(19);
	avl.insert(20);
	avl.insert(21);
	avl.insert(22);
	avl.insert(23);
	avl.insert(25);
	avl.insert(1);
	avl.insert(2);
	avl.print();
	avl.printByOrder(IN_ORDER);

	/*
	AvlTree avltree;
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	//seed = 1;
	mt19937 eng(seed);
	uniform_int_distribution<int> dist(0,100);

	for(int i = 0; i<20; i++)
	{
		int insert = dist(eng);
		cout << "inserir " << insert << endl;
		avltree.insert(insert);
	}
	avltree.printByLevel();
	cout << "preorder: ";
	avltree.printByOrder(PRE_ORDER);

	for(int i = 0; i<2; i++)
	{
	   int rm = dist(eng);
		cout << "Remove " << rm << endl;
		avltree.remove(rm);
	}
	avltree.remove(30);
	avltree.remove(72);
	avltree.remove(12);
	avltree.remove(0);
	avltree.remove(54);
	avltree.remove(18);
	avltree.remove(34);
	avltree.remove(100);


	if(avltree.busca(94))
		cout << "VALOR " << 94 << " ENCONTRADO!!!!!!!!!" << endl;
	else
		cout << "VALOR " << 94 << " NAO ENCONTRADO!!!!!!!!!" << endl;

	if(avltree.busca(30))
		cout << "VALOR " << 30 << " ENCONTRADO!!!!!!!!!" << endl;
	else
		cout << "VALOR " << 30 << " NAO ENCONTRADO!!!!!!!!!" << endl;

	cout << "preorder: ";
	avltree.printByOrder(PRE_ORDER);
	avltree.printByLevel()*/
}

int main(int argc, char** argv)
{
	if (argc == 2 && !strcmp(argv[1], "test"))
	{
		testViniman();
		return 0;
	}

	FileUtils::showTop();

	if (argc != 2 && argc != 1)
	{
		cout << "Erro na chamada do programa. Informe corretamente o path (caminho) padrao inicial." << endl;
		cout << "Ou deixe em branco, caso queira considerar o diretorio do executavel como path" << endl;
		cout << R"(Certifique-se de no path estar o arquivo "entrada.txt" e a pasta "pythonquestions".)" << endl;
		cout << R"(Eh necessario que os arquivos "Answers.csv", "Questions.csv" e "Tags.csv" estejam no diretorio "pythonquestions".)" << endl;
		cout << "Formato a inserir na linha de comando para execucao do algoritmo:" << endl;
		cout << "<./executavel> <pathDoDiretorioInicial>" << endl;
		FileUtils::endProgram();
		return 0;
	}

	Variables vars;
	/// Se o quandtidade de argumentos é 1, nao foi informado o caminho, entao passa uma string vazia
	/// Do contrário, passa o caminho passado por parametro
	vars.entryPath(argc == 1 ? "" : argv[1]);

	/**
	 * Limpa os arquivos de saida, para nao conter lixos de outra execução
	 * Caso queira salvar os resultados da saída, eh necessário copiar os arquivos
	 */
	FileUtils::clearFileContent("saidaInsercao.txt");
	FileUtils::clearFileContent("saidaBusca.txt");
	FileUtils::clearFileContent("saidaRemocao.txt");

	/**a
	 * Leitura dos arquivos de questões e de respostas.
	 * O arquivo de Tags nao eh usado nessa parte do trabalho
	 */
	if (vars.questionVector.empty())
		FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);
	if (vars.answerVector.empty())
		FileUtils::readFileAnswer(vars.answerPath, vars.answerVector);

	openMenu(vars);

	return 0;
}

/**
 * Menu de opções inicial
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void openMenu(Variables &vars)
{
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "||            TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS              ||" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "||                    INSIRA O CODIGO DA OPCAO ESCOLHIDA                       ||" << endl;
	cout << "||     Opcao 0: Sair e encerrar a execucao                                     ||" << endl;
	cout << "||     Opcao 1: Estatisticas de Insercao                                       ||" << endl;
	cout << "||     Opcao 2: Estatisticas de Busca - Usuários Mais Frequentes               ||" << endl;
	cout << "||     Opcao 3: Estatisticas de Busca - Usuários Menos Frequentes              ||" << endl;
	cout << "||     Opcao 4: Estatisticas de Busca - Usuários Aleatórios                    ||" << endl;
	cout << "||     Opcao 5: Estatisticas de Remocao - Questions Aleatórias                 ||" << endl;
	cout << "||     Opcao 6: Estatisticas de Remocao - Questions Ordenadas                  ||" << endl;
	cout << "||-----------------------------------------------------------------------------||" << endl;
	cout << "||     Opcao: ";
	cin >> vars.entry;
	cout << "||-----------------------------------------------------------------------------||" << endl;
	switch (vars.entry)
	{
		case 0:
			FileUtils::endProgram();
		case 1:
			insercao(vars);
			break;
		case 2:
			busca(vars);
			break;
		case 3:
			busca(vars);
			break;
		case 4:
			busca(vars);
			break;
		case 5:
			remocao(vars, false); /// passa false por parametro, para nao ordenar
			break;
		case 6:
			remocao(vars, true); /// passa true por parametro, para ordenar os valores a serem removidos
		default:
			cout << "Opcao invalida. Tente novamente:" << endl;
			openMenu(vars);
	}
	FileUtils::pauseScreen(true);
	char executarNovamente;
	cout << "Executar novamente? (S/N)" << endl;
	cin >> executarNovamente;
	while (executarNovamente != 'N' && executarNovamente != 'n' && executarNovamente != 'S' && executarNovamente != 's')
	{
		cout << "Entrada invalida! Tente novamente: ";
		cin >> executarNovamente;
	}
	executarNovamente == 'S' || executarNovamente == 's' ? openMenu(vars) : FileUtils::endProgram();
}





/**
 * Menu de opções de Insercao para escolha da arvore
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void insercao(Variables &vars)
{
	vars.Ns = FileUtils::readInputFile("entradaInsercao.txt");
	vars.N = vars.Ns.size();
	while(true)
	{
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "||            TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS              ||" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "||         INSERCAO DE QUESTIONS - INSIRA O CODIGO DA OPCAO ESCOLHIDA          ||" << endl;
		cout << "||  Opcao 0: Voltar ao menu inicial                                            ||" << endl;
		cout << "||  Opcao 1: Gerar uma arvore AVL                                              ||" << endl;
		cout << "||  Opcao 2: Gerar uma arvore AVL Modificada (FB pode estar entre -3 e 3)      ||" << endl;
		cout << "||  Opcao 3: Gerar uma arvore Vermelho e Preta                                 ||" << endl;
		cout << "||  Opcao 4: Gerar uma arvore Splay                                            ||" << endl;
		cout << "||  Opcao 5: Gerar uma arvore B                                                ||" << endl;
		cout << "||  Opcao 6: Gerar uma arvore Treap (NossaArvoreDeBalanceamento)               ||" << endl;
		cout << "||  -------------------------------------------------------------------------  ||" << endl;
		cout << "Opcao: ";
		cin >> vars.entry;
		cout << "---------------------------------------------------------------------------------" << endl;
		switch (vars.entry)
		{
			case -1:
			FileUtils::endProgram();
			case 0:
				openMenu(vars);
				break;
			case 1:
				geraAVL(vars);
				break;
			case 2:
				geraAVLModificada(vars);
				break;
			case 3:
				geraVermelhoPreta(vars);
				break;
			case 4:
				geraSplay(vars);
				break;
			case 5:
				geraB(vars);
				break;
			case 6:
				geraNossaArvoreBalanc(vars);
				break;
			default:
				cout << "Opcao invalida. Tente novamente:" << endl;
				insercao(vars);
		}
	}
}

/**
 * Menu de opções de Remocao para escolha da arvore
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 * @param ordenado: valor booleano, se for true ordena vetor de remocao
 */
void remocao(Variables &vars, bool ordenado)
{
	vars.Ns = FileUtils::readInputFile("entradaRemocao.txt");
	vars.N = vars.Ns.size();
	while(true)
	{
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "||            TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS              ||" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "||     REMOCAO DE QUESTIONS " << (ordenado?"ORDENADAS ":"ALEATORIAS") << " - INSIRA O CODIGO DA OPCAO ESCOLHIDA    ||" << endl;
		cout << "||  Opcao 0: Voltar ao menu inicial                                            ||" << endl;
		cout << "||  Opcao 1: Remover elementos em arvore AVL                                   ||" << endl;
		cout << "||  Opcao 2: Remover elementos em arvore AVL Modificada (FB entre -3 e 3)      ||" << endl;
		cout << "||  Opcao 3: Remover elementos em arvore Vermelho e Preta                      ||" << endl;
		cout << "||  Opcao 4: Remover elementos em arvore Splay                                 ||" << endl;
		cout << "||  Opcao 5: Remover elementos em arvore B                                     ||" << endl;
		cout << "||  Opcao 6: Remover elementos em arvore Treap (NossaArvoreDeBalanceamento)    ||" << endl;
		cout << "||  -------------------------------------------------------------------------  ||" << endl;
		cout << "Opcao: ";
		cin >> vars.entry;
		cout << "---------------------------------------------------------------------------------" << endl;
		switch (vars.entry)
		{
			case 0:
				openMenu(vars);
			case 1:
				remocaoAVL(vars, ordenado);
				break;
			case 2:
				remocaoAVLModificada(vars, ordenado);
				break;
			case 3:
				remocaoVermelhoPreta(vars, ordenado);
				break;
			case 4:
				remocaoSplay(vars, ordenado);
				break;
			case 5:
				remocaoB(vars, ordenado);
				break;
			case 6:
				remocaoNossaArvoreBalanc(vars, ordenado);
				break;
			default:
				cout << "Opcao invalida. Tente novamente:" << endl;
				remocao(vars, ordenado);
		}
	}
}


/**
 * Menu de opções de Busca para escolha da arvore
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void busca(Variables &vars)
{
	/// Salva qual busca foi escolhida
	vars.entryBusca = vars.entry;
	string tempBuscaStr;
	if(vars.entryBusca == BUSCA_MAIS_FREQ)
		tempBuscaStr = "MAIS FREQUENTES";
	if(vars.entryBusca == BUSCA_MENOS_FREQ)
		tempBuscaStr = "MENOS FREQUENTES";
	if(vars.entryBusca == BUSCA_ALEATORIOS)
		tempBuscaStr = "ALEATORIAS";

	/// Se for busca pelos usuarios mais ou menos frequentes, chama a funcao que gera esse vector de frequencia
	if(vars.entryBusca == BUSCA_MAIS_FREQ || vars.entryBusca == BUSCA_MENOS_FREQ)
	{
		vector<Vertex> sorteredUsers;
		if(vars.usersFrequency.empty())
            buscaUsersFrequency (vars); /// Funcao que gera o vector de frequencias ordenadas
	}

	vars.Ns = FileUtils::readInputFile("entradaBusca.txt");
	vars.N = vars.Ns.size();
	while(true)
	{
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "||            TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS              ||" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "    BUSCA DE QUESTIONS " << tempBuscaStr << " - INSIRA O CODIGO DA OPCAO ESCOLHIDA  " << endl;
		cout << "  Opcao 0: Voltar ao menu inicial" << endl;
		cout << "  Opcao 1: Buscar " << tempBuscaStr << " em arvore AVL" << endl;
		cout << "  Opcao 2: Buscar " << tempBuscaStr << " em arvore AVL Modificada (FB entre -3 e 3)" << endl;
		cout << "  Opcao 3: Buscar " << tempBuscaStr << " em arvore Vermelho e Preta" << endl;
		cout << "  Opcao 4: Buscar " << tempBuscaStr << " em arvore Splay" << endl;
		cout << "  Opcao 5: Buscar " << tempBuscaStr << " em arvore B" << endl;
		cout << "  Opcao 6: Buscar " << tempBuscaStr << " em arvore Treap (NossaArvoreDeBalanceamento)" << endl;
		cout << "               ------------------------------------------  " << endl;
		cout << "Opcao: ";
		cin >> vars.entry;
		cout << "---------------------------------------------------------------------------------" << endl;

        /// Impressao no arquivo de saida

		if(vars.entry != 0)
		{
			string str;
			if (vars.entryBusca == BUSCA_MAIS_FREQ) {
				str += "\n\n-----------------------------------------------------------------";
				str += "\nBusca de Usuarios mais frequentes na " + vars.trees[vars.entry];
				str += "\n-----------------------------------------------------------------";
			} else if (vars.entryBusca == BUSCA_MENOS_FREQ) {
				str += "\n\n-----------------------------------------------------------------";
				str += "\nBusca de Usuarios menos frequentes na " + vars.trees[vars.entry];
				str += "\n-----------------------------------------------------------------";
			} else if (vars.entryBusca == BUSCA_ALEATORIOS) {
				str += "\n\n-----------------------------------------------------------------";
				str += "\nBusca de Usuarios aleatorios frequentes na " + vars.trees[vars.entry];
				str += "\n-----------------------------------------------------------------";
			}
			FileUtils::writeToOutputFile("saidaBusca.txt", str);
		}


        switch (vars.entry)
		{
			case 0:
				openMenu(vars);
			case 1:
				buscaAVL(vars);
				break;
			case 2:
				buscaAVLModificada(vars);
				break;
			case 3:
				buscaVermelhoPreta(vars);
				break;
			case 4:
				buscaSplay(vars);
				break;
			case 5:
				buscaB(vars);
				break;
			case 6:
				buscaNossaArvoreBalanc(vars);
				break;
			default:
				cout << "Opcao invalida. Tente novamente:" << endl;
				busca(vars);
		}
	}

}

/**
 * Funcao que gera vector de frequencia de usuarios ativos em vars.usersFrequency
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void buscaUsersFrequency (Variables &vars)
{
	cout << "As frequencias de Users ainda nao foram geradas" << endl;
	cout << "Frequencias sendo geradas..." << endl;
	long N = vars.questionVector.size();
	QuickSort::quickSort(vars.questionVector);
	HashSeparated hashAnswer ((unsigned int)ceil(0.1*N), true);

	QuickSort::quickSort(vars.answerVector);
	QuickSort::quickSort(vars.questionVector);
	auto itAnswer = vars.answerVector.begin();
	auto itQuestion = vars.questionVector.begin();
	for (const auto &it : vars.questionVector)
	{
		if (it == -1) continue;
		for (; (*itAnswer) < it; ++itAnswer);
		for (; (*itQuestion) < it; ++itQuestion);
		if ((*itAnswer) == it && (*itAnswer) != -1)
			hashAnswer.insert((*itAnswer).getUserId());
		if ((*itQuestion) == it && (*itQuestion) != -1)
			hashAnswer.insert((*itQuestion).getUserId());
	}
	hashAnswer.insertElementsVector(vars.usersFrequency);
	QuickSort::quickSort(vars.usersFrequency);

	// Códgio para Testar se esta funcionando
	/*resetiosflags;
    cout << setw(12) << left << "frequencia" << "UserIDs\n";
    for (int i = 0; i < N && i < vars.usersFrequency.size() && i < 50; ++i) {
        cout << left << setw(12) << vars.usersFrequency.at(i).frequence << setw(12) << vars.usersFrequency.at(i).value << endl;
    }
    resetiosflags;*/

}

/**
 * Funcao que gera vetor de elementos para serem buscados nas arvores
 * Gera elementos de acordo com o tipo de busca selecionado
 * Tipos de busca: Por usuarios mais frequente, menos frequentes ou seleciona aleatoriamente
 * @param vars: Usado em toda a main()
 * @param userIds: UserIds selecionados
 * @param N: Numero de UserIds para selecionar
 */
void geraUserIdsBusca(Variables &vars, set<int> &userIds, int N)
{
	cout << "Selecionando os " << N << " Users Ids." << endl;
	if (vars.entryBusca == BUSCA_MAIS_FREQ)
	{
		for (int i = 0; i < vars.usersFrequency.size() && userIds.size() < N; ++i)
		{
			userIds.insert(vars.usersFrequency[i].value);
		}
	}
	else if (vars.entryBusca == BUSCA_MENOS_FREQ)
	{
		for (int i = 1; i<= vars.usersFrequency.size() && userIds.size() < N; ++i)
		{
			userIds.insert(vars.usersFrequency[vars.usersFrequency.size()-i].value);
		}
	}
	else if (vars.entryBusca == BUSCA_ALEATORIOS)
	{
		for (int i = 0; i < vars.questionVector.size() && userIds.size() < N; ++i)
		{
			userIds.insert(vars.questionVector[i].getUserId());
		}
	}
}

/**
 * Funcao de insercao na arvore AVL
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraAVL(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore AVL.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			AvlTree<Question> avlTreeQuestion;

			CompareCount::initializeCounters("Insercao na rvore AVL", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}


/**
 * Funcao de insercao na arvore AVL Modificada
 * Modificacao feita: Arvore esta balanceada quando -3=<FB<=3
 * Arvore esta desbalanceada se esta fora do intervalo acima
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraAVLModificada(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore AVL Modificada.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/**O parametro "true" passado para o construtor informa
			que seta a AVL com fator de balanceamento modificado*/
			AvlTree<Question> avlModifiedTreeQuestion(true);

			CompareCount::initializeCounters("Insercao na Árvore AVL Modificada (fb normal=3)", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlModifiedTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}

/**
 * Funcao de insercao na arvore Vermelho e Preta
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraVermelhoPreta(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore Vermelho e preta.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			RBTree<Question> rbTreeQuestion;

			CompareCount::initializeCounters("Insercao na Árvore Vermelho e Preta", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				rbTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}

/**
 * Funcao de insercao na arvore Splay
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraSplay(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore Splay.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			SplayTree<Question> splayTreeQuestion;

			CompareCount::initializeCounters("Insercao na Árvore Splay", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				splayTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}

/**
 * Funcao de insercao na arvore B
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraB(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore B.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			BTree<Question> bTreeQuestion;

			CompareCount::initializeCounters("Insercao na Árvore B", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				bTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}


/**
 * Funcao de insercao na nossa arvore de balanceamento (Treap Tree)
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void geraNossaArvoreBalanc(Variables &vars)
{
	string str = "\n----------------------------------------------------";
	str += "\nGeracao e insercao em Arvore Treap.";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			TreapTree<Question> treapTreeQuestion;

			CompareCount::initializeCounters("Insercao na Árvore Treap", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				treapTreeQuestion.insert(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaInsercao.txt", str);
}


/**
 * Funcao de remocao na arvore AVL
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoAVL(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao na Arvore AVL";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			AvlTree<Question> avlTreeQuestion;

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlTreeQuestion.insert(tempVectorQuestions[k]);
			}

			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if(ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}


/**
 * Funcao de remocao na arvore AVL Modificada
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoAVLModificada(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao na Arvore AVL Modificada";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			AvlTree<Question> avlModifiedTreeQuestion(true);

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlModifiedTreeQuestion.insert(tempVectorQuestions[k]);
			}


			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if(ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore AVL Modificada (fb normal=3)", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				avlModifiedTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}


/**
 * Funcao de remocao na arvore Vermelho e Preta
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoVermelhoPreta(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao na Arvore Vermelho e Preta";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			RBTree<Question> rbTreeQuestion;

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				rbTreeQuestion.insert(tempVectorQuestions[k]);
			}

			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if(ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore Vermelho e Preta", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				rbTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}


/**
 * Funcao de remocao na arvore Splay
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoSplay(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao na Arvore Splay";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			SplayTree<Question> splayTreeQuestion;

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				splayTreeQuestion.insert(tempVectorQuestions[k]);
			}

			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if(ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore Splay", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				splayTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}

/**
 * Funcao de remocao na arvore B
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoB(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore B";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			BTree<Question> bTreeQuestion;

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				bTreeQuestion.insert(tempVectorQuestions[k]);
			}

			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if(ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore B", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				bTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}

/**
 * Funcao de remocao na nossa arvore de balanceamento (Treap Tree)
 * @param vars: Usado por toda a main() facilitando e concentrando tudo que eh usado em uma variavel só
 * @param ordenado: true: ordenar vetor de elementos gerados para remocao, false: nao ordenar
 */
void remocaoNossaArvoreBalanc(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore Treap";
	str += "\n----------------------------------------------------";

	for (int i = 0; i < vars.N; i++)
	{
		str += "\nExperimento " + to_string(i + 1) + ": N = " + to_string(vars.Ns[i]) + "\n\n";
		cout << "\nExperimento " << to_string(i + 1) << ": N = " << to_string(vars.Ns[i]) << endl;
		for (int j = 1; j <= 5; j++)
		{
			str += "Iteracao " + to_string(j) + "\n";
			cout << "Iteracao " << to_string(j) << endl;

			///Inserindo Questoes na Arvore
			vector<Question> tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			TreapTree<Question> treapTreeQuestion;

			cout << "Inserindo Questions na arvore...\n";
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				treapTreeQuestion.insert(tempVectorQuestions[k]);
			}

			/// Gera vector de questions para fazer a remocao
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);

			/// Se for remocao ordenada, ordena o vector de Questoes que foi gerado
			if (ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			cout << "Removendo Questions da arvore...\n";
			CompareCount::initializeCounters("Remocao na Árvore Treap", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();
			for (int k = 0; k < vars.Ns[i]; k++)
			{
				treapTreeQuestion.remove(tempVectorQuestions[k]);
			}
			CompareCount::timeEnd();
			str += CompareCount::getDataString();
		}
	}
	FileUtils::writeToOutputFile("saidaRemocao.txt", str);
}


/**
 * Funcao de Busca na arvore AVL
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaAVL(Variables &vars)
{
    set<int> userIds;
	string str;

    for(int i = 0; i < vars.N; ++i)
    {
    	/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

		cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
		AvlTree<int> avlTree;
		for(auto it : userIds)
		{
			avlTree.insert(it);
		}

		cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
		str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

		CompareCount::initializeCounters("Busca em árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
		CompareCount::setTimeStart();
		for(auto it : userIds)
		{
			avlTree.search(it);
		}
		CompareCount::timeEnd();

		str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}


/**
 * Funcao de Busca na arvore AVL Modificada
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaAVLModificada(Variables &vars)
{
    set<int> userIds;
    string str;

    for(int i = 0; i < vars.N; ++i)
    {
		/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

        cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
        AvlTree<int> modifiedAvlTree(true);
        for(auto it : userIds)
        {
            modifiedAvlTree.insert(it);
        }

        cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
        str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

        CompareCount::initializeCounters("Busca em árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
        CompareCount::setTimeStart();
        for(auto it : userIds)
        {
            modifiedAvlTree.search(it);
        }
        CompareCount::timeEnd();

        str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}

/**
 * Funcao de Busca na arvore Vermelho e Preta
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaVermelhoPreta(Variables &vars)
{
    set<int> userIds;
    string str;

    for(int i = 0; i < vars.N; ++i)
    {
		/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

        cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
        RBTree<int> rbTree;
        for(auto it : userIds)
        {
            rbTree.insert(it);
        }

        cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
        str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

        CompareCount::initializeCounters("Busca em árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
        CompareCount::setTimeStart();
        for(auto it : userIds)
        {
            rbTree.search(it);
        }
        CompareCount::timeEnd();

        str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}

/**
 * Funcao de Busca na arvore Splay
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaSplay(Variables &vars)
{
    set<int> userIds;
    string str;

    for(int i = 0; i < vars.N; ++i)
    {
		/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

        cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
        SplayTree<int> splayTree;
        for(auto it : userIds)
        {
            splayTree.insert(it);
        }

        cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
        str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

        CompareCount::initializeCounters("Busca em árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
        CompareCount::setTimeStart();
        for(auto it : userIds)
        {
            splayTree.search(it);
        }
        CompareCount::timeEnd();

        str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}


/**
 * Funcao de Busca na arvore B
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaB(Variables &vars)
{
    set<int> userIds;
    string str;

    for(int i = 0; i < vars.N; ++i)
    {
		/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

        cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
        BTree<int> bTree;
        for(auto it : userIds)
        {
            bTree.insert(it);
        }

        cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
        str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

        CompareCount::initializeCounters("Busca em árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
        CompareCount::setTimeStart();
        for(auto it : userIds)
        {
            bTree.search(it);
        }
        CompareCount::timeEnd();

        str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}

/**
 * Funcao de Busca na nossa arvore de balancemento (Treap Tree)
 * @param vars: Usado por toda a main() facilitando e concentrando
 * tudo que eh usado em uma variavel só
 */
void buscaNossaArvoreBalanc(Variables &vars)
{
    set<int> userIds;
    string str;

    for(int i = 0; i < vars.N; ++i)
    {
		/// Chama funcao para gerar user ids para a busca
		geraUserIdsBusca(vars, userIds, vars.Ns[i]);

        cout << "Inserindo na arvore " << vars.Ns[i] << " elementos." << endl;
        TreapTree<int> treapTree;
        for(auto it : userIds)
        {
            treapTree.insert(it);
        }

        cout << "Buscando na arvore de " << vars.Ns[i] << " elementos." << endl;
        str += "\nBusca na Arvore de " + to_string(vars.Ns[i])+  " Users Ids Aleatórios:\n";

        CompareCount::initializeCounters("Busca em árvore Treap", static_cast<unsigned long>(vars.Ns[i]));
        CompareCount::setTimeStart();
        for(auto it : userIds)
        {
            treapTree.search(it);
        }
        CompareCount::timeEnd();

        str += CompareCount::getDataString();
        userIds.clear();
    }
    FileUtils::writeToOutputFile("saidaBusca.txt", str);
}

/**
 * Funcao que gera vetor de Questions Aleatorios e retorna
 * @param vetQuestions: Vetor com todas as questions importadas do arquivos Questions.csv
 * @param n: numero de questions a inserir no vector
 * @return: vector de n Questions
 */
vector<Question> getVetQuestionsRand(vector<Question> &vetQuestions, const int &n)
{
	/**
	 * ifdef utilizando #define para RANDOM_SEED feito no inicio do arquivo da main.cpp
	 * para escolher o metodo de geracao de seed que melhor se enquadr para Windows ou Linux
	 */
	long seed = RANDOM_SEED;
	std::mt19937 eng(seed); // seed the generator
	uniform_int_distribution<unsigned long> distAleatoria(0, vetQuestions.size() - 1);///distribuicao uniforme aleatoria

	vector<int> questionsIds; ///Usado para nao ter registro com id repetido
	questionsIds.reserve((vetQuestions.size()));
	for (auto &it : vetQuestions)
		questionsIds.push_back(it.getQuestionId());

	vector<Question> vetQuestionsAleatorio; /// Vector de questions gerados aleatoriamente
	vetQuestionsAleatorio.reserve(n);

	for (int i = 0; i < n; i++)
	{
		unsigned int indice;
		do
		{
			indice = distAleatoria(eng);
		} while (questionsIds[indice] == -1);
		vetQuestionsAleatorio.push_back(vetQuestions[indice]);
		questionsIds[indice] = -1;
	}
	//FileUtils::writeToOutputFile("Seed: " + to_string(seed));
	return vetQuestionsAleatorio;
}

/**
 * Imprime um vector de elementos
 * @tparam T Template, onde T é o tipo do elemento
 * @param vector Vector de elemntos do Tipo T (Template) para impressão
 */
template<class T> void printVector(const vector<T> &vector)
{
	for (const auto &it : vector)
		cout << it << " ";
	cout << endl << endl;
}