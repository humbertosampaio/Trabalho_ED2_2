#include <cstring>
#include <vector>

#include "Headers/CompareCount.h"
#include "Headers/FileUtils.h"

#include "Source/QuickSort.cpp"
#include "Source/BinaryTree.cpp"
#include "Source/SplayTree.cpp"
#include "Source/AvlTree.cpp"
#include "Source/RBTree.cpp"
#include "Source/BTree.cpp"
#include "Source/TreapTree.cpp"


#define RANDOM_SEED std::chrono::system_clock::now().time_since_epoch().count()

#define AVL_TREE 1
#define AVL_MOD_TREE 2
#define RB_TREE 3
#define SPLAY_TREE 4
#define B_TREE 5
#define NOSSA_TREE 6

#define BUSCA_MAIS_FREQ 2
#define BUSCA_MENOS_FREQ 3
#define BUSCA_ALEATORIOS 4

/// ->>>>> Criar classe de impressao, para imprimir arvores, etc e tirar os metodos das classes arvores

using namespace std;

struct Variables
{
	vector<Question> questionVector;
	vector<Answer> answerVector;
	vector<Tag> tagVector;
	vector<int> intVector;

	string path;
	string questionPath;
	string answerPath;
	string tagPath;

	vector<int> Ns;
	unsigned long N;
	short entry;

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
		tagPath = path + "pythonquestions/Tags.csv";
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
void buscaAVL(Variables &vars, short &busca);
void buscaAVLModificada(Variables &vars, short &busca);
void buscaVermelhoPreta(Variables &vars, short &busca);
void buscaSplay(Variables &vars, short &busca);
void buscaB(Variables &vars, short &busca);
void buscaNossaArvoreBalanc(Variables &vars, short &busca);
vector<Question> getVetQuestionsRand(vector<Question> &vetQuestions, const int &n);

void testViniman()
{
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

void testEdson()
{
	RBTree<int> rb;
	int random;
	for (int i = 0; i < 10; ++i)
	{
		random = rand() % 100;
		cout << random << " ";
		rb.insert(random);
	}
	cout << endl;
	rb.print();
	rb.remove(58);
	rb.print();
}

void testHumberto()
{
	TreapTree<int>* t = new TreapTree<int>();
	vector<int> vec;
	for (int i = 1; i <= 30; i++)
		vec.push_back(i);
	random_shuffle(vec.begin(), vec.end());
	t->insert(vec);
	//t->insert(1);
	//t->insert(10);
	//t->insert(-40);
	//t->insert(30);
	//t->insert(-50);
	t->print();
	
	TreapNode<int>* no = t->search(30);
	if(no != nullptr)
		cout << no->getValue();

	vector<int> vec2;
	int start = 15, end = 30;
	for (int i = start; i <= end; i++)
		vec2.push_back(i);
	random_shuffle(vec2.begin(), vec2.end());
	t->remove(vec2);
	cout << endl;
	t->printByOrder(IN_ORDER);

	for (int i = 0; i <= end; i++)
	{
		TreapNode<int>* no2 = t->search(i);
		if (no2 != nullptr)
			cout << no2->getValue() << endl;
	}

	system("pause");
}


int main(int argc, char** argv)
{
	if (argc == 2 && !strcmp(argv[1], "test"))
	{
		testViniman();
		return 0;
	}
	else if (argc == 2 && !strcmp(argv[1], "testedson"))
	{
		testEdson();
		return 0;
	}
	else if (argc == 2 && !strcmp(argv[1], "testluis"))
	{
		/*testLuis();*/
		return 0;
	}
	else if (argc == 4)
	{
		testHumberto();
		return 0;
	}

	//ofstream saida;
	/*saida.open("saida.txt", ios::app);
	saida << left << setw(12)<< left << "frequencia" << setw(12) << "Tags\n";
	for (int i = 0; i < 10; ++i)
		saida << left << setw(12) << 100 << setw(25) << 20 << endl;
	saida << "\n\n\n";
	saida << setw(12)<< left << "frequencia" << setw(12) << "UserIDs\n";
	for (int i = 0;i < 10; ++i)
		saida << left << setw(12)<< 100 << setw(12) << 20 << endl;
	*/

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
	vars.entryPath(argc == 1 ? "" : argv[1]);

	FileUtils::clearFileContent("saidaInsercao.txt");
	FileUtils::clearFileContent("saidaBusca.txt");
	FileUtils::clearFileContent("saidaRemocao.txt");

	if (vars.questionVector.empty())
		FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);
	if (vars.tagVector.empty())
		FileUtils::readFileTag(vars.tagPath, vars.tagVector);
	if (vars.answerVector.empty())
		FileUtils::readFileAnswer(vars.answerPath, vars.answerVector);

	openMenu(vars);

	return 0;
}


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
			remocao(vars, false);
			break;
		case 6:
			remocao(vars, true);
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
			case 0:
				openMenu(vars);
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

void busca(Variables &vars)
{
	short tempEscolhaBusca = vars.entry;
	string tempBuscaStr;
	if(tempEscolhaBusca == BUSCA_MAIS_FREQ)
		tempBuscaStr = "MAIS FREQUENTES";
	if(tempEscolhaBusca == BUSCA_MENOS_FREQ)
		tempBuscaStr = "MENOS FREQUENTES";
	if(tempEscolhaBusca == BUSCA_ALEATORIOS)
		tempBuscaStr = "ALEATORIAS";

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
		switch (vars.entry)
		{
			case 0:
				openMenu(vars);
			case 1:
				buscaAVL(vars, tempEscolhaBusca);
				break;
			case 2:
				buscaAVLModificada(vars, tempEscolhaBusca);
				break;
			case 3:
				buscaVermelhoPreta(vars, tempEscolhaBusca);
				break;
			case 4:
				buscaSplay(vars, tempEscolhaBusca);
				break;
			case 5:
				buscaB(vars, tempEscolhaBusca);
				break;
			case 6:
				buscaNossaArvoreBalanc(vars, tempEscolhaBusca);
				break;
			default:
				cout << "Opcao invalida. Tente novamente:" << endl;
				busca(vars);
		}
	}

}

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

			CompareCount::initializeCounters("Árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
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

			CompareCount::initializeCounters("Árvore AVL Modificada (fb normal=3)", static_cast<unsigned long>(vars.Ns[i]));
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

			CompareCount::initializeCounters("Árvore Vermelho e Preta", static_cast<unsigned long>(vars.Ns[i]));
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

			CompareCount::initializeCounters("Árvore Splay", static_cast<unsigned long>(vars.Ns[i]));
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

			CompareCount::initializeCounters("Árvore B", static_cast<unsigned long>(vars.Ns[i]));
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

			CompareCount::initializeCounters("Árvore Treap", static_cast<unsigned long>(vars.Ns[i]));
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

void remocaoAVL(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore AVL";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if(ordenado) {
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore AVL", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

void remocaoAVLModificada(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore AVL Modificada";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if(ordenado) {
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore AVL Modificada", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

void remocaoVermelhoPreta(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore Vermelho e Preta";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if(ordenado) {
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore Vermelho e Preta", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

void remocaoSplay(Variables &vars, bool ordenado)
{
	string str = "\n----------------------------------------------------";
	str += "\nRemocao em Arvore Splay";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if(ordenado) {
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore Splay", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if(ordenado) {
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore B", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

			///Remocao de Questoes na arvore
			tempVectorQuestions.clear();
			tempVectorQuestions = getVetQuestionsRand(vars.questionVector, vars.Ns[i]);
			if (ordenado)
			{
				QuickSort::quickSort(tempVectorQuestions);
			}

			CompareCount::initializeCounters("Remocao em Árvore Treap", static_cast<unsigned long>(vars.Ns[i]));
			CompareCount::setTimeStart();

			cout << "Removendo Questions da arvore...\n";
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

void buscaAVL(Variables &vars, short &busca)
{

}

void buscaAVLModificada(Variables &vars, short &busca)
{

}

void buscaVermelhoPreta(Variables &vars, short &busca)
{

}

void buscaSplay(Variables &vars, short &busca)
{

}

void buscaB(Variables &vars, short &busca)
{

}

void buscaNossaArvoreBalanc(Variables &vars, short &busca)
{

}

/**
 *
 * @param vetQuestions
 * @param n
 * @return
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