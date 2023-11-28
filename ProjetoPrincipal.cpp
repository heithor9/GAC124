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
	int i = c+1, j = f;
	while (i <= j) {
	   if (bilionario[i].nome >= pivo) i++;
	   else if (pivo >= bilionario[j].nome) j--; 
	   else { 
		   swap (bilionario[i].nome,bilionario[j].nome);
		   swap (bilionario[i].fortuna,bilionario[j].fortuna);
		   swap	(bilionario[i].fonte,bilionario[j].fonte);
		   swap (bilionario[i].pais,bilionario[j].pais);
		   swap (bilionario[i].idade,bilionario[j].idade);
		   swap (bilionario[i].sexo,bilionario[j].sexo);
		   i++;
		   j--;
	   }
	}                 
	bilionario[c].nome = bilionario[j].nome;
	bilionario[j].nome = pivo;
	
	return j;

}


int particionamento(bilionarios* bilionario, int c, int f) {

	string pivo = bilionario[c].nome;
	int i = c+1, j = f;
	while (i <= j) {
	   if (bilionario[i].nome <= pivo) i++;
	   else if (pivo <= bilionario[j].nome) j--; 
	   else { 
		   swap (bilionario[i].nome,bilionario[j].nome);
		   swap (bilionario[i].fortuna,bilionario[j].fortuna);
		   swap	(bilionario[i].fonte,bilionario[j].fonte);
		   swap (bilionario[i].pais,bilionario[j].pais);
		   swap (bilionario[i].idade,bilionario[j].idade);
		   swap (bilionario[i].sexo,bilionario[j].sexo);
		   i++;
		   j--;
	   }
	}                 
	bilionario[c].nome = bilionario[j].nome;
	bilionario[j].nome = pivo;
	
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



void leituraArqBinario (bilionarios* bilionario, int tamanho) {
	ifstream arquivo("saida.bin");
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
    cin.ignore();
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
    cout << endl << "Cadastro concluido com sucesso!";
}


void buscaVetor (bilionarios* bilionario, int numRegistros) {
	string nomeBuscado;
	string sexoBuscado;
	int entrada;
	cout << "Escolha um dos filtros da busca" << endl <<
	"1 - Nome" << endl <<
	"2 - Sexo" << endl << endl;
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
			
			while (i < numRegistros or teste == true)
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
			cout << "Esses sao os bilionario do sexo " << sexoBuscado << " que fazem parte do ranking"<< endl;
			
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
					<< "Sexo: " << bilionario[i].sexo << endl << endl;
				}
				
				i++;
			}
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
	leituraArqBinario(bilionario, numRegistros);
	
	cout << "Opcoes disponiveis:" << endl <<
	"1 - Fazer uma busca" << endl <<
	"2 - Inserir um novo elemento" << endl <<
	"3 - Ordenar o vetor em ordem alfabetica" << endl << endl;
	int entrada, entrada1, num;

	cout << "Digite um valor: ";
	cin >> entrada;
	
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
			cout << "1 - Crescente";
			cout << endl << "2 - Decrescente" << endl << endl <<"Digite um valor: ";
			cin >> entrada1;
			switch (entrada1) { 
				case 1:
					cout << "Aqui esta seu vetor ordenado em ordem alfabetica crescente!" << endl << endl;
					particionamento(bilionario, 0, numRegistros-1);
					num = particionamento(bilionario, 0, numRegistros-1);
					quickSort(bilionario, num, numRegistros-1);
					escritaArqBinario(bilionario, numRegistros);
					leituraArqBinario(bilionario, numRegistros);
					
				break;
				
				case 2:
					cout << "Aqui esta seu vetor ordenado em ordem alfabetica decrescente!" << endl << endl;
					particionamentoDecrescente(bilionario, 0, numRegistros-1);
					num = particionamentoDecrescente(bilionario, 0,numRegistros-1);
					quickSortDecrescente(bilionario, 0, numRegistros-1);
					escritaArqBinario(bilionario, numRegistros);
					leituraArqBinario(bilionario, numRegistros);
					
			}
			break;
			
			
		default:
            cout << "Opcao invalida" << endl << endl;
		
	}
	
	} 
	arquivo_csv.close();
	
return 0;
}
