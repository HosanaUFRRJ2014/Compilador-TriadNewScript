#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>



using namespace Atributos;
using namespace MapaTipos;


namespace TratamentoString
{
	bool ehStringVazia(int );
	string montarCopiarString(string, string);
	string montarConcatenarString(string, string);
	string tratarCaracteresEspeciais(string, string, int *, int *);
	int atualizarTamanhoString(int );
	string realizarTraducaoDeclaracaoDeString(string, ATRIBUTOS , ATRIBUTOS , ATRIBUTOS );
	string realizarOperacaoAritmeticaString(string, ATRIBUTOS, ATRIBUTOS, ATRIBUTOS);
	ATRIBUTOS tratarConversaoImplicitaString(string , ATRIBUTOS , ATRIBUTOS );
	bool necessidaDeclaracaoDinamica(ATRIBUTOS , ATRIBUTOS );

	bool ehStringVazia(int tamanhoString)
	{
		if(tamanhoString > 0) return false;

	}


	string montarCopiarString(string str1, string str2)
	{
		string retorno = "\tstrcpy(" + str1 + "," + str2 + ")";

		return retorno;
	}

	string montarConcatenarString(string str1, string str2)
	{

		string retorno = "\tstrcat(" + str1 + "," + str2 + ")";

		return retorno;

	}

	int atualizarTamanhoString(int tamString)
	{
		int novoTamanhoString = 0;

		novoTamanhoString = tamString - 2 + 1; //tirando as duas aspas e colocando o \0

		return novoTamanhoString;

	}


	string realizarTraducaoDeclaracaoDeString(string operacao, ATRIBUTOS dolarDolar, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		string retorno = "";

		if(necessidaDeclaracaoDinamica(dolar1, dolar3))
			retorno = "\tchar * " + dolarDolar.label + ";\n";

		else
			retorno = "\tchar " + dolarDolar.label + "[" +  to_string(dolarDolar.tamanho) + "]" + ";\n";

		return retorno;
	}

	string realizarOperacaoAritmeticaString(string operacao,ATRIBUTOS * dolarDolar, ATRIBUTOS * dolar1, ATRIBUTOS * dolar3)
	{
		string retorno = "";

		//não dá para fazer switch case com string em C++. Essa funcionalidade é do Java 7 +;
		if (operacao == "+")
		{
			retorno = montarCopiarString(dolarDolar->label,"\"\"") + ";\n";
			retorno += montarConcatenarString(dolarDolar->label, dolar1->label) + ";\n";
			retorno += montarConcatenarString(dolarDolar->label, dolar3->label) + ";\n";
			dolarDolar->tamanho = dolar1->tamanho + dolar3->tamanho - 1; //para remover um dos '\0'

			if(dolar1->ehDinamica == true || dolar3->ehDinamica == true)
				dolarDolar->ehDinamica = true;


		}
		//TODO - fazer para outras operações aritméticas

		return retorno;


	}

	bool necessidaDeclaracaoDinamica(ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		if(dolar1.ehDinamica || dolar3.ehDinamica)  //necessidade de fazer assim, pq valores que deviam ser 0 estavam vindo como numero 252, por exemplo.
		{
			return true;
		}
		return false;

	}


}
