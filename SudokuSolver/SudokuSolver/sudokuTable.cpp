#include <stdlib.h>
#include "util.cpp"

#include <iostream>
using namespace std;

struct Sudoku
{
	int matriz[9][9] = { //table - 1
		{0, 0, 0, 3, 1, 0, 0, 2, 0},
		{4, 0, 0, 0, 8, 0, 0, 1, 0},
		{9, 0, 7, 4, 0, 2, 3, 8, 0},
		{0, 8, 0, 6, 0, 7, 9, 0, 0},
		{0, 0, 6, 0, 0, 0, 0, 0, 0},
		{0, 4, 3, 0, 0, 0, 0, 5, 2},
		{8, 6, 5, 0, 0, 4, 2, 3, 0},
		{0, 7, 0, 2, 0, 1, 8, 9, 5},
		{1, 2, 0, 0, 3, 5, 0, 0, 7}
	};
};

struct ConjuntoDeCandidatos {
	int quantidade = 9; //A box iniciara com os 9 candidatos
	int cadidato[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //cada box ter� inicialmente todos os candidatos
};

struct TabelaSudoku {
	ConjuntoDeCandidatos boxes[9][9];
};

struct ContadorDeNumeros {
	int numero;
	int quantidade;
	int posX;
	int posY;
};


void imprimirMatriz(Sudoku* tabela);
void zerarContador(ContadorDeNumeros* contador);
void imprimirTabelaBoxes(TabelaSudoku* tabela);
bool setValorNaBox(ConjuntoDeCandidatos* box, int valor);
bool setValorNaTabela(TabelaSudoku* tabela, int posY, int posX, int valor);
bool candidatoSozinho(TabelaSudoku* tabela);
TabelaSudoku gerarTabelaSudoku(Sudoku* tab);
ContadorDeNumeros verificarNumeroSozinho(TabelaSudoku* tabela, ContadorDeNumeros contador[9]);



/*
struct TabelaDeEntrada
{
	int matriz[9][9] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 9, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
};
*/


void imprimirMatriz(Sudoku* tabela) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (tabela->matriz[i][j] != 0)
				cout << tabela->matriz[i][j];
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl; 
	cout << endl;
}



/*----------------------------------------------------------------*/


TabelaSudoku gerarTabelaSudoku(Sudoku* tab) {

	TabelaSudoku tabela = TabelaSudoku();


	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			if (tab->matriz[i][j] != 0) {
				setValorNaTabela(&tabela, i, j, tab->matriz[i][j]);
			}
		}
	}
	return tabela;
}

bool setValorNaBox(ConjuntoDeCandidatos* box, int valor) {
	//verifica se o valor recebido est� entre 1 e 9
	if (valor < 1 || valor > 9)
		return false;

	for (int i = 0; i < box->quantidade; i++) {
		if (box->cadidato[i] == valor) {
			box->cadidato[0] = valor;
			(box->quantidade) = 1;
			//quando encontrar o valor, move o valor pra posi��o 0 e seta a quantidade como 1
			return true;
		}
	}
	return false;
	//caso n�o encontre o valor na box, retorna false
}

int apagarValorNaBox(ConjuntoDeCandidatos* box, int valor) {
	//verifica se o valor recebido est� entre 1 e 9
	if (valor < 1 || valor > 9)
		return 0;
	for (int k = 0; k < box->quantidade; k++) {
		if (box->cadidato[k] == valor) {
			for (int k2 = k; k2 < box->quantidade - 1; k2++) {
				box->cadidato[k2] = box->cadidato[(k2 + 1)];
			}
			box->quantidade--;
			if (box->quantidade == 0) {
				//caso uma casa fique sem senhum candidato poss�vel, encerra a aplica��o
				return -1;
			}
			return 1;
			//quando encontrar o valor, move o valor pra posi��o 0 e seta a quantidade como 1 e retorna true
		}
	}
	return 0;
};

bool setValorNaTabela(TabelaSudoku* tabela, int posY, int posX, int valor) {
	//verifica se a posi��o � v�lida
	if (posX < 0 || posX > 8 || posY < 0 || posY > 8) {
		return false;
	}
	ConjuntoDeCandidatos* box = &(tabela->boxes[posY][posX]);

	if (setValorNaBox(box, valor)) {
		//se conseguiu setar o valor na box, percorre a linha coluna e quad apagando o valor

		//percorre a linha
		for (int i = 0; i < 9; i++) {
			if (i != posX) { //como o for percorrer� TODA a linha, incluindo a box que acabou de ser setada, deve-se verificar se a coluna � diferente da do numeor setado
				ConjuntoDeCandidatos* boxAux = &(tabela->boxes[posY][i]); //pega cada coluna da linha
				apagarValorNaBox(boxAux, valor);
			}
		}

		//percorre a coluna
		for (int i = 0; i < 9; i++) {
			if (i != posY) { //como o for percorrer� TODA a coluna, incluindo a box que acabou de ser setada, deve-se verificar se a coluna � diferente da do numeor setado
				ConjuntoDeCandidatos* boxAux = &(tabela->boxes[i][posX]);
				apagarValorNaBox(boxAux, valor);
			}
		}

		//percorre o quadrado

		int inicioX = getInicioQuadrado(posX);
		int inicioY = getInicioQuadrado(posY);

		for (int y = inicioY; y < inicioY + 3; y++) {
			for (int x = inicioX; x < inicioX + 3; x++) {
				if (!(y == posY && x == posX)) { //se a posi��o percorrida for diferente da box do valor setado
					ConjuntoDeCandidatos* boxAux = &(tabela->boxes[y][x]);
					apagarValorNaBox(boxAux, valor);
				}
			}
		}
		return true;
	}
	return false;
}

