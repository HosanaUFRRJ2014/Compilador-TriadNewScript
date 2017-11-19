#include <stdio.h>

int main()
{
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

	return 0;
}
