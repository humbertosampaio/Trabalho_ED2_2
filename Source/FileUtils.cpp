//
// Created by edson on 28/03/18.
//

#include "../Headers/FileUtils.h"

void FileUtils::clearFileContent(string path)
{
	ofstream writer(path, std::ofstream::out | std::ofstream::trunc);
	if (writer.is_open())
	{
		writer.clear();
		writer << "-----------------------------------------" << endl;
		writer << "Trabalho de Estrutura de Dados 2" << endl;
		writer << "Autores: Edson, Humberto, Luis e Vinicius" << endl;
		writer << "ANALISE DOS ALGORITMOS E BASE DE DADOS" << endl;
		writer << "-----------------------------------------" << endl << endl;
	}
	else
		cout << "Falha ao limpar o conteudo do arquivo \"" << path << "\"." << endl;
}

void FileUtils::readFileQuestion(string path, vector<Question> &questionList)
{
	fstream file;
	file.open(path.c_str());

	if (file.is_open())
	{
	    cout << "\tLendo arquivo de registros Questions.csv" << endl;
	    cout << "\tPath (caminho): " << path << endl;
		//variavel para calcular tempo de execucao
		clock_t tStart = clock();

		//lendo o arquivo em blocos de 4MB
		unsigned int length = 4 * 1024 * 1024;

		//criando e inicializando buffer
		char *buffer = new char[length];
		file.read(buffer, length);

		//variaveis auxiliares
		string tempString;
		string *obj = new string[6];
		int objPosition = 0;
		int quotationMarksCount = 0;
		long registriesCount = 0;
		int i = 0;

		//ignorando cabecalho
		for (; buffer[i] != '\n'; ++i);

		//iteracao principal
        string progressBar;
        cout<< "\tLendo Questions.csv\n";
		while (!file.eof())
		{
			while (++i < length && buffer[i] != char_traits<char>::eof())
			{
				if (buffer[i] != ',' && buffer[i] != '\n')
				{
					if (buffer[i] == '"')
						quotationMarksCount++;
					tempString.push_back(buffer[i]);
				} else if (quotationMarksCount % 2 == 0)
				{
					obj[objPosition] = tempString;
					tempString.clear();
					++objPosition;
				}
				if (objPosition > 5)
				{
					questionList.emplace_back(obj);
					registriesCount++;

                    if (registriesCount % 24000 == 0)
                    {
                        progressBar += "=";
                        cout << "\t" << right<< "["<< progressBar<< setw(27-(registriesCount/24000)) << "] " << (registriesCount / 6000) << "%\r" << std::flush;
                    }

					objPosition = 0;
					quotationMarksCount = 0;
					delete[] obj;
					obj = new string[6];
				}
			}
			file.read(buffer, length);
			i = -1;
		}
        cout << endl;
        resetiosflags;
		cout << "\tTempo gasto na leitura: " << (double) (clock() - tStart) / CLOCKS_PER_SEC << "s" << endl << endl;
		file.close();
		delete[] buffer;
		delete[] obj;
		return;
	}
	cout << "\tFalha na leitura do arquivo!" << endl;
	cout << "\tO caminho tentado foi: \"" << path << "\"." << endl;
	cout << "\tVERIFIQUE se digitou o nome do diretorio path corretamente." << endl;
	exit(0);
}

void FileUtils::readFileTag(string path, vector<Tag> &tagList)
{
	fstream file;
	file.open(path.c_str());

	if (file.is_open())
	{

        int registriesCount = 0;
		string tag;
		int questionId;
		int atualId;
		file >> tag;
        file >> questionId >> tag;
        tag.erase(0, 1);
        atualId = questionId;
        list<string> atualList;
        atualList.push_back(tag);

        string progressBar;
        cout << "\tLendo arquivo de registros Tags.csv" << endl;
		cout << "\tPath (caminho): " << path << endl;
		while (file >> questionId >> tag)
		{
			//apaga a virgua da string
			tag.erase(0, 1);
            if (atualId != questionId) {
                tagList.emplace_back(atualId, atualList);
                atualList.clear();
            }
            ++registriesCount;
            atualList.push_back(tag);
            atualId = questionId;

            if (registriesCount % 75000 == 0)
            {
                progressBar += "=";
                cout << right<< "\t["<< progressBar<< setw(25-(registriesCount/75000)) << "] " << registriesCount/18750 << "%\r" << std::flush;
           }
		}
        cout << endl;
        resetiosflags;
        tagList.emplace_back(atualId, atualList);
        file.close();
        return;
    }
	cout << "falha na leitura do arquivo!" << endl;
}

