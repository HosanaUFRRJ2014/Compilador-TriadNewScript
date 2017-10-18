/*Compilador FOCA*/
#include<string.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0

int main(void)
{
	char temp1[7];

	temp1[0] = 'a';
	temp1[1] = 'b';
	temp1[2] = 'c';
	temp1[3] = '+';
	temp1[4] = '$';
	temp1[5] = '*';
	temp1[6] = '\0';

printf("%s\n\n", temp1);

	return 0;
}
