/*Compilador FOCA*/
#include<string.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0

	int USER_abc;

int main(void)
{

	int temp1;
	int USER_a;
	int temp2;
	int temp4;
	int temp5;
	int temp6;
	int temp7;
	int temp8;
	int temp9;
	int temp10;
	int temp11;
	int temp12;
	float temp13;
	float temp14;
	float temp15;

	temp1 = 109;
	USER_abc = temp1;

printf("%d\n\n", USER_abc);

	temp2 = 10;
	USER_a = temp2;

printf("%d\n\n", USER_a);

	{
	char temp3;
	char USER_a;

	temp3 = 'O';
	USER_a = temp3;

printf("%d\n\n", USER_a);

	}
	temp4 = 1;
	temp5 = 3;
	temp6 = 10;
	temp7 = 50;
	temp8 = temp6 + temp7;
	temp9 = temp5 * temp8;
	temp10 = 2;
	temp11 = temp9 / temp10;
	temp12 = temp4 - temp11;
	temp13 = -1.0;
	temp14 = (float)temp12;
	temp15 = temp14 * temp13;

printf("%f\n\n", temp15);

	return 0;
}
