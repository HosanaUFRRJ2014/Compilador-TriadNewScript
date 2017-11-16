/*Compilador FOCA*/
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

	char temp1[14];
	char temp2[9];
	char temp3[24];

	temp1[0] = 's';
	temp1[1] = 'a';
	temp1[2] = 'b';
	temp1[3] = 'e';
	temp1[4] = ' ';
	temp1[5] = 'd';
	temp1[6] = 'e';
	temp1[7] = ' ';
	temp1[8] = 'n';
	temp1[9] = 'a';
	temp1[10] = 'd';
	temp1[11] = 'a';
	temp1[12] = ' ';
	temp1[13] = '\0';
	temp2[0] = 'i';
	temp2[1] = 'n';
	temp2[2] = 'o';
	temp2[3] = 'c';
	temp2[4] = 'e';
	temp2[5] = 'n';
	temp2[6] = 't';
	temp2[7] = 'e';
	temp2[8] = '\0';
	strcat(temp3,temp1);
	strcat(temp3,temp2);

	std::cout << temp3 <<  "\n";


	return 0;
}
