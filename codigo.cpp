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


	char variavelDoUsuario1[5]; //VARUSER_senh
	char temp1[6];
	char temp5[10];



int main(void)
{
	strcpy(variavelDoUsuario1,"->ar");

	strcpy(temp1,"");
	strcat(temp1,"ar");
	strcat(temp1,"ara");
	strcpy(temp5,"");
	strcat(temp5,variavelDoUsuario1);
	strcat(temp5,temp1);
	variavelDoUsuario1 = temp5;


	std::cout << variavelDoUsuario1 <<  "\n";


FIMCODINTER:	return 0;
}
