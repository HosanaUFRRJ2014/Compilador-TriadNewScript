/*Compilador TriadNewScript*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

#define TAMANHO_INICIAL_STRING 10
#define FATOR_CARGA_STRING 1
#define FATOR_MULTIPLICADOR_STRING 2


int temp1;
int temp2;
int temp3;
int temp4;




int main(void)
{
	temp1 = 0;
	temp2 = strcmp("banana","banana");
	temp3 = temp1 == temp2;
	temp4 = temp3;
	if(temp4)
		goto IF_TRUE1;

	std::cout << "Palavras diferentes" <<  '\n';

	goto FIM_IF1;
	IF_TRUE1:

	std::cout << "Palavras iguais" <<  '\n';

	FIM_IF1:;

	goto FIMCODINTER;


	INDEX_NEG_ZERO:
	std::cout << "Acesso ou alocação de memória indevida (Memory fault)." <<  '\n';

	FIMCODINTER:
	return 0;
}
