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


char * variavelDoUsuario1; //VARUSER_a
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
int temp11;
int variavelDoUsuario2; //VARUSER_b



int main(void)
{
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
		temp5 = temp5 + temp6;
		temp1 = (char *) realloc(temp1,temp5);
TAMINALTRtemp1:
	temp9 = temp3 == temp10;
	if(temp9) goto FIMWHILESTRtemp1;
	if(temp6) goto WHILESTRtemp1;
FIMWHILESTRtemp1:

	temp1[temp2] = '\0';
	variavelDoUsuario1 = (char *) realloc(temp1,temp5);
	strcpy(variavelDoUsuario1,temp1);

	temp11 = sizeof(variavelDoUsuario1);
	std::cout << temp2 << '\n';
	variavelDoUsuario2 = temp11;


	std::cout << variavelDoUsuario1 <<  '\n';



	std::cout << variavelDoUsuario2 <<  '\n';


FIMCODINTER:	return 0;
}
