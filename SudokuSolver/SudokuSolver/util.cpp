int getInicioQuadrado(int pos) {
	if (pos < 0 || pos > 8) { //a posição na tabela vai somente de 0 a 8
		return -1;
	}

	if (pos < 3) {
		return 0;
	}
	else if (pos < 6) {
		return 3;
	}
	return 6;
	/*ATENÇÃO -  a primeira função delimita os valores de entrada, caso for modificar, certificar que valor de 
	retorno esteja correto*/
}