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

	ATRIBUTOS concatenarTraducoesAtributos(ATRIBUTOS , ATRIBUTOS );
	ATRIBUTOS copiarDadosAtributos(ATRIBUTOS );
	void imprimirAtributos(ATRIBUTOS atributos);

//	recuperarLabelCodigoIntermediario($x.label)
	ATRIBUTOS concatenarTraducoesAtributos(ATRIBUTOS atributosDestino, ATRIBUTOS atributosOrigem)
	{
		ATRIBUTOS atributosSaida;
		atributosSaida.traducaoDeclaracaoDeVariaveis = atributosDestino.traducaoDeclaracaoDeVariaveis + atributosOrigem.traducaoDeclaracaoDeVariaveis;
		atributosSaida.traducao = atributosDestino.traducao + atributosOrigem.traducao;

		return atributosSaida;

	}

	ATRIBUTOS copiarDadosAtributos(ATRIBUTOS atributosOrigem)
	{
		ATRIBUTOS atributosDestino;
		atributosDestino.label = atributosOrigem.label;
		atributosDestino.tipo = atributosOrigem.tipo;
		atributosDestino.escopoDeAcesso = atributosOrigem.escopoDeAcesso;
		atributosDestino.tamanho = atributosOrigem.tamanho;
		atributosDestino.ehDinamica = atributosOrigem.ehDinamica;
		atributosDestino.estruturaDoConteudo = atributosOrigem.estruturaDoConteudo;
		atributosDestino.labelTamanhoDinamicoString = atributosOrigem.labelTamanhoDinamicoString;

		return atributosDestino;
	}

	void imprimirAtributos(ATRIBUTOS atributos)
	{
		std::cout << "/* Imprimindo variável: " << atributos.label  <<  " */" << '\n';
		std::cout << "// atributos.label :" << atributos.label << '\n';
		std::cout << "// atributos.tipo :" << atributos.tipo << '\n';
		std::cout << "// atributos.escopoDeAcesso :" << atributos.escopoDeAcesso << '\n';
		std::cout << "// atributos.tamanho :" << atributos.tamanho << '\n';
		std::cout << "// atributos.ehDinamica :" << atributos.ehDinamica << '\n';
		std::cout << "// atributos.estruturaDoConteudo :" << atributos.estruturaDoConteudo << '\n';
		std::cout << "// atributos.traducaoDeclaracaoDeVariaveis :" << atributos.traducaoDeclaracaoDeVariaveis << '\n';
		std::cout << "// atributos.traducao :" << atributos.traducao << '\n';
		std::cout << "/*********** Fim da impressão ***************/" << '\n';

	}

	#endif
}
