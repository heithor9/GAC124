#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

struct bilionarios{
	string nome;
	float fortuna;
	string fonte;
	string pais;
	int idade;
	string sexo;
};


int particionamentoDecrescente(bilionarios* bilionario, int c, int f) {

	string pivo = bilionario[c].nome;
	bilionarios pivoPrincipal = bilionario[c];
	int i = c+1, j = f;
	while (i <= j) {
	   if (bilionario[i].nome >= pivo) i++;
	   else if (pivo >= bilionario[j].nome) j--; 
	   else { 
		   swap (bilionario[i],bilionario[j]);
		   i++;
		   j--;
	   }
	}                 
	bilionario[c] = bilionario[j];
	bilionario[j] = pivoPrincipal;
	
	return j;

}


int particionamento(bilionarios* bilionario, int c, int f) {

	string pivo = bilionario[c].nome;
	bilionarios pivoPrincipal = bilionario[c];
	int i = c+1, j = f;
	while (i <= j) {
	   if (bilionario[i].nome <= pivo) i++;
	   else if (pivo <= bilionario[j].nome) j--; 
	   else { 
		   swap (bilionario[i],bilionario[j]);
		   i++;
		   j--;
	   }
	}                 
	bilionario[c] = bilionario[j];
	bilionario[j] = pivoPrincipal;
	
	return j;

}
   
void quickSort (bilionarios *bilionario, int posPivo, int fim) {

   int posNovoPivo;         
   if (posPivo < fim) {  
      posNovoPivo = particionamento(bilionario, posPivo, fim);
      quickSort(bilionario, posPivo, posNovoPivo- 1); 
      quickSort(bilionario, posNovoPivo + 1, fim); 
   }
}


void quickSortDecrescente (bilionarios *bilionario, int posPivo, int fim) {

   int posNovoPivo;         
   if (posPivo < fim) {  
      posNovoPivo = particionamentoDecrescente(bilionario, posPivo, fim);
      quickSortDecrescente(bilionario, posPivo, posNovoPivo- 1); 
      quickSortDecrescente(bilionario, posNovoPivo + 1, fim); 
   }
}



void escritaArqBinario(bilionarios* &bilionario, int tamanho) {
    ofstream arquivo("saida.bin", ios::binary); 

    for (int i = 0; i < tamanho; i++) {
        arquivo.write((char*)&bilionario[i], sizeof(bilionarios)); 
    }

    arquivo.close(); 
}



void buscaDirecionada (bilionarios* bilionario, int i, int fim) {
	i -= 1;
	cout << endl << endl;
	while (i < fim) 
	{
		cout << "Posicao #" << i+1 << ": " << bilionario[i].nome << endl
		<< "Fortuna: " << bilionario[i].fortuna << " bilhoes" << endl
		<< "Fonte da sua fortuna: " << bilionario[i].fonte << endl
		<< "Pais de origem: " << bilionario[i].pais << endl
		<< "Idade: " << bilionario[i].idade << endl
		<< "Sexo: " << bilionario[i].sexo << endl;
		cout << "=======================" << endl << endl;
		i++;
	}
	
	
}




void leituraArqBinario (bilionarios* bilionario, int tamanho) {
	ifstream arquivo("saida.bin", ios::in);
	arquivo.read((char*) bilionario, sizeof(bilionarios)*tamanho);
	arquivo.close();
	
	for (int i = 0; i < tamanho; i++)
	{
		cout << "Posicao #" << i+1 << ": " << bilionario[i].nome << endl
		<< "Fortuna: " << bilionario[i].fortuna << " bilhoes" << endl
		<< "Fonte da sua fortuna: " << bilionario[i].fonte << endl
		<< "Pais de origem: " << bilionario[i].pais << endl
		<< "Idade: " << bilionario[i].idade << endl
		<< "Sexo: " << bilionario[i].sexo << endl;
		cout << "=======================" << endl << endl;
		
	}
	
	
}

