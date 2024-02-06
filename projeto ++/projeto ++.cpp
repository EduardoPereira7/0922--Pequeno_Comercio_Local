#include <iostream>
#include <windows.h> //para as arrow keys
#include <string>
#include <iomanip>
#pragma warning(disable: 4996)  //ignorar os warnings sobre a funcao da data

using namespace std;
COORD CursorPosition; // usado para o goto
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // para cores

void menuClientes(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void menuPrincipal(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void menuRelatorios(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void menuStock(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void removerCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void alterarNomeCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void adicionarCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void imprimirClientes(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void adicionarStock(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void removerProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void adicionarProduto(string** matVendas, string** matProdutos, string** matClientes, int* countIDD);
void imprimirProdutos(string** matVendas, string** matProdutos, string** matClientes, int* countID, bool, bool);
void gotoXY(int, int);
void defaultCliente(int* countID, string nome, string telefone, string morada, string** matClientes);
void defaultProduto(int* countID, string nome, string quantidade, string custo, string** matProdutos);
void vendas(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void mostrarTalao(string** matCheckout, string** matVendas, string** matProdutos, string** matClientes, int* countID, int lastVenda);
void totalvendas(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void vendasPorProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID);
void vendasPorCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID);

string** criarMatClientes();
string** criarMatProdutos();
string** criarMatVendas();
string* selecionarProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID);
string** checkout(string** matVendas, string** matProdutos, string** matClientes, int* countID);

///////////////////////////////////////////////////////////////////VENDAS//////////////////////////////////////////////////////////////////

void mostrarTalao(string** matCheckout, string** matVendas, string** matProdutos, string** matClientes, int* countID, int lastVenda) { //funçao para imprimir o talao
	int countLinha = 1, seraQue = rand() % 10000 + 1, vaiSair = rand() % 10000 + 1;
	double valorEntregue = 0;
	if (seraQue == vaiSair) {  //Verifica se os dois randoms são iguais para oferecer a compra
		cout << "Parabéns. Foi premiado com uma oferta total da sua compra atual.";
	}
	else {
		cout << "Valor a pagar: " << stod(matVendas[lastVenda][2]) * 1.23 << ". Insira o valor entregue: ";
		cin >> valorEntregue;
		if (valorEntregue < (stod(matVendas[lastVenda][2]) * 1.23)) {
			do
			{
				cout << "\n!! Introduza um valor superior ao valor a pagar:";
				cin >> valorEntregue;
			} while (valorEntregue < stod(matVendas[lastVenda][2]) * 1.23);
		}
	}
	system("cls");
	cout << "\n\n\t\t      TALÃO\n\n";
	cout << "\tDt/Hr:    " << matVendas[lastVenda][3] << "\n";
	cout << "\tVenda nº " << matVendas[lastVenda][0] << "\n";
	cout << "\tCliente nº " << matVendas[lastVenda][1] << "\n";
	cout << "\t..................................\n";
	cout << "\t\t     Artigos\n\n";
	for (int i = 1; i < 20; i++)
	{
		if (matCheckout[i][0] != "0") {
			cout << "\t" << countLinha << ". " << matCheckout[i][1] << "\t\t     " << stod(matCheckout[i][3]) << "\n\t     Quant: " << matCheckout[i][2] << "\t\t   (s/IVA)\n";
			countLinha++;
		}
	}
	cout << "\t..................................\n";
	cout << "\t\t    Resumo IVA\n\n";
	cout << "\tTaxa      " << "Valor     " << "IVA      " << "Total\n";
	cout << "\t\t (s/IVA)" << "\t   (c/IVA)\n";
	cout << "\t23%       " << stod(matVendas[lastVenda][2]) << "\t    " << stod(matVendas[lastVenda][2]) * 0.23 << "     " << stod(matVendas[lastVenda][2]) * 1.23 << "\n";
	if (seraQue == vaiSair) {
		cout << "Oferta de " << stod(matVendas[lastVenda][2]) * 1.23 << ".";
	}
	else {
		cout << "        ..................................\n";
		cout << "\t\t    Pagamento\n\n";
		cout << "\tValor Entregue: " << "\t     " << valorEntregue << "\n";
		cout << "\tTroco: " << "\t\t\t     " << valorEntregue - stod(matVendas[lastVenda][2]) * 1.23 << "\n";
	}
	cout << "\n\n\n Precisone Enter para sair";
	system("pause>nul");
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);
}

void vendas(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	int idCliente, lastVenda = 0, totalProd = 0, aux = 0;
	double valorTotal = 0.0;
	//string  data = __TIMESTAMP__;
	string** matCheckout = checkout(matVendas, matProdutos, matClientes, countID);
	imprimirClientes(matVendas, matProdutos, matClientes, countID);
	//falta verificaçao do ID
	for (int i = 1; i < 20; i++)
	{
		if (stoi(matClientes[i][0]) > (aux))
		{
			(aux = stoi(matClientes[i][0]));
		}
	}
	if (aux != 0)
	{
		cout << "Insira do ID de Cliente que está a comprar: ";
		cin >> idCliente;
		if (idCliente > aux || idCliente <= 0) {
			while (idCliente > aux || idCliente <= 0) {
				cout << "Introduza um valor válido correspondente aos IDs de cliente apresentados: ";
				cin >> idCliente;
			}
		}
		if (idCliente <= aux && idCliente > 0)
		{
			for (int i = 1; i < 20; i++)  //calcular valor total
			{
				if (matCheckout[i][0] != "0") {
					valorTotal += stod(matCheckout[i][3]);
					totalProd += stoi(matCheckout[i][2]);
				}
				else break;
			}
			for (int i = 1; i < 101; i++)
			{
				if (matVendas[i][0] == "0")
				{
					matVendas[i][0] = to_string(countID[2]);
					countID[2]++;
					matVendas[i][1] = to_string(idCliente);
					matVendas[i][2] = to_string(valorTotal);
					time_t timetoday;
					time(&timetoday);
					matVendas[i][3] = asctime(localtime(&timetoday));
					lastVenda = i;
					break;
				}
			}
			for (int i = 1; i < 20; i++)  //ciclo para adicionar numero de produtos comprados nos clientes
			{
				if (matClientes[i][0] == to_string(idCliente))
					matClientes[i][4] = to_string(stoi(matClientes[i][4]) + totalProd);
				break;
			}
			for (int i = 1; i < 20; i++)
			{
				if (matCheckout[i][0] == "0")
					break;
				for (int j = 1; j < 20; j++)
				{
					if (matCheckout[i][0] == matProdutos[j][0] && matProdutos[j][0] != "0") {
						matProdutos[j][4] = to_string(stoi(matProdutos[j][4]) + stoi(matCheckout[i][2]));
						break;
					}
				}
			}
			return mostrarTalao(matCheckout, matVendas, matProdutos, matClientes, countID, lastVenda);
		}
	}
	else
	{
		cout << "\n" << "Não existe nenhum cliente para fazer a venda." << "\n" << "Precisone Enter para voltar.";
		system("pause>nul");
		return menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

string** checkout(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	int opcao, countLinha = 1;
	string** matCheckout = new string * [20];  //criar a matriz para o Checkout
	for (int i = 0; i < 20; i++)
	{
		matCheckout[i] = new string[4];
	}
	matCheckout[0][0] = "ID Prod.";
	matCheckout[0][1] = "Nome";
	matCheckout[0][2] = "Quant.";
	matCheckout[0][3] = "Preço s/IVA";
	for (int i = 1; i < 20; i++) { //igualar matriz a zero
		for (int j = 0; j < 4; j++)
		{
			matCheckout[i][j] = "0";
		}
	}
	do {
		system("cls");
		string* vecProd = selecionarProduto(matVendas, matProdutos, matClientes, countID);
		for (int i = 1; i < 20; i++)
		{
			if (matCheckout[i][0] == vecProd[0]) {
				matCheckout[i][2] = to_string(stoi(matCheckout[i][2]) + stoi(vecProd[2]));
				matCheckout[i][3] = to_string(stof(matCheckout[i][3]) + stof(vecProd[3]));
				break;
			}
			else if (matCheckout[i][0] == "0") {
				matCheckout[i][0] = vecProd[0];
				matCheckout[i][1] = vecProd[1];
				matCheckout[i][2] = vecProd[2];
				matCheckout[i][3] = vecProd[3];
				break;
			}
		}
		cout << "\n\nCarrinho:\n\n";
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 4; j++)
			{
				if (matCheckout[i][0] != "0") {
					if (j == 3 && i > 0)
						cout << stof(matCheckout[i][j]) * 1.3;
					else if (i == 0 && j == 3)
						cout << "Preço s/IVA";
					else
						cout << matCheckout[i][j] << "\t" << "\t";
				}
			}
			if (matCheckout[i][0] != "0")
				cout << "\n";
		}
		cout << "\n" << "\t" << "Quer comprar mais? Se sim prima 1, para finalizar prima 2.\n";
		cin >> opcao;
	} while (opcao == 1);
	return matCheckout;
}

string* selecionarProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID) { //funcao bool para criar do while que repete enquanto quiser comprar mais produtos
	bool flag = false, ligado = true;
	int i, x = 8, opcao = 0, ID, qnt, aux = 0; //qnt=quantidade de produto a comprar
	string* vecProd = new string[4];
	imprimirProdutos(matVendas, matProdutos, matClientes, countID, flag, true); //imprimir com custo*1.3
	for (int i = 1; i < 20; i++)
	{
		if (stoi(matProdutos[i][0]) > (aux))
		{
			(aux = stoi(matProdutos[i][0]));
		}
	}
	if (aux != 0)
	{
		cout << "Insira o ID do produto a adquirir: ";
		cin >> ID;
		if (ID > aux || ID <= 0) {
			while (ID > aux || ID <= 0) {
				cout << "Introduza um valor válido correspondente aos IDs dos produtos em stock: ";
				cin >> ID;
			}
		}
		if (ID <= aux && ID > 0)
		{
			for (i = 1; i < 20; i++)
			{
				if (matProdutos[i][0] == to_string(ID)) {
					do {
						cout << "Quantidade: " << "\n";
						cin >> qnt;
						if (qnt > stoi(matProdutos[i][2]) || qnt <= 0)
							cout << "Nao pode adquirir essa quantidade. A quantidade em stock é " << matProdutos[i][2] << ".\n";
					} while (qnt > stoi(matProdutos[i][2]) || qnt <= 0);
					matProdutos[i][2] = to_string(stoi(matProdutos[i][2]) - qnt);
					break;
				}
			}
			vecProd[0] = matProdutos[i][0];										 /*ID produto*/
			vecProd[1] = matProdutos[i][1];										 /*Nome Produto*/
			vecProd[2] = to_string(qnt);                                    /*quantidade para compra*/
			vecProd[3] = to_string(stof(matProdutos[i][3]) * qnt);       /*preço s/ IVA*/
			return vecProd;
		}
	}
	else
	{
		cout << "\n" << "Sem stock de produtos." << "\n" << "Precisone Enter para voltar.";
		system("pause>nul");
		menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

///////////////////////////////////////////////////////////////////PRODUTOS////////////////////////////////////////////////////////////////

void imprimirProdutos(string** matVendas, string** matProdutos, string** matClientes, int* countID, bool menu, bool preco) {
	cout << "\n";
	if (preco) {
		for (int i = 0; i < 20; i++) { //imprimir a matriz dos produtos para vendas
			for (int j = 0; j < 4; j++)
			{
				if (matProdutos[i][0] != "0") {
					if (j == 3 && i > 0)
						cout << stof(matProdutos[i][j]) * 1.3;  //setprecision imprime pelo menos (2) casas decimais, fixed limita a (2).
					else if (i == 0 && j == 3)
						cout << "Preço s/IVA";
					else
						cout << matProdutos[i][j] << "\t" << "\t";
				}
			}
			if (matProdutos[i][0] != "0")
				cout << "\n";
		}
		return;
	}
	else {
		for (int i = 0; i < 20; i++) { //imprimir a matriz dos produtos para gestao do stock
			for (int j = 0; j < 4; j++)
			{
				if (matProdutos[i][0] != "0") {
					cout << matProdutos[i][j] << "\t" << "\t";
				}
			}
			if (matProdutos[i][0] != "0")
				cout << "\n";
		}if (menu) {
			cout << "Pressione enter para voltar.";
			system("pause>nul");
			return menuPrincipal(matVendas, matProdutos, matClientes, countID);
		}
	}
}

void adicionarProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID) { //cria novos clientes na estrutura
	// id do produto, nome do produto, quantidade, custo
	for (int i = 1; i < 20; i++)
	{
		if (matProdutos[i][0] == "0")
		{
			matProdutos[i][0] = to_string(countID[1]);
			cout << "ID do produto: " << matProdutos[i][0] << "\n";
			cout << "\nNome do produto: " << "\n";
			cin >> matProdutos[i][1];
			cout << "\nQuantidade: " << "\n";
			cin >> matProdutos[i][2];
			cout << "\nPreco de custo: " << "\n";
			cin >> matProdutos[i][3];
			matProdutos[i][4] = "0";
			countID[1]++;
			break;
		}
	}
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);

}

void removerProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	imprimirProdutos(matVendas, matProdutos, matClientes, countID, false, false);
	int ID, i, aux = 0;
	for (int i = 1; i < 20; i++) {
		if (stoi(matProdutos[i][0]) > (aux))
		{
			(aux = stoi(matProdutos[i][0]));
		}
	}
	if (aux != 0) {
	marca:
		cout << "Insira o ID do produto a remover: ";
		cin >> ID;
		if (ID > aux || ID <= 0) {
			while (ID > aux || ID <= 0) {
				cout << "Introduza um valor válido correspondente aos IDs dos produtos apresentados: ";
				cin >> ID;
			}
		}
		if (ID <= aux && ID > 0) {
			for (i = 1; i < 20; i++) {
				if (matProdutos[i][0] == to_string(ID))
					break;
				else if (i == 19) {
					cout << "Esse ID já não consta na base de dados. Tente novamente.\n";
					goto marca;
				}
			}
			for (int j = i; j < 20; j++) {
				for (int k = 0; k < 5; k++) {
					if (j < 19)
						matProdutos[j][k] = matProdutos[j + 1][k];
				}
			}
			return menuPrincipal(matVendas, matProdutos, matClientes, countID);
		}
	}
	else
	{
		cout << "\n" << "Não existe nenhum produto para remover do stock." << "\n" << "Precisone Enter para voltar.";
		system("pause>nul");
		return menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

void adicionarStock(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	imprimirProdutos(matVendas, matProdutos, matClientes, countID, false, false);
	int ID, add, aux = 0;
	for (int i = 1; i < 20; i++)
	{
		if (stoi(matProdutos[i][0]) > (aux))
		{
			(aux = stoi(matProdutos[i][0]));
		}
	}	if (aux != 0)
	{
	marca:
		cout << "Insira o ID do produto a adicionar: ";
		cin >> ID;
		if (ID > aux || ID <= 0) {
			while (ID > aux || ID <= 0) {
				cout << "Introduza um valor válido correspondente aos IDs dos produtos apresentados: ";
				cin >> ID;
			}
		}
		if (ID <= aux && ID > 0)
		{
			for (int i = 1; i < 20; i++)
			{
				if (matProdutos[i][0] == to_string(ID)) {
					do {
						cout << "Quantidade a adicionar: " << "\n";
						cin >> add;
						if (add < 1)
							cout << "Nao pode adicionar essa quantidade. Tente novamente.\n";
					} while (add < 1);
					matProdutos[i][2] = to_string(stoi(matProdutos[i][2]) + add);
					break;
				}
				else if (i == 19) {
					cout << "Esse ID já não consta na base de dados. Tente novamente.\n";
					goto marca;
				}
			}
			return menuPrincipal(matVendas, matProdutos, matClientes, countID);
		}
	}
	else
	{
		cout << "\n" << "Não existe nenhum produto para adicionar stock." << "\n" << "É necessário criar primeiro o produto." << "\n" << "Precisone Enter para voltar.";
		system("pause>nul");
		return menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

///////////////////////////////////////////////////////////////////CLIENTES////////////////////////////////////////////////////////////////

void imprimirClientes(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	cout << "\n";
	for (int i = 0; i < 20; i++) { //imprimir a matriz dos clientes
		for (int j = 0; j < 4; j++)
		{
			if (matClientes[i][0] != "0") {
				cout << matClientes[i][j] << "\t" << "\t";
			}
		}
		if (matClientes[i][0] != "0")
			cout << "\n";
	}
	return;
}

void adicionarCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID) { //cria novos clientes na estrutura
	// 0= id do cliente,1= nome,2= númerode telefone,3= morada
	for (int i = 0; i < 20; i++)
	{
		if (matClientes[i][0] == "0")
		{
			matClientes[i][0] = to_string(countID[0]);
			cout << "ID do cliente: " << matClientes[i][0] << "\n";
			cout << "Nome do cliente: " << "\n";
			getline(cin >> ws, matClientes[i][1]);
			cout << "Numero de telefone do cliente: " << "\n";
			cin >> matClientes[i][2];
			cout << "Morada do cliente: " << "\n";
			getline(cin >> ws, matClientes[i][3]); //receber texto da linha inteira: permite armazenar frases
			countID[0]++;
			matClientes[i][4] = "0";
			break;
		}
	}
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);
}

void alterarNomeCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	imprimirClientes(matVendas, matProdutos, matClientes, countID);
	int ID, i, aux = 0;
	string novoNome;
marca:
	cout << "Insira o ID do cliente cujo nome quer alterar: ";
	cin >> ID;
	for (int i = 1; i < 20; i++)
	{
		if (stoi(matClientes[i][0]) > (aux))
		{
			(aux = stoi(matClientes[i][0]));
		}
	}
	if (ID > aux || ID <= 0) {
		while (ID > aux || ID < 0) {
			cout << "Introduza um valor válido correspondente aos IDs apresentados: ";
			cin >> ID;
		}
	}
	if (ID <= aux && ID > 0)
	{
		for (i = 0; i < 20; i++)
		{
			if (matClientes[i][0] == to_string(ID)) {
				cout << "Novo nome do cliente: " << "\n";
				getline(cin >> ws, matClientes[i][1]);
				break;
			}
			else if (i == 19) {
				cout << "Esse ID já não consta na base de dados. Tente novamente.\n";
				goto marca;
			}
		}
		return menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

void removerCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	imprimirClientes(matVendas, matProdutos, matClientes, countID);
	int ID = 0, i, aux = 0;

	for (int i = 1; i < 20; i++)
	{
		if (stoi(matClientes[i][0]) > (aux))
		{
			(aux = stoi(matClientes[i][0]));
		}
	}
	if (aux != 0)
	{
	marca:
		cout << "Insira o ID do cliente a remover: ";
		cin >> ID;
		if (ID > aux || ID <= 0) {
			while (ID > aux || ID < 0) {
				cout << "Introduza um valor válido correspondente aos IDs apresentados: ";
				cin >> ID;
			}
		}
		if (ID <= aux && ID > 0)
		{
			for (i = 0; i < 20; i++)
			{
				if (matClientes[i][0] == to_string(ID))
					break;
				else if (i == 19) {
					cout << "Esse ID já não consta na base de dados. Tente novamente.\n"; //se não encontrar nenhum igual é porque já foi eliminado
					goto marca;
				}
			}
			for (int j = i; j < 20; j++) {
				for (int k = 0; k < 5; k++)
				{
					if (j < 19)
						matClientes[j][k] = matClientes[j + 1][k];
				}
			}
			return menuPrincipal(matVendas, matProdutos, matClientes, countID);
		}
	}
	else
	{
		cout << "\n" << "Não existe nenhum cliente para remover." << "\n" << "Precisone Enter para voltar.";
		system("pause>nul");
		return menuPrincipal(matVendas, matProdutos, matClientes, countID);
	}
}

///////////////////////////////////////////////////////////////////RELATÓRIOS//////////////////////////////////////////////////////////////

void vendasPorCliente(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	int i;
	string nome;
	imprimirClientes(matVendas, matProdutos, matClientes, countID);
	do {
		cout << "Qual o cliente que pretende pesquisar?";
		cin >> nome;
		for (i = 1; i < 20; i++)
		{
			if (matClientes[i][1] == nome)
			{
				cout << "O/A " << matClientes[i][1] << " tem " << matClientes[i][4] << " compras efetuadas.";
				break;
			}
			else if (matClientes[i][1] != nome && i == 19) {
				cout << "Não foi possível encontrar o cliente. Tente novamente.\n";
				break;
			}
		}
	} while (matClientes[i][1] != nome);
	system("pause>nul");
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);
}

void vendasPorProduto(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	int i;
	string prod;
	imprimirProdutos(matVendas, matProdutos, matClientes, countID, false, true);
	do {
		cout << "Qual o produto que pretende pesquisar?";
		cin >> prod;
		for (i = 1; i < 20; i++)
		{
			if (matProdutos[i][1] == prod)
			{
				cout << prod << " tem " << matProdutos[i][4] << " vendas.";
				break;
			}
			else if (matProdutos[i][1] != prod && i == 19)
			{
				cout << "Não foi possível encontrar esse produto, tente novamente.\n";
				break;
			}
		}
	} while (matProdutos[i][1] != prod);
	system("pause>nul");
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);
}

void totalvendas(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	cout << "Total de vendas: " << countID[2] - 1;
	int  numVendido = 0, uniVendidas = 0, maiorNcompras = 0;
	double lucro = 0;

	cout << "\n";
	for (int i = 0; i < 101; i++) { //imprimir a matriz das vendas
		for (int j = 0; j < 4; j++)
		{
			if (i == 0)
				cout << matVendas[i][j] << "\t";
			else if (matVendas[i][0] != "0") {
				cout << matVendas[i][j] << "\t" << "\t";
			}
		}
		if (matVendas[i][0] != "0")
			cout << "\n";
	}
	for (int i = 1; i < 20; i++) {  //procura maior numero de vendas
		if (stoi(matProdutos[i][4]) > numVendido)
		{
			numVendido = stoi(matProdutos[i][4]);
		}
	}
	if (numVendido == 0) {
		cout << "\n" << "Ainda não houve nenhuma venda para obter relatórios.";
	}
	else {
		//mais vendido
		for (int i = 1; i < 20; i++) {
			if (stoi(matProdutos[i][0]) != 0)  //mostra os produtos com o numero de vendas mais alto
			{
				if (stoi(matProdutos[i][4]) == numVendido)
				{
					cout << "\n" << "Produto mais vendido: " << matProdutos[i][1] << " com " << numVendido << " unidades vendidas." << "\n";
				}
			}
			else break;
		}
		// menos vendido
		for (int i = 1; i < 20; i++) {
			if (matProdutos[i][0] != "0") {  //procura o valor de vendas mais baixo
				if (stoi(matProdutos[i][4]) < numVendido)
				{
					numVendido = stoi(matProdutos[i][4]);
				}
			}
			else break;
		}
		for (int i = 1; i < 20; i++) {
			if (stoi(matProdutos[i][0]) != 0)  //mostra os produtos com o numero de vendas mais baixo
			{
				if (stoi(matProdutos[i][4]) == numVendido)
				{
					cout << "\n" << "Produto menos vendido: " << matProdutos[i][1] << " com " << numVendido << " unidades vendidas." << "\n";
				}
			}
			else break;
		}
		// mais lucro
		for (int i = 1; i < 20; i++) {
			if (stod(matProdutos[i][3]) * stod(matProdutos[i][4]) > lucro)
			{
				uniVendidas = stoi(matProdutos[i][4]);
				lucro = stod(matProdutos[i][3]) * 0.30 * stod(matProdutos[i][4]);  //calcula os 30% de cada produto e multiplica pelo numero de vendas 
			}
		}
		for (int i = 1; i < 20; i++) {
			if (stoi(matProdutos[i][0]) != 0)  //mostra os produtos com mais lucro
			{
				if (stod(matProdutos[i][3]) *0.3 * stod(matProdutos[i][4]) == lucro)
				{
					cout << "\n" << "Produto com mais lucro: " << matProdutos[i][1] << " em " << uniVendidas << " unidades vendidas, com " << lucro << " de lucro." << "\n";
				}
			}
			else break;
		}
		//cliente com mais vendas
		for (int i = 1; i < 20; i++)
		{
			if (stoi(matClientes[i][4]) > maiorNcompras)	 //procura cliente que comprou mais produtos
			{
				maiorNcompras = stoi(matClientes[i][4]);
			}
		}
		for (int i = 1; i < 20; i++) {
			if (stoi(matClientes[i][0]) != 0)  //mostra os clientes que compraram mais produtos
			{
				if (stoi(matClientes[i][4]) == maiorNcompras)
				{
					cout << "\n" << "Cliente que mais comprou: " << matClientes[i][1] << " com " << maiorNcompras << " artigos comprados no total.";
				}
			}
			else break;
		}
	}
	system("pause>nul");
	return menuPrincipal(matVendas, matProdutos, matClientes, countID);
}

//////////////////////////////////////////////////////////////CRIAR MATRIZES///////////////////////////////////////////////////////////////

string** criarMatProdutos() {
	string** matProdutos = new string * [20]; //criar a matriz Produtos
	for (int i = 0; i < 20; i++)
	{
		matProdutos[i] = new string[5];
	}
	matProdutos[0][0] = "ID";
	matProdutos[0][1] = "Produto";
	matProdutos[0][2] = "Stock";
	matProdutos[0][3] = "Custo";
	matProdutos[0][4] = "Vendas";
	for (int i = 1; i < 20; i++) { //igualar matriz a zero
		for (int j = 0; j < 5; j++)
		{
			matProdutos[i][j] = "0";
		}
	}
	return matProdutos;
}

string** criarMatClientes() {
	string** matClientes = new string * [20]; //criar a matriz Clientes
	for (int i = 0; i < 20; i++)
	{
		matClientes[i] = new string[5];
	}
	matClientes[0][0] = "ID";
	matClientes[0][1] = "Nome";
	matClientes[0][2] = "Telefone";
	matClientes[0][3] = "Morada";
	matClientes[0][4] = "Compras";
	for (int i = 1; i < 20; i++) { //igualar matriz a zero
		for (int j = 0; j < 5; j++)
		{
			matClientes[i][j] = "0";
		}
	}
	return matClientes;
}

string** criarMatVendas() {
	string** matVendas = new string * [101]; //criar a matriz para as vendas
	for (int i = 0; i < 101; i++)
	{
		matVendas[i] = new string[4];
	}
	matVendas[0][0] = "ID Venda";
	matVendas[0][1] = "ID Cliente";
	matVendas[0][2] = "Total";
	matVendas[0][3] = "Data";
	for (int i = 1; i < 101; i++) { //igualar matriz a zero
		for (int j = 0; j < 4; j++)
		{
			matVendas[i][j] = "0";
		}
	}
	return matVendas;
}

/////////////////////////////////////////////////////////INTRODUZIR VALORES DEFAULT////////////////////////////////////////////////////////

void defaultVendas(string** matVendas, string** matProdutos, string** matClientes, int* countID, int i, int j, int qnt, string valorTotal, string data) {
	//adiciona valores default na estrutura das vendas
	//id da venda, id do cliente, valor total, data

	matVendas[countID[2]][0] = to_string(countID[2]);
	matVendas[countID[2]][1] = matClientes[i][0];
	matVendas[countID[2]][2] = valorTotal;
	matVendas[countID[2]][3] = data;
	countID[2]++;
	matClientes[i][4] = to_string(stoi(matClientes[i][4]) + qnt); //adicionar produtos comprados ao cliente
	matProdutos[j][2] = to_string(stoi(matProdutos[j][2]) - qnt); //retirar produtos comprados do stock
	matProdutos[j][4] = to_string(stoi(matProdutos[j][4]) + qnt); //adicionar vendas aos produtos
	return;
}

void defaultCliente(int* countID, string nome, string telefone, string morada, string** matClientes) { //adiciona valores default na estrutura dos clientes
	// id do cliente, nome, númerode telefone, morada

	matClientes[countID[0]][0] = to_string(countID[0]);
	matClientes[countID[0]][1] = nome;
	matClientes[countID[0]][2] = telefone;
	matClientes[countID[0]][3] = morada;
	matClientes[countID[0]][4] = "0";
	countID[0]++;
	return;
}

void defaultProduto(int* countID, string nome, string quantidade, string custo, string** matProdutos) { //adiciona valores default na estrutura dos produtos
	// id do cliente, nome, númerode telefone, custo

	matProdutos[countID[1]][0] = to_string(countID[1]);
	matProdutos[countID[1]][1] = nome;
	matProdutos[countID[1]][2] = quantidade;
	matProdutos[countID[1]][3] = custo;
	matProdutos[countID[1]][4] = "0";
	countID[1]++;
	return;
}

///////////////////////////////////////////////////////////////////MENUS///////////////////////////////////////////////////////////////////

void menuPrincipal(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	system("cls");
	int menu = 0, x = 7, cnt1 = 14, cnt2 = 14;
	bool ligado = true;
	for (int col = 1; col <= 38; col++) {
		gotoXY(cnt1, 3); cout << "*";
		cnt1 = cnt1 + 1;
		gotoXY(cnt2, 13); cout << "*";
		cnt2 = cnt2 + 1;
	}
	int cnt3 = 3, cnt4 = 3;
	for (int col = 1; col <= 11; col++) {
		gotoXY(14, cnt3); cout << "*";
		cnt3 = cnt3 + 1;
		gotoXY(52, cnt4); cout << "*";
		cnt4 = cnt4 + 1;
	}
	SetConsoleTextAttribute(h, BACKGROUND_BLUE);
	gotoXY(20, 5); cout << "------Menu Principal------";
	SetConsoleTextAttribute(h, 15);
	gotoXY(18, 7); cout << "->";

	while (ligado)
	{
		gotoXY(20, 7);  cout << "1) Efetuar venda";
		gotoXY(20, 8);  cout << "2) Gestão de Stock";
		gotoXY(20, 9);  cout << "3) Relatórios";
		gotoXY(20, 10); cout << "4) Gestão de clientes";
		gotoXY(20, 11); cout << "Sair";
		system("pause>nul"); // comando para fazer pausa no programa até que seja escolhida alguma opção

		if (GetAsyncKeyState(VK_DOWN) && x != 11) //seta para baixo
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu++;
			continue;
		}
		if (GetAsyncKeyState(VK_UP) && x != 7) //seta para cima
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // enter
			switch (menu) {

			case 0: {
				system("cls");
				return vendas(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 1: {
				system("cls");
				return menuStock(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 2: {
				system("cls");
				return menuRelatorios(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 3: {
				system("cls");
				return menuClientes(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 4: {
				system("cls");
				int cnt1 = 15, cnt2 = 15;
				for (int col = 1; col <= 34; col++) {
					gotoXY(cnt1, 6); cout << "*";
					cnt1 = cnt1 + 1;
					gotoXY(cnt2, 10); cout << "*";
					cnt2 = cnt2 + 1;
				}
				int cnt3 = 6, cnt4 = 6;
				for (int col = 1; col <= 5; col++) {
					gotoXY(15, cnt3); cout << "*";
					cnt3 = cnt3 + 1;
					gotoXY(48, cnt4); cout << "*";
					cnt4 = cnt4 + 1;
				}
				gotoXY(20, 8);
				cout << "O programa foi terminado";
				ligado = false;
			}
			}
		}
	}
	gotoXY(20, 18);
}

void menuClientes(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	system("cls");
	int menu1 = 0, x1 = 7, cnt1 = 14, cnt2 = 14;
	bool ligado1 = true;
	for (int col = 1; col <= 39; col++) {
		gotoXY(cnt1, 3); cout << "*";
		cnt1 = cnt1 + 1;
		gotoXY(cnt2, 13); cout << "*";
		cnt2 = cnt2 + 1;
	}
	int cnt3 = 3, cnt4 = 3;
	for (int col = 1; col <= 11; col++) {
		gotoXY(14, cnt3); cout << "*";
		cnt3 = cnt3 + 1;
		gotoXY(53, cnt4); cout << "*";
		cnt4 = cnt4 + 1;
	}
	SetConsoleTextAttribute(h, BACKGROUND_INTENSITY);
	gotoXY(20, 5); cout << "------Menu de clientes------";
	SetConsoleTextAttribute(h, 15);
	gotoXY(18, 7); cout << "->";

	while (ligado1 = true)
	{
		gotoXY(20, 7); cout << "1- Criar cliente";
		gotoXY(20, 8); cout << "2- Eliminar cliente";
		gotoXY(20, 9); cout << "3- Alterar nome do cliente";
		gotoXY(20, 10); cout << "Voltar";
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x1 != 10) //seta para baixo
		{
			gotoXY(18, x1); cout << "  ";
			x1++;
			gotoXY(18, x1); cout << "->";
			menu1++;
			continue;
		}
		if (GetAsyncKeyState(VK_UP) && x1 != 7) //seta para cima
		{
			gotoXY(18, x1); cout << "  ";
			x1--;
			gotoXY(18, x1); cout << "->";
			menu1--;
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN)) { // enter
			switch (menu1)
			{
			case 0: {
				system("cls");
				return adicionarCliente(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 1: {
				system("cls");
				return removerCliente(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 2: {
				system("cls");
				return alterarNomeCliente(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 3: {
				system("cls");
				return menuPrincipal(matVendas, matProdutos, matClientes, countID);
				ligado1 = false;
			}
			}
		}
	}
	return;
}

void menuRelatorios(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	system("cls");
	int menu2 = 0, x2 = 7, cnt1 = 14, cnt2 = 14;
	bool ligado2 = true;
	for (int col = 1; col <= 42; col++) {
		gotoXY(cnt1, 3); cout << "*";
		cnt1 = cnt1 + 1;
		gotoXY(cnt2, 13); cout << "*";
		cnt2 = cnt2 + 1;
	}
	int cnt3 = 3, cnt4 = 3;
	for (int col = 1; col <= 11; col++) {
		gotoXY(14, cnt3); cout << "*";
		cnt3 = cnt3 + 1;
		gotoXY(55, cnt4); cout << "*";
		cnt4 = cnt4 + 1;
	}
	SetConsoleTextAttribute(h, BACKGROUND_GREEN);
	gotoXY(20, 5); cout << "------Menu de Relatórios------";
	SetConsoleTextAttribute(h, 15);
	gotoXY(18, 7); cout << "->";

	while (ligado2 = true)
	{
		gotoXY(20, 7); cout << "1- Stock Total";
		gotoXY(20, 8); cout << "2- Vendas por produto";
		gotoXY(20, 9); cout << "3- Vendas por cliente";
		gotoXY(20, 10); cout << "4- Total de vendas";
		gotoXY(20, 11); cout << "Voltar";
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x2 != 11) //seta para baixo
		{
			gotoXY(18, x2); cout << "  ";
			x2++;
			gotoXY(18, x2); cout << "->";
			menu2++;
			continue;
		}
		if (GetAsyncKeyState(VK_UP) && x2 != 7) //seta para cima
		{
			gotoXY(18, x2); cout << "  ";
			x2--;
			gotoXY(18, x2); cout << "->";
			menu2--;
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN)) { // enter
			switch (menu2)
			{
			case 0: {
				system("cls");
				bool flag = true;
				return imprimirProdutos(matVendas, matProdutos, matClientes, countID, flag, false);
				break;
			}
			case 1: {
				system("cls");
				return vendasPorProduto(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 2: {
				system("cls");
				cout << "teste";
				return vendasPorCliente(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 3: {
				system("cls");
				return totalvendas(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 4: {
				system("cls");
				return menuPrincipal(matVendas, matProdutos, matClientes, countID);
				ligado2 = false;
			}
			}
		}
	}
	return;
}

void menuStock(string** matVendas, string** matProdutos, string** matClientes, int* countID) {
	system("cls");
	int menu3 = 0, x3 = 7, cnt1 = 14, cnt2 = 14;
	bool ligado3 = true;
	for (int col = 1; col <= 54; col++) {
		gotoXY(cnt1, 3); cout << "*";
		cnt1 = cnt1 + 1;
		gotoXY(cnt2, 13); cout << "*";
		cnt2 = cnt2 + 1;
	}
	int cnt3 = 3, cnt4 = 3;
	for (int col = 1; col <= 11; col++) {
		gotoXY(14, cnt3); cout << "*";
		cnt3 = cnt3 + 1;
		gotoXY(67, cnt4); cout << "*";
		cnt4 = cnt4 + 1;
	}
	SetConsoleTextAttribute(h, BACKGROUND_RED);
	gotoXY(20, 5); cout << "------Menu de Gerenciamento de Stock------";
	SetConsoleTextAttribute(h, 15);
	gotoXY(18, 7); cout << "->";

	while (ligado3 = true)
	{
		gotoXY(20, 7); cout << "1- Criar artigo";
		gotoXY(20, 8); cout << "2- Adicionar stock ao artigo";
		gotoXY(20, 9); cout << "3- Eliminar produto";
		gotoXY(20, 10); cout << "Voltar";
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x3 != 10) //seta para baixo
		{
			gotoXY(18, x3); cout << "  ";
			x3++;
			gotoXY(18, x3); cout << "->";
			menu3++;
			continue;
		}
		if (GetAsyncKeyState(VK_UP) && x3 != 7) //seta para cima
		{
			gotoXY(18, x3); cout << "  ";
			x3--;
			gotoXY(18, x3); cout << "->";
			menu3--;
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN)) { // enter
			switch (menu3)
			{
			case 0: {
				system("cls");
				return adicionarProduto(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 1: {
				system("cls");
				return adicionarStock(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 2: {
				system("cls");
				return removerProduto(matVendas, matProdutos, matClientes, countID);
				break;
			}
			case 3: {
				system("cls");
				return menuPrincipal(matVendas, matProdutos, matClientes, countID);
				ligado3 = false;
			}
			}
		}
	}
	return;
}

///////////////////////////////////////////////////////////////////GERAIS//////////////////////////////////////////////////////////////////

void gotoXY(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(h, CursorPosition);
	return;
}

int* contadoresID() {
	int* countID = new int[3]; //[0]=ID Cliente, [1]= ID Stock, [2]=ID Venda
	for (int i = 0; i < 3; i++)
	{
		countID[i] = 1;
	}
	return countID;
}

///////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////

int main() {
	string** matClientes = criarMatClientes();
	string** matProdutos = criarMatProdutos();
	string** matVendas = criarMatVendas();
	int* countID = contadoresID(); //[0]=ID Cliente, [1]= ID Stock, [2]=ID Venda
	defaultCliente(countID, "Carlos", "919031747", "Rua Godinho de Faria, 915", matClientes);
	defaultCliente(countID, "Eduardo", "919056987", "Algures em Santa Maria da Feira", matClientes);
	defaultCliente(countID, "Joao", "919098765", "Rua de Tras, 815", matClientes);
	defaultCliente(countID, "Lucio", "919032697", "Rua Mesmo ao Lado da Outra, 594", matClientes);
	defaultProduto(countID, "Fruta", "25", "2,59", matProdutos);
	defaultProduto(countID, "Leite", "32", "1,35", matProdutos);
	defaultProduto(countID, "Legumes", "17", "2,05", matProdutos);
	defaultProduto(countID, "Carne", "12", "4,5", matProdutos);
	defaultVendas(matVendas, matProdutos, matClientes, countID, 1, 2, 3, "3.73", "Thu Dec 22 17:25:51 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 3, 1, 3, "12.42", "Fri Dec 23 10:53:35 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 2, 3, 4, "13.11", "Fri Dec 23 19:15:15 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 1, 2, 3, "6.48", "Mon Dec 26 12:12:26 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 4, 1, 2, "3.73", "Mon Dec 26 15:38:27 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 2, 3, 3, "3.73", "Tue Dec 27 09:46:54 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 3, 4, 2, "3.73", "Tue Dec 27 14:58:08 2022");
	defaultVendas(matVendas, matProdutos, matClientes, countID, 2, 4, 3, "3.73", "Tue Dec 27 17:01:11 2022");
	setlocale(LC_ALL, "portuguese");
	cout << setprecision(2) << fixed; //setprecision imprime pelo menos (2) casas decimais, fixed limita a (2).
	menuPrincipal(matVendas, matProdutos, matClientes, countID);
}