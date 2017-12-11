/*Compilador TriadNewScript*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

	char variavelDoUsuario1[5]; //VARUSER_i
	char temp1[15];
	char temp2[19];
	char variavelDoUsuario2[19]; //VARUSER_h



int main(void)
{
	strcpy(variavelDoUsuario1,"eita");

	strcpy(temp1,"");
	strcat(temp1,variavelDoUsuario1);
	strcat(temp1," atras de ");
	strcpy(temp2,"");
	strcat(temp2,temp1);
	strcat(temp2,variavelDoUsuario1);
	strcpy(variavelDoUsuario2,temp2);


	std::cout << variavelDoUsuario2 <<  "\n";


FIMCODINTER:	return 0;
}