void leituraArqCsv(ifstream& arquivo_csv, bilionarios* bilionario, int numRegistros) {
	char lixo;
	string linha;


	for (int i = 0; i < numRegistros; i++){
	arquivo_csv.ignore();
	getline(arquivo_csv, bilionario[i].nome,',');
	arquivo_csv >> bilionario[i].fortuna;
	arquivo_csv >> lixo;
	getline(arquivo_csv,bilionario[i].fonte,',');
	getline(arquivo_csv,bilionario[i].pais,',');
	arquivo_csv >> bilionario[i].idade;
	arquivo_csv >> lixo;
	arquivo_csv >> bilionario[i].sexo;
	}
}



void escritaArqCsv(bilionarios* bilionario, int tamanho) {
	ofstream arquivo("Banco.csv");
	arquivo << "#nome,Fortuna em bilhões de dólares,Fonte da riqueza,País de origem,Idade" << endl;
	arquivo << tamanho;
	arquivo << endl;
	for (int i = 0; i < tamanho; i++)
	{
		arquivo << bilionario[i].nome << ',' << bilionario[i].fortuna << ','  
		<< bilionario[i].fonte << ',' << bilionario[i].pais << ',' 
		<< bilionario[i].idade << ',' << bilionario[i].sexo
		<< endl;
	}
	

}


int buscaBinaria(bilionarios* bilionario, string procurado, int inicio, int fim) {
	transform(procurado.begin(), procurado.end(), procurado.begin(), ::tolower);
	if (inicio <= fim)
	{
		int meio = (inicio+fim)/2;
		string aux = bilionario[meio].nome;
		transform(aux.begin(), aux.end(), aux.begin(), ::tolower);
		if (aux > procurado) 
			return buscaBinaria(bilionario, procurado, inicio, meio-1);
		
		else if (aux < procurado) 
			return buscaBinaria(bilionario, procurado, meio+1, fim);
		
		else 
			return meio;
	}
	
	else
		return -1;
}



void exclusaoVetor (bilionarios* bilionario, int posicao, int numRegistros) {
	
	for (int i = posicao; i < numRegistros-1; i++)
	{
		bilionario[i].nome = bilionario[i+1].nome;
		bilionario[i].fonte = bilionario[i+1].fonte;
		bilionario[i].fortuna = bilionario[i+1].fortuna;
		bilionario[i].pais = bilionario[i+1].pais;
		bilionario[i].sexo = bilionario[i+1].sexo;
		bilionario[i].idade = bilionario[i+1].idade;
	}
}



void encontrarPosicao(bilionarios* bilionario, string nomeBuscado, int &numRegistros) {
    bool encontrado = false;
    string nomeBilionario;
    transform(nomeBuscado.begin(), nomeBuscado.end(), nomeBuscado.begin(), ::tolower);
    int i = 0;

    while (i < numRegistros && !encontrado) {
        nomeBilionario = bilionario[i].nome;
        transform(nomeBilionario.begin(), nomeBilionario.end(), nomeBilionario.begin(), ::tolower);

        if (nomeBilionario == nomeBuscado) {
            encontrado = true;
            exclusaoVetor(bilionario, i, numRegistros);
            numRegistros--;
            cout << endl << "Cadastro excluido com sucesso!" << endl << endl;
        }
        i++;
    }

    if (!encontrado) {
        cout << endl << "Cadastro nao encontrado!" << endl << endl;
    }
}



void insercaoVetor (bilionarios* &bilionario, int& numRegistros, ifstream& arquivo_csv) {

    bilionarios* aumento = new bilionarios[numRegistros + 1]; 

    for (int i = 0; i < numRegistros; i++) {
        aumento[i] = bilionario[i]; 
    }
	cout << "Hora de criarmos um novo cadastro. Por favor, insira as informacoes." << endl << endl;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, aumento[numRegistros].nome);
    cout << "Fortuna (em bilhoes): ";
    cin >> aumento[numRegistros].fortuna;
    cout << "Fonte de sua fortuna: ";
    cin.ignore();
    getline(cin,aumento[numRegistros].fonte);
    cout << "Pais de origem: ";
    getline(cin, aumento[numRegistros].pais);
    cout << "Idade: ";
    cin >> aumento[numRegistros].idade;
    cout << "Sexo: ";
    cin >> aumento[numRegistros].sexo;

    int posicao = numRegistros; 
    while (posicao > 0 and aumento[posicao].fortuna > aumento[posicao - 1].fortuna) {
        swap(aumento[posicao], aumento[posicao - 1]);
        posicao--;
    }

    delete[] bilionario; 
    bilionario = aumento; 
    numRegistros++; 
    escritaArqCsv(bilionario, numRegistros);
    cout << endl << "Cadastro concluido com sucesso!" << endl << endl;
}



