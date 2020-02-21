// SudokuSolver.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//



//#include <opencv2/opencv.hpp>

#include "sudokuTable.cpp"
//using namespace cv;


int main() {

	//Mat img = imread("foto_lates_Natan.PNG");
	//namedWindow("image", WINDOW_NORMAL);
	//imshow("image", img);
	//waitKey(0);
	//return 0;

	TabelaSudoku tabela = TabelaSudoku();
	TabelaDeEntrada tab = TabelaDeEntrada();

	imprimirMatriz(&tab);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			if(tab.matriz[i][j] != 0)
				setValorNaTabela(&tabela, i, j, tab.matriz[i][j]);
		}
	}

	imprimirTabelaBoxes(&tabela);

	while (candidatoSozinho(&tabela)) {
		cout << endl;
	};
	
	imprimirTabelaBoxes(&tabela);

	//setValor(&tabela, 2, 2, 8);
	//apagarValor(&tabela, 4, 4, 2);

	/*
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << tab.matriz[i][j] << " ";
		}
		cout << endl;
	}
	*/
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
