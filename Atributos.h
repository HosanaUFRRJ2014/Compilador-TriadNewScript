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
		
	};
	
//	recuperarLabelCodigoIntermediario($x.label)

	#endif
}