void buscaVetor (bilionarios* bilionario, int numRegistros) {
	string nomeBuscado;
	string sexoBuscado;
	int entrada;
	cout << "Escolha um dos filtros da busca" << endl <<
	"[1] - Nome" << endl <<
	"[2] - Sexo" << endl << endl;
	cout << "Digite um valor: ";
	cin >> entrada;
	bool teste = true;
	string nomeBilionario;
	string sexoBilionario;
	int i = 0;
	switch (entrada) {
		case 1:
			cin.ignore();
			cout << endl << "Digite o nome de quem voce procura: ";
			getline(cin,nomeBuscado);
			transform(nomeBuscado.begin(), nomeBuscado.end(), nomeBuscado.begin(), ::tolower);
			
			while (i < numRegistros and teste == true)
			{
				nomeBilionario = bilionario[i].nome;
				transform(nomeBilionario.begin(), nomeBilionario.end(), nomeBilionario.begin(), ::tolower);
				
				if (nomeBilionario == nomeBuscado)
				{
					cout << endl;
					cout << "Cadastro encontrado com sucesso!" << endl << endl;
					cout << "Posicao #" << i+1 << " do ranking: " << bilionario[i].nome << endl
					<< "Fortuna: " << bilionario[i].fortuna << " Bilhoes" << endl
					<< "Fonte de sua fortuna: " << bilionario[i].fonte << endl
					<< "Pais de origem: " << bilionario[i].pais << endl
					<< "Idade: " << bilionario[i].idade << " anos" << endl
					<< "Sexo: " << bilionario[i].sexo << endl << endl;
					teste = false;
				}
				
				i++;
			}
			
			if (teste == true)
			{
				cout << "Cadastro nao encontrado";
			}
			break;
			
		case 2:
			cin.ignore();
			cout << endl << "Digite o sexo dos bilionarios procurados: ";
			cin >> sexoBuscado;
			cout << endl;
			transform(sexoBuscado.begin(), sexoBuscado.end(), sexoBuscado.begin(), ::tolower);
			
			
			while (i < numRegistros)
			{
				sexoBilionario = bilionario[i].sexo;
				transform(sexoBilionario.begin(), sexoBilionario.end(), sexoBilionario.begin(), ::tolower);
				
				if (sexoBilionario == sexoBuscado)
				{
					
					cout << endl;
					cout << "Posicao #" << i+1 << " do ranking: "
					<< bilionario[i].nome << endl
					<< "Fortuna: " << bilionario[i].fortuna << " Bilhoes" << endl
					<< "Fonte de sua fortuna: " << bilionario[i].fonte << endl
					<< "Pais de origem: " << bilionario[i].pais << endl
					<< "Idade: " << bilionario[i].idade << " anos" << endl
					<< "Sexo: " << bilionario[i].sexo << endl <<
					"=======================" << endl;
					
					teste = false;
				}
				
				i++;
			}
			
			if (teste == true)
				cout << "As possibilidades sao: Masculino ou Feminino, tente novamente!" << endl << endl;
			
			else
				cout << endl <<  "Esses sao os bilionario do sexo " << sexoBuscado << " que fazem parte do ranking!" << endl << endl;
			
			break;
		
		default:
            cout << "Opcao invalida" << endl;
		}
}


string getClearCommand(){
	
	#ifdef _WIN32
		return "cls"; // Comando de limpeza no Windows
	#else
		return "clear"; // Comando de limpeza em sistemas Unix
	#endif
}

void limparTela() {
    system(getClearCommand().c_str());
}



