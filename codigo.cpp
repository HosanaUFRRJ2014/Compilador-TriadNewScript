/*Compilador TriadNewScript*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

#define TAMANHO_INICIAL_STRING 100


char **variavelDoUsuario1; //VARUSER_a
int temp1;
int temp2;
char* *temp3;




int main(void)
{
	temp2 = 0;
	temp4 = 1;
	temp5 = TAMANHO_INICIAL_STRING;
	temp1 = (char *) malloc(temp5);
	temp3 = 1;
	temp6 = 1;
	temp10 = '\n';

WHILESTRtemp1:
	scanf("%c",&temp3);
	temp1[temp2] = temp3;
	temp2 = temp2 + temp4;
	temp8 = temp2 < temp5;
	if(temp8) goto TAMINALTRtemp1;
		temp5 = temp5 + temp4;
		temp1 = (char *) realloc(temp1,temp5);
TAMINALTRtemp1:
	temp9 = temp3 == temp10;
	if(temp9) goto FIMWHILESTRtemp1;
	if(temp6) goto WHILESTRtemp1;
FIMWHILESTRtemp1:

	temp7 = temp2 - temp4;
	temp1[temp7] = '\0';
	variavelDoUsuario1 = (char *) realloc(temp1,temp5);
	strcpy(variavelDoUsuario1,temp1);

	temp12 = 0;
	temp14 = 1;
	temp15 = TAMANHO_INICIAL_STRING;
	temp11 = (char *) malloc(temp15);
	temp13 = 1;
	temp16 = 1;
	temp20 = '\n';

WHILESTRtemp11:
	scanf("%c",&temp13);
	temp11[temp12] = temp13;
	temp12 = temp12 + temp14;
	temp18 = temp12 < temp15;
	if(temp18) goto TAMINALTRtemp11;
		temp15 = temp15 + temp14;
		temp11 = (char *) realloc(temp11,temp15);
TAMINALTRtemp11:
	temp19 = temp13 == temp20;
	if(temp19) goto FIMWHILESTRtemp11;
	if(temp16) goto WHILESTRtemp11;
FIMWHILESTRtemp11:

	temp17 = temp12 - temp14;
	temp11[temp17] = '\0';
	variavelDoUsuario2 = (char *) realloc(temp11,temp15);
	strcpy(variavelDoUsuario2,temp11);

	temp22 = TAMANHO_INICIAL_STRING;
	temp23 = TAMANHO_INICIAL_STRING;
	temp24 = temp22 + temp23;
	temp21 = (char *) malloc(temp24);
	strcpy(temp21,"");
	strcat(temp21,variavelDoUsuario1);
	strcat(temp21,variavelDoUsuario2);
	variavelDoUsuario3 = temp21; //VARUSER_c


	std::cout << variavelDoUsuario3 <<  '\n';


	goto FIMCODINTER;


	INDEX_NEG_ZERO:
	std::cout << "Acesso ou alocação de memória indevida (Memory fault)." <<  '\n';

	FIMCODINTER:
	return 0;
}
