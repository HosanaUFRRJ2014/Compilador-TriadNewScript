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

	char  *  VARUSER_inocente;
	char * temp1;
	int temp2;
	char temp3;
	int temp4;
	int temp5;
	int temp6;
	int temp7;
	int temp8;
	int temp9;
	char  *  VARUSER_a;
	char * temp10;
	int temp11;
	char temp12;
	int temp13;
	int temp14;
	int temp15;
	int temp16;
	int temp17;
	int temp18;

	temp2 = 0;
	temp4 = 1;
	temp5 = TAMANHO_INICIAL_STRING;
	temp1 = (char *) malloc(TAMANHO_INICIAL_STRING);
	temp3 = 1;
	temp6 = 1;

whileStrtemp1:
	scanf("%c",&temp3);
	temp1[temp2] = temp3;
	temp2 = temp2 + temp4;
	temp7 = temp5 * FATOR_CARGA_STRING;
	temp8 = temp2 < temp7;
	if(temp8) goto tamInaltrtemp1;
		temp5 = temp5 * FATOR_MULTIPLICADOR_STRING;
		temp1 = (char *) realloc(temp1,temp5);
tamInaltrtemp1:
	temp9 = temp3 == '\n';
	if(temp9) goto fimWhileStrtemp1;
	if(temp6) goto whileStrtemp1;
fimWhileStrtemp1:

	VARUSER_inocente = (char *) realloc(temp1,temp5);
	strcpy(VARUSER_inocente,temp1);


	std::cout << VARUSER_inocente <<  "\n";


	temp11 = 0;
	temp13 = 1;
	temp14 = TAMANHO_INICIAL_STRING;
	temp10 = (char *) malloc(TAMANHO_INICIAL_STRING);
	temp12 = 1;
	temp15 = 1;

whileStrtemp10:
	scanf("%c",&temp12);
	temp10[temp11] = temp12;
	temp11 = temp11 + temp13;
	temp16 = temp14 * FATOR_CARGA_STRING;
	temp17 = temp11 < temp16;
	if(temp17) goto tamInaltrtemp10;
		temp14 = temp14 * FATOR_MULTIPLICADOR_STRING;
		temp10 = (char *) realloc(temp10,temp14);
tamInaltrtemp10:
	temp18 = temp12 == '\n';
	if(temp18) goto fimWhileStrtemp10;
	if(temp15) goto whileStrtemp10;
fimWhileStrtemp10:

	VARUSER_a = (char *) realloc(temp10,temp14);
	strcpy(VARUSER_a,temp10);


	std::cout << VARUSER_a <<  "\n";


fimCodInter:	return 0;
}
