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

	char  *  VARUSER_a;
	char  *  VARUSER_b;
	char * temp1;
	int temp2;
	char temp3;
	int temp4;
	int temp5;
	int temp6;
	int temp7;
	int temp8;
	int temp9;
	int temp10;
	char * temp11;
	int temp12;
	char temp13;
	int temp14;
	int temp15;
	int temp16;
	int temp17;
	int temp18;
	int temp19;
	int temp20;

	temp2 = 0;
	temp4 = 1;
	temp5 = TAMANHO_INICIAL_STRING;
	temp1 = (char *) malloc(TAMANHO_INICIAL_STRING);
	temp3 = 1;
	temp6 = 1;
	temp10 = '\n';

WHILESTRtemp1:
	scanf("%c",&temp3);
	temp1[temp2] = temp3;
	temp2 = temp2 + temp4;
	temp7 = temp5 * FATOR_CARGA_STRING;
	temp8 = temp2 < temp7;
	if(temp8) goto TAMINALTRtemp1;
		temp5 = temp5 * FATOR_MULTIPLICADOR_STRING;
		temp1 = (char *) realloc(temp1,temp5);
TAMINALTRtemp1:
	temp9 = temp3 == temp10;
	if(temp9) goto FIMWHILESTRtemp1;
	if(temp6) goto WHILESTRtemp1;
FIMWHILESTRtemp1:

	temp1[temp2] = '\0';
	VARUSER_a = (char *) realloc(temp1,temp5);
	strcpy(VARUSER_a,temp1);

	temp12 = 0;
	temp14 = 1;
	temp15 = TAMANHO_INICIAL_STRING;
	temp11 = (char *) malloc(TAMANHO_INICIAL_STRING);
	temp13 = 1;
	temp16 = 1;
	temp20 = '\n';

WHILESTRtemp11:
	scanf("%c",&temp13);
	temp11[temp12] = temp13;
	temp12 = temp12 + temp14;
	temp17 = temp15 * FATOR_CARGA_STRING;
	temp18 = temp12 < temp17;
	if(temp18) goto TAMINALTRtemp11;
		temp15 = temp15 * FATOR_MULTIPLICADOR_STRING;
		temp11 = (char *) realloc(temp11,temp15);
TAMINALTRtemp11:
	temp19 = temp13 == temp20;
	if(temp19) goto FIMWHILESTRtemp11;
	if(temp16) goto WHILESTRtemp11;
FIMWHILESTRtemp11:

	temp11[temp12] = '\0';
	VARUSER_b = (char *) realloc(temp11,temp15);
	strcpy(VARUSER_b,temp11);

FIMCODINTER:	return 0;
}