int main(){
		
	ifstream arquivo_csv("Banco.csv");
	if (not(arquivo_csv))
		cout << "Erro: nao foi possivel abrir o arquivo de dados!";
	
	else{
	string linha;
	int numRegistros;
	
	getline(arquivo_csv, linha);
	arquivo_csv >> numRegistros;
	
	bilionarios *bilionario = new bilionarios[numRegistros];
	leituraArqCsv(arquivo_csv, bilionario, numRegistros);
	escritaArqBinario(bilionario, numRegistros);
	
	

	int entrada, entrada1, inicio, fim;
	string nomeProcurado, nomeExclusao;
	bool teste1 = true;
	
	
	while(teste1) {
		cout << "Opcoes disponiveis:" << endl <<
		"[1] - Fazer uma busca" << endl <<
		"[2] - Inserir um novo elemento" << endl <<
		"[3] - Ordenar o vetor em ordem alfabetica" << endl <<
		"[4] - Fazer uma busca de uma linha a outra" << endl << 
		"[5] - Excluir um cadastro" << endl <<
		"[6] - Mostrar todos os cadastrados (ordem de riqueza crescente)" << endl <<
		"[-1] - Sair" << endl << endl;
		cout << "Digite um valor: ";
		cin >> entrada;
		cout << endl;
		switch (entrada) {

			case 1:
				limparTela();
				buscaVetor(bilionario, numRegistros);
				break;
			
			case 2:
				limparTela();
				insercaoVetor(bilionario, numRegistros, arquivo_csv);
				escritaArqBinario(bilionario, numRegistros);
				leituraArqBinario(bilionario, numRegistros);
				break;
			
			case 3: 
				limparTela();
				cout << "Voce deseja ordenar por ordem crescente ou decrescente?" << endl;
				cout << "[1] - Crescente";
				cout << endl << "[2] - Decrescente" << endl << endl <<"Digite um valor: ";
				cin >> entrada1;
				cout << endl << endl;
				switch (entrada1) { 
					case 1:
						
						particionamento(bilionario, 0, numRegistros-1);
						quickSort(bilionario, 0, numRegistros-1);
						for (int i = 0; i < numRegistros; i++)
						{
							cout << "Posicao #" << i+1 << ": " << bilionario[i].nome << endl
							<< "Fortuna: " << bilionario[i].fortuna << " bilhoes" << endl
							<< "Fonte da sua fortuna: " << bilionario[i].fonte << endl
							<< "Pais de origem: " << bilionario[i].pais << endl
							<< "Idade: " << bilionario[i].idade << endl
							<< "Sexo: " << bilionario[i].sexo << endl;
							cout << "=======================" << endl << endl;
						}
						
						cout << "Aqui esta seu vetor ordenado em ordem alfabetica crescente!" << endl << endl;
						
					break;
					
					case 2:
						
						particionamentoDecrescente(bilionario, 0, numRegistros-1);
						quickSortDecrescente(bilionario, 0, numRegistros-1);
						for (int i = 0; i < numRegistros; i++)
						{
							cout << "Posicao #" << i+1 << ": " << bilionario[i].nome << endl
							<< "Fortuna: " << bilionario[i].fortuna << " bilhoes" << endl
							<< "Fonte da sua fortuna: " << bilionario[i].fonte << endl
							<< "Pais de origem: " << bilionario[i].pais << endl
							<< "Idade: " << bilionario[i].idade << endl
							<< "Sexo: " << bilionario[i].sexo << endl;
							cout << "=======================" << endl << endl;
						}
						
						cout << "Aqui esta seu vetor ordenado em ordem alfabetica decrescente!" << endl << endl;
					break;
				}
				
				break;
				
			case 4:
				cout << "Digite as linhas que voce deseja buscar" << endl;
				cout << "Linha inicial: "; cin >> inicio;
				cout << "Linha final: "; cin >> fim;
				buscaDirecionada(bilionario, inicio, fim);
				break;
			
			case 5:
				cout << "Digite o nome do bilionario que voce deseja excluir o cadastro: ";
				cin.ignore();
				getline(cin, nomeExclusao);
				encontrarPosicao(bilionario,nomeExclusao,numRegistros);
				escritaArqBinario(bilionario, numRegistros);
				escritaArqCsv(bilionario,numRegistros);
				break;
			
			case -1:
				cout  << "Programa finalizado. Volte sempre!";
				teste1 = false;
				break;
			
			case 6:
				leituraArqBinario(bilionario, numRegistros);
				
				break;
			default:
				cout << "Opcao invalida!" << endl << endl;
				break;
		}
	}
	
	} 
	arquivo_csv.close();
	
return 0;
}
