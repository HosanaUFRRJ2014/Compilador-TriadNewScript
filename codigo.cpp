/*Compilador FOCA*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

#define TAMANHO_INICIAL_STRING 10
#define FATOR_MULTIPLICADOR_STRING 2
#define FATOR_CARGA_STRING 1


int main(void)
{

	int temp1;
	int VARUSER_a;
	float temp2;
	float VARUSER_b;
	float temp3;
	float temp4;
	float VARUSER_c;
	float VARUSER_i;
	int temp5;
	int VARUSER_d;
	float temp6;
	int temp7;
	float temp8;
	float temp9;
	float temp10;
	float temp11;

	temp1 = 1;
	VARUSER_a = temp1;

	temp2 = 1.2;
	VARUSER_b = temp2;

	temp3 = (float)VARUSER_a;
	temp4 = temp3 + VARUSER_b;
	VARUSER_c = temp4;


	std::cout << VARUSER_c <<  "\n";


	temp5 = 1;
	VARUSER_d = temp5;

	temp6 = 10.5;
	temp7 = 4;
	temp8 = (float)temp7;
	temp9 = temp6 * temp8;
	temp10 = (float)VARUSER_d;
	temp11 = temp10 + temp9;
	VARUSER_i = temp11;


	std::cout << VARUSER_i <<  "\n";


FIMCODINTER:	return 0;
}
