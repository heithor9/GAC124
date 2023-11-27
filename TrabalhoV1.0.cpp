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
	"2 - Inserir um novo elemento" << endl << endl;
	
	int entrada;
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
		
			
		default:
            cout << "Opcao invalida" << endl;
		
	}
	
	} 
	arquivo_csv.close();
	
return 0;
}
