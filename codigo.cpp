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

	char temp1[4];
	char VARUSER_a[4];
	char temp2[10];
	char temp3[14];
	char temp4[18];

	temp1[0] = 'e';
	temp1[1] = 'i';
	temp1[2] = 't';
	temp1[3] = 'a';
	temp1[4] = '\0';
	strcpy(VARUSER_a,temp1);

	temp2[0] = '\t';
	temp2[1] = 'a';
	temp2[2] = 't';
	temp2[3] = 'r';
	temp2[4] = 'a';
	temp2[5] = 's';
	temp2[6] = '\t';
	temp2[7] = 'd';
	temp2[8] = 'e';
	temp2[9] = '\t';
	temp2[10] = '\0';
	strcpy(temp3,"");
	strcat(temp3,VARUSER_a);
	strcat(temp3,temp2);
	strcpy(temp4,"");
	strcat(temp4,temp3);
	strcat(temp4,VARUSER_a);

	std::cout << temp4 <<  "\n";


fimCodInter:	return 0;
}
