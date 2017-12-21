#include <stdio.h>

int main()
{
	
	/*
	int a = 5;
	
	switch(a)
	{
		case 1: {break;}
		case 2:
		case 5: {printf("Sou o case 5!\n");}
		case 10: {printf("Sou o case 10!\n");}
		case 15: {printf("Sou o case 15!\n");}
		default: {printf("Sou o default!\n");}
	}
	*/
	/*
	int b = 9;
	
	do{
		printf("b = %d\n",b);
		if(b == 5)
			break;
		b--;
	}while(b > 0);
	*/
	
	int a,b;
	
	for(a = 10,b = 10;a > 0 && b > 0;a--,b--,printf("--Dei update!--\n"))
		printf("Oi, eu sou um for!\n");
	
	
	return 0;
}
