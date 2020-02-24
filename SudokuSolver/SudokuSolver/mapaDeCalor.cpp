
#include "sudokuTable.cpp"

struct MapaCalor {
	BoxValorCalor* matriz;
	int quantidade;
};

struct BoxValorCalor {
	ValorCalor* vetor;
	int quantidade;
	int posX;
	int posY;
};

struct ValorCalor{
	int valor;
	int calorLinha;
	int calorColuna;
	int calorQuad;
};

void imprimirMapaCalor(MapaCalor* mapa){

	for (int i = 0; i < mapa->quantidade; i++) { //percorre a matriz

		BoxValorCalor* box = &(mapa->matriz[i]);

		cout << "BOX POS [" << box->posY << "][" << box->posX << "]" << endl;

		for (int j = 0; j < box->quantidade; j++) { //percorre os valores das boxes

			cout << "Valor " << box->vetor[j].valor << endl;
			cout << "Calor linha: " << box->vetor[j].calorLinha << endl;
			cout << "Calor coluna: " << box->vetor[j].calorColuna << endl;
			cout << "Calor Quadrado: " << box->vetor[j].calorQuad << endl;

		}
		cout << endl;
	}
}


int getCalorTotal(ValorCalor* valorCalor) {
	return valorCalor->calorColuna + valorCalor->calorLinha + valorCalor->calorQuad;
}

ValorCalor* getVetorValorCalor(ConjuntoDeCandidatos* box) {

	ValorCalor* vetorValor = new ValorCalor[box->quantidade];

	for (int i = 0; i < box->quantidade; i++) {
		vetorValor[i].valor = box->cadidato[i];
		vetorValor[i].calorColuna = 0;
		vetorValor[i].calorLinha = 0;
		vetorValor[i].valor = 0;
	}

	return vetorValor;
}

 MapaCalor getMapaCalor(TabelaSudoku* tabela) {

	 MapaCalor mapa;

	 int qtdBoxes = getQtdCelulasComMaisDeUmCandidato();
	 mapa.matriz = new BoxValorCalor[qtdBoxes];
	 mapa.quantidade = qtdBoxes;

	 int cont = 0;

	 for (int i = 0; i < 9; i++) { //percorre todas as células
		 for (int j = 0; j < 9; j++) { //percorre todas as células

			 ConjuntoDeCandidatos* box = &(tabela->boxes[i][j]);

			 if (box->quantidade > 1) { //entra somente em células com qtd de candidatos maior q 1
				 mapa.matriz[cont].posX = j;
				 mapa.matriz[cont].posY = i;
				 mapa.quantidade = box->quantidade;
				 mapa.matriz[cont].vetor = getVetorValorCalor(box);
			 }
		 }
	 }
	 return mapa;
}

 int getQtdCelulasComMaisDeUmCandidato(TabelaSudoku* tabela) {

	 int cont = 0;

	 for (int i = 0; i < 9; i++) {
		 for (int j = 0; j < 9; j++) {
			 if (tabela->boxes[i][j].quantidade > 1) {
				 cont++;
			 }
		 }
	 } //necessário contar quantas casas há para iniciar o vetor

	 return cont;
 }