/*----------------------------------------------------------------*/

/* TECNICAS DE RESOLU��O*/

//candidato sozinho//


ContadorDeNumeros verificarNumeroSozinho(TabelaSudoku* tabela, ContadorDeNumeros contador[9]) {

	ContadorDeNumeros aux;
	aux.quantidade = -1;

	//verifica se h� algum candidato sozinho na linha
	for (int k = 0; k < 9; k++) {
		if (contador[k].quantidade == 1) {
			ConjuntoDeCandidatos boxAux = tabela->boxes[contador[k].posY][contador[k].posX]; //recebe a box que contem o candidato unico
			if (boxAux.quantidade > 1) { //se o numero ainda n�o foi setado, define ele

				return contador[k];
			}
		}
	}
	return aux;
}
void zerarContador(ContadorDeNumeros* contador) {
	contador->posX = -1;
	contador->posY = -1;
	contador->quantidade = 0;
}

void imprimirContadorVet(ContadorDeNumeros contador[9]) {
	for (int i = 0; i < 9; i++) {
		cout << "numero " << contador[i].numero << " quantidade: " << contador[i].quantidade << endl;
	}
}

bool candidatoSozinho(TabelaSudoku* tabela) {
	ContadorDeNumeros contador[9];

	for (int i = 0; i < 9; i++) {
		contador[i] = ContadorDeNumeros();
		zerarContador(&contador[i]);
		contador[i].numero = i + 1;
	}

	//INICIO CONTAGEM LINHAS
	for (int i = 0; i < 9; i++) { //percorre a tabela 9x9
		//INICIO zera contador
		for (int f = 0; f < 9; f++) {
			zerarContador(&contador[f]);
		}
		//FIM zera contador

		for (int j = 0; j < 9; j++) { //percorre a tabela 9x9 - colunas

			ConjuntoDeCandidatos* box = &(tabela->boxes[i][j]);  //recebe cada box

			for (int k = 0; k < box->quantidade; k++) { //percorre os valores da box e adiciona ao contador
				int valor = box->cadidato[k];
				int pos = valor - 1;
				contador[pos].posX = j; //recebe a ultima coluna adicionada no valor candidato encontrado, caso sobre somente um, teremos a posi��o o unico candidato da linha
				contador[pos].posY = i; //evitar inconsistencia de dados 
				contador[pos].quantidade++; //a posi��o 0 guarda o valor 1 e adiante, ent�o � necess�rio diminuir 1 do valor encontrado
			}
		}
		//ap�s terminar a contagem dos itens da linha
		ContadorDeNumeros contAux = verificarNumeroSozinho(tabela, contador);
		if (contAux.quantidade == 1) { //se o contador retorno tiver quantidade 1, seta o valor
			//cout << "Valor encontrado sozinho: " << contAux.numero << " na posicao [" << contAux.posY << "][" << contAux.posX << "] - LINHA" << endl;
			setValorNaTabela(tabela, contAux.posY, contAux.posX, contAux.numero);
			return true;
		};
	}
	//FIM CONTAGEM LINHAS
	
	//INICIO CONTAGEM COLUNAS
	for (int j = 0; j < 9; j++) { //percorre a tabela 9x9
		//INICIO zera contador
		for (int f = 0; f < 9; f++) {
			zerarContador(&contador[f]);
		}
		//FIM zera contador

		for (int i = 0; i < 9; i++) { //percorre a tabela 9x9 - colunas

			ConjuntoDeCandidatos* box = &(tabela->boxes[i][j]);  //recebe cada box

			for (int k = 0; k < box->quantidade; k++) { //percorre os valores da box e adiciona ao contador
				int valor = box->cadidato[k];
				int pos = valor - 1;
				contador[pos].posX = j; //recebe a ultima coluna adicionada no valor candidato encontrado, caso sobre somente um, teremos a posi��o o unico candidato da linha
				contador[pos].posY = i; //evitar inconsistencia de dados 
				contador[pos].quantidade++; //a posi��o 0 guarda o valor 1 e adiante, ent�o � necess�rio diminuir 1 do valor encontrado
			}
		}
		//ap�s terminar a contagem dos itens da linha
		ContadorDeNumeros contAux = verificarNumeroSozinho(tabela, contador);
		if (contAux.quantidade == 1) { //se o contador retorno tiver quantidade 1, seta o valor
			//cout << "Valor encontrado sozinho: " << contAux.numero << " na posicao [" << contAux.posY << "][" << contAux.posX << "] - LINHA" << endl;
			setValorNaTabela(tabela, contAux.posY, contAux.posX, contAux.numero);
			return true;
		};
	}
	//FIM CONTAGEM COLUNAS

	//conta os numeros em cada quadrado
	for (int quadIniY = 0; quadIniY < 9; quadIniY += 3) {
		for (int quadIniX = 0; quadIniX < 9; quadIniX += 3) {
			
			//No inicio de cada quadrado, reseta o contador
			for (int f = 0; f < 9; f++) {
				contador[f].quantidade = 0; // inicia/reseta o contador em cada linha
			}
			//percorre o quadrado
			for (int y = quadIniY; y < quadIniY + 3; y++) {
				for (int x = quadIniX; x < quadIniX + 3; x++) {
					ConjuntoDeCandidatos* box = &(tabela->boxes[y][x]);

					for (int k = 0; k < box->quantidade; k++) { //percorre os valores da box e adiciona ao contador
						int valor = box->cadidato[k];
						contador[(valor - 1)].posX = x; //recebe a ultima coluna adicionada no valor candidato encontrado, caso sobre somente um, teremos a posi��o o unico candidato da linha
						contador[(valor - 1)].posY = y; //evitar inconsistencia de dados 
						contador[(valor - 1)].quantidade++; //a posi��o 0 guarda o valor 1 e adiante, ent�o � necess�rio diminuir 1 do valor encontrado
					}
				}
			}

			//verifica se h� algum candidato sozinho na linha
			ContadorDeNumeros contAux = verificarNumeroSozinho(tabela, contador);
			if (contAux.quantidade == 1) { //se o contador retorno tiver quantidade 1, seta o valor		
				setValorNaTabela(tabela, contAux.posY, contAux.posX, contAux.numero);
				//cout << "Valor encontrado sozinho: " << contAux.numero << " na posicao [" << contAux.posY << "][" << contAux.posX << "] - Quadrado " << getInicioQuadrado(contAux.posY) <<"x"<< getInicioQuadrado(contAux.posX) <<endl;
				return true;
			};
		}
	}
	return false;
}

