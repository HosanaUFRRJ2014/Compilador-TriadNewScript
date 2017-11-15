/*Compilador FOCA*/
#include <iostream>
#include <string.h>
#include <sstream>

#define TRUE 1
#define FALSE 0

	int temp1;
	int VARUSER_a;

int main(void)
{
	temp1 = 1;
	VARUSER_a = temp1;

	char temp2[4];
		char VARUSER_a[0];
	int temp3;
	int temp4;
	int temp5;
	int temp6;
	int temp7;
	char temp8[8];
	char temp9[4];
	char temp10[13];

	temp2[0] = 'a';
	temp2[1] = 'l';
	temp2[2] = 'o';
	temp2[3] = '\0';
	strcpy(VARUSER_a,temp2);


	std::cout << VARUSER_a <<  "\n";


	temp3 = 1;
	temp4 = 3;
	temp5 = 7;
	temp6 = temp4 * temp5;
	temp7 = temp3 + temp6;

	std::cout << temp7 <<  "\n";


	temp8[0] = 'D';
	temp8[1] = 'o';
	temp8[2] = 'c';
	temp8[3] = 't';
	temp8[4] = 'o';
	temp8[5] = 'r';
	temp8[6] = ' ';
	temp8[7] = '\0';
	temp9[0] = 'W';
	temp9[1] = 'h';
	temp9[2] = 'o';
	temp9[3] = '\0';
	strcat(temp10,temp8);
	strcat(temp10,temp9);

	std::cout << temp10 <<  "\n";


	return 0;
}
