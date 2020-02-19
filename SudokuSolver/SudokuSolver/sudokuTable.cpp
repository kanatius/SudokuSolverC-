#include "util.cpp"
#include <stdlib.h>


struct TabelaDeEntrada
{
	int matriz[9][9] = { 
		{0, 0, 0, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
};



/*----------------------------------------------------------------*/
struct ConjuntoDeCandidatos {
	int quantidade = 9; //A box iniciara com os 9 candidatos
	int cadidato[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9 }; //cada box terá inicialmente todos os candidatos
};

struct TabelaSudoku {
	ConjuntoDeCandidatos boxes[9][9];
};
bool setValorNaBox(ConjuntoDeCandidatos* box, int valor) {
	//verifica se o valor recebido está entre 1 e 9
	if (valor < 1 || valor > 9)
		return false;

	for (int i = 0; i < box->quantidade; i++) {
		if (box->cadidato[i] == valor) {
			box->cadidato[0] = valor;
			(box->quantidade) = 1;
			//quando encontrar o valor, move o valor pra posição 0 e seta a quantidade como 1
			return true;
		}
	}
	return false;
	//caso não encontre o valor na box, retorna false
}

bool apagarValorNaBox(ConjuntoDeCandidatos* box, int valor){
	//verifica se o valor recebido está entre 1 e 9
	if (valor < 1 || valor > 9)
		return false;

	for (int k = 0; k < box->quantidade; k++) {
		if (box->cadidato[k] == valor) {
			for (int k2 = k; k2 < box->quantidade - 1; k2++) {
				box->cadidato[k2] = box->cadidato[(k2 + 1)];
			}
			box->quantidade--;
			if (box->quantidade == 0) {
				//caso uma casa fique sem senhum candidato possível, encerra a aplicação
				exit(-1);
			}
			return true;
			//quando encontrar o valor, move o valor pra posição 0 e seta a quantidade como 1 e retorna true
		}
	}
	return false;
};

bool setValorNaTabela(TabelaSudoku* tabela, int posX, int posY, int valor) {

	//verifica se a posição é válida
	if (posX < 1 || posX > 9 || posY < 1 || posY > 9) {
		return false;
	}

	ConjuntoDeCandidatos* box = &(tabela->boxes[posY][posX]);

	if (setValorNaBox(box, valor)) {
		//se conseguiu setar o valor na box, percorre a linha coluna e quad apagando o valor

		//percorre a linha
		for (int i = 0; i < 9; i++) {
			if (i != posX) { //como o for percorrerá TODA a linha, incluindo a box que acabou de ser setada, deve-se verificar se a coluna é diferente da do numeor setado
				ConjuntoDeCandidatos* boxAux = &(tabela->boxes[posY][i]); //pega cada coluna da linha
				apagarValorNaBox(boxAux, valor);
			}
		}

		//percorre a coluna
		for (int i = 0; i < 9; i++) {
			if (i != posY) { //como o for percorrerá TODA a coluna, incluindo a box que acabou de ser setada, deve-se verificar se a coluna é diferente da do numeor setado
				ConjuntoDeCandidatos* boxAux = &(tabela->boxes[i][posX]);
				apagarValorNaBox(boxAux, valor);
			}
		}
		
		//percorre o quadrado

		int inicioX = getInicioQuadrado(posX);
		int inicioY = getInicioQuadrado(posY);

		for (int y = inicioY; y < inicioY + 3; y++){
			for (int x = inicioX; x < inicioX + 3; x++) {
				if (!(y == posY && x == posX)) { //se a posição percorrida for diferente da box do valor setado
					ConjuntoDeCandidatos* boxAux = &(tabela->boxes[i][posX]);
					apagarValorNaBox(boxAux, valor);
				}
			}
		}
		/*--------Continuar daqui----------*/
		return true;
		/*--------Continuar daqui----------*/
	}
	return false;

}

bool ApagarValorNaTabela(TabelaSudoku* tabela, int posX, int posY, int valor) {
	//verifica se a posição é válida
	if (posX < 1 || posX > 9 || posY < 1 || posY > 9) {
		return false;
	}

	ConjuntoDeCandidatos* box = &(tabela->boxes[posY][posX]);

	if (apagarValorNaBox(box, valor)){
		//se conseguiu apagar o valor, verifica se ficou somente 1 candidato
		//se ficou somente um candidato, define o valor na posição
		if (box->quantidade == 1) {
			int candidatoRestante = box->cadidato[0];
			setValorNaTabela(tabela, posX, posY, candidatoRestante);
		}
		return true;
	}
	return false;
}






/*----------------------------------------------------------------*/

/* TECNICAS DE RESOLUÇÃO*/

//candidato sozinho//

struct ContadorDeNumeros {
	int numero;
	int quantidade;
};

/*
bool candidatoSozinho(TabelaSudoku* tabela) {

	bool mudancas = false;
	do {

		ContadorDeNumeros contador[9];
		for (int i = 0; i < 9; i++) {
			contador[i].numero = i + 1;
		}

		/* conta os numeros em cada LINHA
		for (int i = 0; i < 9; i++) { //percorre a tabela 9x9

			for (int f = 0; f < 9; f++) { 
				contador[i].quantidade = 0; // inicia/reseta o contador em cada linha
			}

			for (int j = 0; j < 9; j++) { //percorre a tabela 9x9 - colunas

				ConjuntoDeCandidatos* box = &(tabela->boxes[i][j]);

				for (int k = 0; k < box->quantidade; k++) { //percorre os valores da box e adiciona ao contador
					int valor = box->cadidato[k];
					contador[(valor - 1)].quantidade++; //a posição 0 guarda o valor 1 e adiante, então é necessário diminuir 1 do valor encontrado
				}
				 

			}
		}




	} while (mudancas);
	

}

*/

//




