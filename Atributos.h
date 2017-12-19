#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

/*Namespace criado apenas para separar a struct ATRIBUTOS de sintatica.y
Razão: Preciso usá-la em TratamentoString. Espero que a escolha de implementação seja compreendida.*/
namespace Atributos
{

	#ifndef ATRIBUTOS
	#define YYSTYPE ATRIBUTOS

	struct ATRIBUTOS
	{
		string label;
		string traducaoDeclaracaoDeVariaveis;
		string traducao;
		string tipo;
		int escopoDeAcesso = -1;
		int tamanho = 0;
		bool ehDinamica = false;
		string estruturaDoConteudo;
		string labelTamanhoDinamicoString;
		int valorNum = -1; //Retornar valor tipoPrimitivo TK_NUM inteiro.
		string labelIndice; //Salvar o label resultado de um cálculo de indice do array.
		string nomeIdOriginal; //Poder retornar os valores do array corretamente.
		bool acessoArray = false; //Poder reconhecer o caso ternura[x,y] = luadecristal[z,w].
		bool criacaoArray = false; //Poder tratar os erros de livia[x,y] = int[u,v].
		string tipoArray; //Se for array de acesso, saber o tipo do mesmo.

	};

//	recuperarLabelCodigoIntermediario($x.label)

	#endif
}
