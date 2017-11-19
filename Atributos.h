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
		string label; //Texto lido do lex.
		string traducaoDeclaracaoDeVariaveis; //Para colocação do atributo no início do código.
		string traducao; //Tradução do código atual.
		string tipo; //Tipo resultante atual da tradução.
		int escopoDeAcesso = -1;
		int tamanho = 0;
		
	};




	#endif
}
