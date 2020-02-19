
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
bool setValor(TabelaSudoku* tabela, int posX, int posY, int valor) {
	//verifica se o valor recebido está entre 1 e 9
	if (valor < 1 || valor > 9)
		return false;
	
	//verifica se a posição é válida
	if (posY < 1 || posY > 9 || posX < 1 || posX > 9)
		return false;

	ConjuntoDeCandidatos* box = &(tabela->boxes[posY][posX]);


	for (int i = 0; i < box->quantidade; i++) {
		if (box->cadidato[i] == valor) {
			box->cadidato[0] = valor;
			(box->quantidade) = 1;
			return true;
			//quando encontrar o valor, move o valor pra posição 0 e seta a quantidade como 1 e retorna true
		}
	}
	return false;
	//caso não encontre o valor na box, retorna false
}

bool apagarValor(TabelaSudoku* tabela, int posX, int posY, int valor){
	//verifica se o valor recebido está entre 1 e 9
	if (valor < 1 || valor > 9)
		return false;
	
	//verifica se a posição é válida
	if (posY < 1 || posY > 9 || posX < 1 || posX > 9)
		return false;
	
	ConjuntoDeCandidatos* box = &(tabela->boxes[posY][posX]);


	for (int k = 0; k < box->quantidade; k++) {
		if (box->cadidato[k] == valor) {
			for (int k2 = k; k2 < box->quantidade - 1; k2++) {
				box->cadidato[k2] = box->cadidato[(k2 + 1)];
			}
			box->quantidade--;
			return true;
			//quando encontrar o valor, move o valor pra posição 0 e seta a quantidade como 1 e retorna true
		}
	}
	return false;
};




/*----------------------------------------------------------------*/

/* TECNICAS DE RESOLUÇÃO*/

//candidato sozinho//

/*
bool candidatoSozinho(TabelaSudoku* entrada) {

	bool mudancas = false;
	do {

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {



			}
		}




	} while (mudancas);


}
*/



//




