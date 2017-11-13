
//Entrou em ID TIPO
/*Compilador FOCA*/
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

	int temp1;
	int VARUSER_b;

int main(void)
{
	temp1 = 10;
	VARUSER_b = temp1;

	int VARUSER_a;
	int temp2;
	int temp3;

	std::cin >> temp2;
	VARUSER_a = temp2;

	temp3 = VARUSER_a + VARUSER_b;

	std::cout << temp3 <<  "\n";



	std::cout << VARUSER_b <<  "\n";


	return 0;
}
