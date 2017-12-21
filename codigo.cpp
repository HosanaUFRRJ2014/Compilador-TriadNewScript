/*Compilador TriadNewScript*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

#define TAMANHO_INICIAL_STRING 100


int temp1;
int variavelDoUsuario1; //VARUSER_a
float temp2;
float variavelDoUsuario2; //VARUSER_b
float temp3;
float temp4;
float variavelDoUsuario3; //VARUSER_c
float variavelDoUsuario4; //VARUSER_i
int temp5;
int variavelDoUsuario5; //VARUSER_d
float temp6;
int temp7;
float temp8;
float temp9;
float temp10;
float temp11;
int temp12;
float temp13;
float temp14;
float temp15;



int main(void)
{
	temp1 = 1;
	variavelDoUsuario1 = temp1;

	temp2 = 1.2;
	variavelDoUsuario2 = temp2;

	temp3 = (float)variavelDoUsuario1;
	temp4 = temp3 + variavelDoUsuario2;
	variavelDoUsuario3 = temp4;


	std::cout << variavelDoUsuario3 <<  '\n';


	temp5 = 1;
	variavelDoUsuario5 = temp5;

	temp6 = 10.5;
	temp7 = 4;
	temp8 = (float)temp7;
	temp9 = temp6 * temp8;
	temp10 = (float)variavelDoUsuario5;
	temp11 = temp10 + temp9;
	temp12 = 2;
	temp13 = (float)temp12;
	temp14 = variavelDoUsuario2 / temp13;
	temp15 = temp11 - temp14;
	variavelDoUsuario4 = temp15;


	std::cout << variavelDoUsuario4 <<  '\n';


	goto FIMCODINTER;


	INDEX_FORA_LIMITE:
	std::cout << "Acesso a memória indevido (Memory fault)." <<  '\n';


	ALOCACAO_NEG_ZERO:
	std::cout << "Alocação de memória indevida (Memory fault)." <<  '\n';

	FIMCODINTER:
	return 0;
}
