/*Compilador FOCA*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

#define TAMANHO_INICIAL_STRING 10
#define FATOR_MULTIPLICADOR_STRING 2
#define FATOR_CARGA_STRING 0.75


int main(void)
{

	char VARUSER_inocente[9];;
	char temp1[9];
	char temp2[17];
	char temp3[26];
		char VARUSER_a[26];

	temp1[0] = 'i';
	temp1[1] = 'n';
	temp1[2] = 'o';
	temp1[3] = 'c';
	temp1[4] = 'e';
	temp1[5] = 'n';
	temp1[6] = 't';
	temp1[7] = 'e';
	temp1[8] = '\0';
	strcpy(VARUSER_inocente,temp1);

	temp2[0] = 's';
	temp2[1] = 'a';
	temp2[2] = 'b';
	temp2[3] = 'e';
	temp2[4] = '\t';
	temp2[5] = 'd';
	temp2[6] = 'e';
	temp2[7] = '\t';
	temp2[8] = '\'';
	temp2[9] = 'n';
	temp2[10] = 'a';
	temp2[11] = 'd';
	temp2[12] = 'a';
	temp2[13] = '\'';
	temp2[14] = ' ';
	temp2[15] = '\n';
	temp2[16] = '\0';
	strcpy(temp3,"");
	strcat(temp3,temp2);
	strcat(temp3,VARUSER_inocente);
	strcpy(VARUSER_a,temp3);


	std::cout << VARUSER_a <<  "\n";


	return 0;
}
