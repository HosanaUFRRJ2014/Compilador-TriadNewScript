anho: 
1.tamanho: 
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

	char temp1[1];
	char VARUSER_a[1];
	char temp2[3];
	char VARUSER_b[3];
	char temp3[3];
	char temp4[6];

	temp1[0] = 'a';
	temp1[1] = '\0';
	strcpy(VARUSER_a,temp1);

	temp2[0] = 'a';
	temp2[1] = 'a';
	temp2[2] = 'a';
	temp2[3] = '\0';
	strcpy(VARUSER_b,temp2);

	temp3[0] = 'a';
	temp3[1] = 'b';
	temp3[2] = 'c';
	temp3[3] = '\0';
	strcpy(temp4,"");
	strcat(temp4,temp3);
	strcat(temp4,VARUSER_b);
	strcpy(VARUSER_a,temp4);


	std::cout << VARUSER_a <<  "\n";


fimCodInter:	return 0;
}