void FileUtils::readFileAnswer(string path, vector<Answer> &answerList)
{
	fstream file;
	file.open(path.c_str());

	if (file.is_open())
	{
		//variavel para calcular tempo de execucao

		//lendo o arquivo em blocos de 4MB
		unsigned int length = 4 * 1024 * 1024;

		//criando e inicializando buffer
		char *buffer = new char[length];
		file.read(buffer, length);

		//variaveis auxiliares
		string tempString;
		string *obj = new string[6];
		int objPosition = 0;
		int quotationMarksCount = 0;
		long registriesCount = 0;
		int i = 0;

		//ignorando cabecalho
		for (; buffer[i] != '\n'; ++i)
			;

        //iteracao principal
        string progressBar = "=";
        cout << "\tLendo arquivo de registros Answers.csv" << endl;
		cout << "\tPath (caminho): " << path << endl;
        while (!file.eof())
        {
            while (++i < length && buffer[i] != char_traits<char>::eof())
            {
                if (buffer[i] != ',' && buffer[i] != '\n')
                {
                    if (buffer[i] == '"')
                        quotationMarksCount++;
                    tempString.push_back(buffer[i]);
                } else if (quotationMarksCount % 2 == 0)
                {
                    obj[objPosition] = tempString;
                    tempString.clear();
                    ++objPosition;
                }
                if (objPosition > 5)
                {
                    answerList.emplace_back(obj);
                    registriesCount++;

                    if (registriesCount % 38400 == 0)
                    {
                        progressBar += "=";
                        cout << right<< "\t["<< progressBar<< setw(27-(registriesCount/38400)) << "] " << registriesCount/9550 << "%\r" << std::flush;
                        //cout << right<< "\t["<< progressBar<< setw(27-(registriesCount/40000)) << "] " << registriesCount/1000 << "%\r" << std::flush;
                    }

                    objPosition = 0;
                    quotationMarksCount = 0;
                    delete[] obj;
                    obj = new string[6];
                }
            }
            file.read(buffer, length);
            i = -1;
        }
        cout << endl;
        resetiosflags;
        file.close();
        delete[] buffer;
        delete[] obj;
        return;
    }
    cout << "falha na leitura do arquivo!" << endl;
}

vector<int> FileUtils::readInputFile(string path)
{
	ifstream reader(path, std::ifstream::in);
	vector<int> vector;
	if (reader.is_open())
	{
		int line, n, i = 0;
		reader >> n;
		while (reader >> line)
		{
			vector.push_back(line);
			i++;
		}

		if (n != i)
		{
			cout << "ERRO! Tente novamente!" << endl;
			cout << "Arquivo de entrada fora do padrao!" << endl;
			cout << "O numero fornecido na primeira linha do arquivo nao reflete a quantidade de N's." << endl;
			FileUtils::endProgram();
		}
	}
	else
	{
		cout << "ERRO na leitura do arquivo de entrada!" << endl;
		cout << "O caminho tentado foi: \"" << path << "\"." << endl;
		cout << "Verifique se o arquivo de entrada se encontra no mesmo diretorio do executavel" << endl;
		pauseScreen(true);
		endProgram();
	}
	return vector;
}

void FileUtils::writeToOutputFile(const string &outputFileName, const string &text)
{
	ofstream writer(outputFileName, ios::app);
	if (writer.is_open())
	{
		writer << text << endl;
		writer.close();
	}
	else
		cout << "Falha ao escrever no arquivo \"" << outputFileName << "\"." << endl;
}


void FileUtils::endProgram()
{
    cout << "\n*---------------------------------------------------------------------------------*" << endl;
	cout << "*                  --             FIM DO PROGRAMA             --                  *" << endl;
	cout << "*                    Os resultados dos testes foram salvos no                     *" << endl;
	cout << "*               arquivo \"saida.txt\" dentro do path do executavel.                 *" << endl;
	cout << "**Obs: Salve seu arquivo de saida, pois ele sera sobreescrito na proxima execucao**" << endl;
	cout << "*---------------------------------------------------------------------------------*" << endl;
	pauseScreen(false);
	exit(0);
}

void FileUtils::pauseScreen(bool continuar)
{
	int c;
	cout << endl << "Pressione <Enter> para " << (continuar ? "continuar" : "fechar");
	cout << " o algoritmo...." << endl;
    while ((c = getchar()) != '\n' && c != EOF);
	clearerr(stdin);
	//getchar();
}

void FileUtils::showTop()
{
    cout << "         --------------------------------------------------" << endl;
    cout << "         -  --------------------------------------------  -" << endl;
    cout << "         -  -  -  Trabalho de Estrutura de Dados 2  -  -  -" << endl;
    cout << "         -  --------------------------------------------  -" << endl;
    cout << "         --------------------------------------------------" << endl;
    cout << "         ---------          -> AUTORES <-         ---------" << endl;
    cout << "         --------            Edson Lopes        -----------" << endl;
    cout << "         --------         Humberto Sampaio          -------" << endl;
    cout << "         ------------       Luis Henrique     -------------" << endl;
    cout << "         ----------        Vinicius Carlos       ----------" << endl;
    cout << "         --------------------------------------------------" << endl;
    cout << "         --------------------------------------------------" << endl;
	pauseScreen(true);
    cout << "---------------------------- INFORMACOES ----------------------------" << endl;
    cout << "-> Os arquivos de saida serao gerados no diretorio do executavel" << endl;
	cout << "-> Os arquivos de entrada precisam estar no diretorio do executavel" << endl;
    cout << "-> Para executar use: <./NomeDoExecutavelCompilado> <path>" << endl;
	cout << "-> Caso nao passe a path por linha de comando, o diretorio onde esta" << endl;
	cout << "   o executavel sera considerado como path." << endl;
    cout << "-> Os arquivos usados (Answers.csv, Questions.csv, Tags.csv) precisam" << endl;
    cout << "   estar na pasta pythonquestions que fica no diretorio informado." << endl;
    cout << "---------------------------- INFORMACOES ----------------------------" << endl;
    pauseScreen(true);
}