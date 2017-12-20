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


char **variavelDoUsuario1; //VARUSER_a
int temp1;
int temp2;
char* *temp3;




int main(void)
{
	temp1 = 5;
	variavelDoUsuario1 = (char**) malloc(temp1 * sizeof(char*));
	variavelDoUsuario1[0] = "Lívia";
	variavelDoUsuario1[1] = "de";
	variavelDoUsuario1[2] = "Azevedo";
	variavelDoUsuario1[3] = "da";
	variavelDoUsuario1[4] = "Silva";

	temp2 = 5;
	temp3 = (char**) malloc(temp2 * sizeof(char*));
	temp3[0] = "William";
	temp3[1] = "Anderson";
	temp3[2] = "de";
	temp3[3] = "Brito";
	temp3[4] = "Gomes";
	free(variavelDoUsuario1);
	variavelDoUsuario1 = temp3;

	goto FIMCODINTER;


	INDEX_FORA_LIMITE:
	std::cout << "Acesso a memória indevido (Memory fault)." <<  '\n';


	ALOCACAO_NEG_ZERO:
	std::cout << "Alocação de memória indevida (Memory fault)." <<  '\n';

	FIMCODINTER:
	free(variavelDoUsuario1);
	return 0;
}