void imprimirTabelaBoxes(TabelaSudoku* tabela) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
		{
			cout << "Boxes[" << i << "][" << j << "]: ";
			for (int k = 0; k < tabela->boxes[i][j].quantidade; k++)
			{
				cout << tabela->boxes[i][j].cadidato[k] << " ";
			}
			cout << endl;
		}
	}
}
void zerarVetor9(int vetor[9]) {
	for (int i = 0; i < 9; i++)
		vetor[i] = 0;

}


int verificarLinhaCompleta(Sudoku* sudoku, int linha) {

	int contador[9] = { 0,0,0,0,0,0,0,0,0 };

	for (int j = 0; j < 9; j++) {

		if (sudoku->matriz[linha][j] == 0) {
			continue;
		}

		int pos = sudoku->matriz[linha][j] - 1;

		if (contador[pos] == 0) {
			contador[pos]++;
		}
		else if (contador[pos] == 1) { //se for a segunda ocorrencia do numero, returna -1 = numero repetido
			return -1;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (contador[i] == 0) {
			return 0;
		}
	}

	return 1;
}

int verificarColunaCompleta(Sudoku* sudoku, int coluna) {

	int contador[9] = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 9; i++) {

		if (sudoku->matriz[i][coluna] == 0) {
			continue;
		}

		int pos = sudoku->matriz[i][coluna] - 1;

		if (contador[pos] == 0) {
			contador[pos]++;
		}
		else if (contador[pos] == 1) { //se for a segunda ocorrencia do numero, returna -1 = numero repetido
			return -1;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (contador[i] == 0) {
			return 0;
		}
	}

	return 1;
}

//-----------------------CONTINUAR DAQUI-----------------------------------------//
struct Posicao {
	int x;
	int y;
};

Posicao getPosInicialQuadrado(int numDoQuad) {
	
	if (numDoQuad < 0 || numDoQuad > 8) {
		return ;
	}




}



int verificarQuadCompleto(Sudoku* sudoku, int coluna) {

	int contador[9] = { 0,0,0,0,0,0,0,0,0 };
	
	

	for (int i = 0; i < 9; i++) {
		if (contador[i] == 0) {
			return 0;
		}
	}

	return 1;
}
//-----------------------CONTINUAR DAQUI-----------------------------------------//



int verificarMapaCompleto(Sudoku* sudoku) {
	
	for (int i = 0; i < 9; i++) { //contando os valores relacionados a linha
		
		int resultLinha = verificarLinhaCompleta(sudoku, i);
		int resultColuna = verificarColunaCompleta(sudoku, i);

		if (resultLinha == -1) {
			cout << "Linha " << i << " com valor repetido" << endl;
			return -1;
		}
		else if (resultLinha == 1) {
			cout << "Linha " << i << " completa " << endl;
		}

		if (resultColuna == -1) {
			cout << "Coluna " << i << " com valor repetido" << endl;
			return -1;
		}
		else if (resultColuna == 1) {
			cout << "Coluna " << i << " completa " << endl;
		}

	}

}
