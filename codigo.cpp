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


char temp1;
int temp2;
int temp3;
int temp4;
int temp5;



int main(void)
{
	temp1 = 'a';
	temp2 = 1;
	temp4 = (int)temp1;
		temp3 = temp4 == temp2;
	temp5 = temp3;
	if(temp5)
		goto IF_TRUE1;

	std::cout << "Palavras diferentes" <<  '\n';

	goto FIM_IF1;
	IF_TRUE1:

	std::cout << "Palavras iguais" <<  '\n';

	FIM_IF1:;

FIMCODINTER:	return 0;
}
