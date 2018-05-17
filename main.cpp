#include <iostream>
#include <limits>
#include "Headers/FileUtils.h"

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

int main(int argc, char** argv)
{
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