//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_INICIAL_STRING 10
#define FATOR_MULTIPLICADOR_STRING 2
#define FATOR_CARGA_STRING 0.75 

 //o número de vezes que a String crescerá
//Como no Hashmap do Java. https://docs.oracle.com/javase/6/docs/api/java/util/HashMap.html

int main(int argc, char const *argv[])
{
	
	int temp0;
	char temp1;
	int temp2;
//	int tempx;
	int temp3;
	char * vetor; //trocar por label da entrada


	int temp4;
	int temp5;
	int temp6;
	int temp7;

	temp0 = 0;
	temp2 = 1;
	temp3 = TAMANHO_INICIAL_STRING;
	vetor = (char *) malloc(TAMANHO_INICIAL_STRING); //só armazena 1060 caracteres
	temp4 = 1;

whileStr: //concatenar com label da string
		scanf("%c",&temp1);
		vetor[temp0] = temp1;
		temp0 = temp0 + temp2;

		temp5 = temp3 * FATOR_CARGA_STRING;
		temp6 = temp0 < temp5; 

		//printf("O temp0  em: %d\n", temp0);

		if (temp6) goto tamInaltr;
			//printf("O temp0 estourou, em: %d, (tamanhoAtual * FATOR_CARGA_STRING): %d\n", temp0, temp5);
			temp3 = temp3 * FATOR_MULTIPLICADOR_STRING;
			vetor = (char *) realloc(vetor, temp3);

tamInaltr: 
		temp7 = temp1 == '\n';
		if (temp7) goto fimWhileStr;


		if (temp4) goto whileStr;




fimWhileStr:


/*	while(1)
	{
		scanf("%c",&c);
		vetor[i] = c;
		i = i + um;

		if (i >= tamanhoAtual * FATOR_CARGA_STRING)
		{
			printf("O i estourou, em: %d\n", i);
			tamanhoAtual = tamanhoAtual * FATOR_MULTIPLICADOR_STRING;
			vetor = (char *) realloc(vetor, tamanhoAtual);
		}

		if (c == '\n')
			break;

	}*/

	/*tempx = temp0;
	printf("\n\n\n\n***********************************Imprimindo entrada:***************************************** \n\n\n\n");
	for (temp0 = 0; temp0 < tempx; ++temp0)
	{
		printf("%c",vetor[temp0]);
	}*/

	return 0;
}
