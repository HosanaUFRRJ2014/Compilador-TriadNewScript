//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_INICIAL 5
#define FATOR_MULTIPLICADOR 2 //o número de vezes que a String crescerá
#define FATOR_CARGA 0.75 //Como no Hashmap do Java. https://docs.oracle.com/javase/6/docs/api/java/util/HashMap.html

int main(int argc, char const *argv[])
{
	
	long i;
	char c;
	char um;
	long count;
	long tamanhoAtual;
	char * vetor;


	int aux1;
	int aux2;
	int aux3;
	int aux4;

	i = 0;
	um = 1;
	tamanhoAtual = TAMANHO_INICIAL;
	vetor = (char *) malloc(TAMANHO_INICIAL); //só armazena 1060 caracteres
	aux1 = 1;


whileStr: 
		scanf("%c",&c);
		vetor[i] = c;
		i = i + um;

		aux2 = tamanhoAtual * FATOR_CARGA;
		aux3 = i < aux2; 

		printf("O i  em: %lu\n", i);

		if (aux3) goto tamInaltr;
			printf("O i estourou, em: %lu, (tamanhoAtual * FATOR_CARGA): %d\n", i, aux2);
			tamanhoAtual = tamanhoAtual * FATOR_MULTIPLICADOR;
			vetor = (char *) realloc(vetor, tamanhoAtual);

tamInaltr: 
		aux4 = c == '\n'
		if (aux4) goto fimWhileStr;


		if (aux1) goto whileStr;




fimWhileStr:


/*	while(1)
	{
		scanf("%c",&c);
		vetor[i] = c;
		i = i + um;

		if (i >= tamanhoAtual * FATOR_CARGA)
		{
			printf("O i estourou, em: %d\n", i);
			tamanhoAtual = tamanhoAtual * FATOR_MULTIPLICADOR;
			vetor = (char *) realloc(vetor, tamanhoAtual);
		}

		if (c == '\n')
			break;

	}*/

	count = i;
	printf("\n\n\n\n***********************************Imprimindo entrada:***************************************** \n\n\n\n");
	for (i = 0; i < count; ++i)
	{
		printf("%c",vetor[i]);
	}

	return 0;
}
