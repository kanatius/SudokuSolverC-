int getInicioQuadrado(int pos) {
	if (pos < 0 || pos > 8) { //a posi��o na tabela vai somente de 0 a 8
		return -1;
	}

	if (pos < 3) {
		return 0;
	}
	else if (pos < 6) {
		return 3;
	}
	return 6;
	/*ATEN��O -  a primeira fun��o delimita os valores de entrada, caso for modificar, certificar que valor de 
	retorno esteja correto*/
}