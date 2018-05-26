#include <cstring>
#include <BTree.h>
#include "Headers/FileUtils.h"
#include "Source/BinaryTree.cpp"
#include "Source/SplayTree.cpp"
#include "Source/AvlTree.cpp"
#include "Source/RBTree.cpp"
#include "Source/BTree.cpp"

/// ->>>>> Criar classe de impressao, para imprimir arvores, etc e tirar os metodos das classes arvores



using namespace std;

struct Variables
{
    vector<Question> questionVector;
    vector<Answer> answerVector;
    vector<Tag> tagVector;
    vector<int> intVector;

    string sourceFileName;
    string path;
    string questionPath;
    string answerPath;
    string tagPath;

    vector<int> Ns;
    unsigned long N;
    int section;
    int cenary;
    int entry;

    void entryPath(string _path) {
        path = _path;
        if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/' && !path.empty())
            path.push_back('/');
        if(!path.empty())
            cout << "Path informado: " << path << endl;
        else
            cout << "Como nao foi informado a path, consideraremos o diretorio do executavel como path" << endl;
        questionPath = path + "pythonquestions/Questions.csv";
        answerPath = path + "pythonquestions/Answers.csv";
        tagPath = path + "pythonquestions/Tags.csv";
        sourceFileName = path + "entrada.txt";
    }
};


void testViniman()
{
    BTree<Question> bt;
    string* str = new string[5];
    str[0] = "023";
    str[1] = "33";
    str[2] = "11";
    str[3] = "93";
    str[4] = "32";
    Question qt1(str);
    cout << "Question " << qt1 << endl;
    str[0] = "2";
    str[1] = "333";
    str[2] = "1";
    str[3] = "3";
    str[4] = "9";
    Question qt2(str);
    str[0] = "200";
    str[1] = "39";
    str[2] = "33";
    str[3] = "44";
    str[4] = "66";
    Question qt3(str);
    str[0] = "1";
    str[1] = "39";
    str[2] = "33";
    str[3] = "44";
    str[4] = "66";
    Question qt4(str);
    str[0] = "5";
    str[1] = "39";
    str[2] = "33";
    str[3] = "44";
    str[4] = "66";
    Question qt5(str);
    bt.insere(qt2);
    bt.insere(qt3);
    bt.insere(qt1);
    bt.insere(qt5);
    bt.insere(qt4);
    //bt.insere(qt4);
    bt.imprime();

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
    RBTree<int> rbt;
    rbt.insert(530);
    rbt.insert(40);
    rbt.insert(90);
    rbt.print();
}

void testHumberto()
{
    /*
	AvlTree<int>* a = new AvlTree<int>();
	a->insert(1);
	a->insert(10);
	a->insert(-40);
	a->insert(30);
	a->insert(-50);
	a->print();
	a->remove(-40);
	a->print();

	cout << endl;
	SplayTree<int>* b = new SplayTree<int>();
	b->insert(1);
	b->insert(10);
	b->insert(-40);
	b->insert(30);
	b->insert(-50);
	b->print();
	b->remove(-40);
	b->print();
	system("pause");
     */
}


int main(int argc, char** argv)
{
    if(argc == 2 && !strcmp(argv[1], "test"))
    {
        testViniman();
        return 0;
    }
    else if(argc == 2 && !strcmp(argv[1], "testedson"))
    {
        testEdson();
        return 0;
    }
    else if ( argc == 2 && !strcmp(argv[1], "testluis"))
    {
        /*testLuis();*/
        return 0;
    }
	else if (argc == 1 && false)
	{
		testHumberto();
		return 0;
	}

    ofstream saida;
    saida.open("saida.txt", ios::app);
    saida << left << setw(12)<< left << "frequencia" << setw(12) << "Tags\n";
    for (int i = 0; i < 10; ++i)
        saida << left << setw(12) << 100 << setw(25) << 20 << endl;
    saida << "\n\n\n";
    saida << setw(12)<< left << "frequencia" << setw(12) << "UserIDs\n";
    for (int i = 0;i < 10; ++i)
        saida << left << setw(12)<< 100 << setw(12) << 20 << endl;


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
    vars.entryPath(argc==1 ? "" : argv[1]);
    vars.Ns = FileUtils::readInputFile(vars.sourceFileName);
    vars.N = vars.Ns.size();
    FileUtils::clearFileContent("saida.txt");

    if(vars.questionVector.empty())
        FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);
    if(vars.tagVector.empty())
        FileUtils::readFileTag(vars.tagPath, vars.tagVector);
    if(vars.answerVector.empty())
        FileUtils::readFileAnswer(vars.answerPath, vars.answerVector);
    return 0;
}




void openMenu(Variables &vars)
{
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "||            TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS              ||" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "||                    INSIRA O CODIGO DA OPCAO ESCOLHIDA                       ||" << endl;
    cout << "Opcao 0: Sair e encerrar a execucao" << endl;
    cout << "Opcao 1: Gerar uma arvore AVL" << endl;
    cout << "Opcao 2: Gerar uma arvore AVL Modificada [Balanceada se fb esta entre -3 e 3]" << endl;
    cout << "Opcao 2: Gerar uma arvore Vermelho e Preta" << endl;
    cout << "Opcao 2: Gerar uma arvore Splay" << endl;
    cout << "Opcao 2: Gerar uma arvore B" << endl;
    cout << "Opcao 2: Gerar uma arvore ..... (MinhaArvoreDeBalanceamento)" << endl;
    cout << "----------" << endl;
    cout << "Opcao: ";
    cin >> vars.section;
    cout << "||---------------------------------------------------------------------------------||" << endl;
    switch (vars.section)
    {
        case 0:
            FileUtils::endProgram();
        case 1: /// Secao 1
            //section1(vars);
            break;
        case 2: /// Secao 2
            int param;
            //section2(vars);
            break;
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

void section1(Variables &vars) {
    if(vars.questionVector.empty())
        FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);
    do {
        cout << "\t---------------------------------------------------------------------------------" << endl;
        cout << "\tEscolha o cenario:" << endl;
        cout << "\tCenario 1: Impacto de diferentes estruturas de dados" << endl;
        cout << "\tCenario 2: Impacto de variacoes do Quicksort" << endl;
        cout << "\tCenario 3: QuickSort X InsertionSort X MergeSort X HeapSort X MeuSort(CombSort)" << endl;
        cout << "\tCenario 4: Tratamento de Colisoes: Enderecamento X Encadeamento" << endl;
        cout << "\t0: Voltar" << endl;
        cout << "\t----------" << endl;
        cout << "\tOpcao: ";
        cin >> vars.cenary;
        cout << "\t---------------------------------------------------------------------------------" << endl;
        switch (vars.cenary) {
            case 0:
                openMenu(vars);
                break;
            case 1: // Secao 1, Cenario 1
                //section1_cenary1(vars);
                break;
            case 2: // Secao 1, Cenario 2
                //section1_cenary2(vars);
                break;
            case 3: // Secao 1, Cenario 3
                //section1_cenary3(vars);
                break;
            case 4: // Secao 1, Cenario 4
                //section1_cenary4(vars);
                break;
            default:
                cout << "\tCenario Invalido. Tente novamente" << endl;
                section1(vars);
        }
    } while (vars.cenary >= 1 && vars.cenary <= 4);
}
