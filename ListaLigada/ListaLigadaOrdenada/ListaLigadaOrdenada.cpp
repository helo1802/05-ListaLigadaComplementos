#include <cstdlib>
#include <iostream>
#include <type_traits>
using namespace std;

struct NO {
	int valor;
	NO* prox;
};

NO* primeiroElemento = NULL;
NO* ultimoElemento = NULL;

// headers
void menu();
void inicializar();
void mostrarTamanho();
void mostrarElemento();
void inserirElemento();
void removerElemento();
void procurarElemento();
NO* posicaoElemento(int numero);
//--------------------------

int main(){
	menu();
}

void menu() {
	int op = 0;
	while (op != 7) {
		system("cls"); // somente no windows

		cout << "Menu Lista Ligada";
		cout << endl << endl;
		cout << "1 - Inicializar Lista \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Exibir elementos \n";
		cout << "4 - Buscar elemento \n";
		cout << "5 - Inserir elemento \n";
		cout << "6 - Excluir elemento \n";
		cout << "7 - Sair \n\n";

		cout << "Opcao: ";
		cin >> op;

		switch (op) {
		case 1: inicializar();
			break;
		case 2: mostrarTamanho();
			break;
		case 3: mostrarElemento();
			break;
		case 4: procurarElemento();
			break;
		case 5: inserirElemento();
			break;
		case 6: removerElemento();
			break;

		case 7:
			return;
		default:
			break;
		}

		system("pause"); // somente no windows
	}
}

void inicializar() {
	// se a lista j� possuir elementos
	// libera a memoria ocupada
	NO* aux = primeiroElemento;
	while (aux != NULL) {
		NO* paraExcluir = aux;
		aux = aux->prox;
		free(paraExcluir);
	}

	primeiroElemento = NULL;
	cout << "Lista inicializada \n";
}

void mostrarTamanho() {
	int nElementos = 0;
	NO* aux = primeiroElemento;

	while (aux != NULL) {
		nElementos++;
		aux = aux->prox;
	}
	cout << "Quantidade de elementos: " << nElementos << endl;
}

void mostrarElemento() {
	if (primeiroElemento == NULL) {
		cout << "Lista vazia \n";
		return;
	} else {
		cout << "Elementos: \n";
		NO* aux = primeiroElemento;
		while (aux != NULL) {
			cout << aux->valor << endl;
			aux = aux->prox;
		}
	}
}

void inserirElemento() {
	// aloca memoria dinamicamente para o novo elemento
	NO* novoElemento = (NO*)malloc(sizeof(NO));
	if (novoElemento == NULL) {
		return;
	}

	cout << "Digite o elemento: ";
	cin >> novoElemento->valor;
	novoElemento->prox = NULL;

	NO* existente = posicaoElemento(novoElemento->valor);

	if(existente) {
		cout << "Elemento já existe na lista, tente outro.";
		return;
	}

	if (primeiroElemento == NULL) {
		primeiroElemento = novoElemento;
		ultimoElemento = novoElemento;
	} else {
		ultimoElemento->prox = novoElemento;
		ultimoElemento = novoElemento;


		bool trocado = true;

		while(trocado) {
			NO* atual = primeiroElemento;

			trocado = false;

			while(atual->prox != NULL) {
				NO* proximoElemento = atual->prox;

				if(atual->valor > proximoElemento->valor) {
					int troca = atual->valor;

					atual->valor = proximoElemento->valor;
					proximoElemento->valor = troca;

					trocado = true;
					continue;
				}
				atual = atual->prox;
			}
		}
	}
}

void removerElemento() {
	int valorDigitado;
	cout << "Digite o valor que quer excluir: ";
	cin >> valorDigitado;

	NO* aux = primeiroElemento;

	while (aux->prox != NULL) {
		NO* proximoElemento = aux->prox;
 
		if (primeiroElemento->valor == valorDigitado) {
			free(primeiroElemento);
			primeiroElemento = proximoElemento;
			break;
		}

		if (proximoElemento->valor == valorDigitado) {
			aux->prox = proximoElemento->prox;

			free(proximoElemento);
			break;
		}
		aux = aux->prox;
	}
}

void procurarElemento() {
	int valorDigitado;
	cout << "Digite o valor que quer excluir: ";
	cin >> valorDigitado;

	NO* elemento = posicaoElemento(valorDigitado);

	if(elemento == NULL) {
		cout << "Nenhum elemento foi encontrado com esse valor.";
		return;
	}

	cout << elemento->valor;
}

NO* posicaoElemento(int valor) {
	NO* atual = primeiroElemento;

	while (atual != NULL) {
		if (atual->valor == valor) {
			break;
		}
		atual = atual->prox;
	}

	return atual;
}