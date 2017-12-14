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
	string montarMallocString(string, string );
	string montarCopiarString(string, string);
	string montarConcatenarString(string, string);
	string tratarCaracteresEspeciais(string, string, int *, int *);
	int atualizarTamanhoString(int );
	string realizarTraducaoDeclaracaoDeStringConcatenada(string, ATRIBUTOS *, ATRIBUTOS *, ATRIBUTOS *, string, string, string);
	string realizarOperacaoAritmeticaString(string, ATRIBUTOS *, ATRIBUTOS *, ATRIBUTOS *, string, string, string);
	ATRIBUTOS tratarConversaoImplicitaString(string , ATRIBUTOS , ATRIBUTOS );
	bool necessidaDeclaracaoDinamica(ATRIBUTOS , ATRIBUTOS );

	bool ehStringVazia(int tamanhoString)
	{
		if(tamanhoString > 0) return false;

	}

	string montarMallocString(string strDestino,string tamString)
	{
		//temp21 = (char *) malloc(sizeof(*variavelDoUsuario1 + *variavelDoUsuario2));
		return "\t" + strDestino + " = (char *) malloc(" + tamString +");\n";
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


	string realizarTraducaoDeclaracaoDeStringConcatenada(string operacao, ATRIBUTOS * dolarDolar, ATRIBUTOS * dolar1, ATRIBUTOS * dolar3, string varTamDolarDolar, string varTamDolar1, string varTamDolar3)
	{
		string retorno = "";

		if(necessidaDeclaracaoDinamica(*dolar1, *dolar3))
		{
			retorno = "char * " + dolarDolar->label + ";\n";
			retorno += "int " + varTamDolar1 + ";\n";
			retorno += "int " + varTamDolar3+ ";\n";
			retorno += "int " + varTamDolarDolar + ";\n";

			dolarDolar->ehDinamica = true;
		}

		else
			retorno = "\tchar " + dolarDolar->label + "[" +  to_string(dolarDolar->tamanho) + "]" + ";\n";

		return retorno;
	}

/*	string gerarDeclaracaoTamanhoConcatenacaoString()
	{

	}
*/
	string realizarOperacaoAritmeticaString(string operacao,ATRIBUTOS * dolarDolar, ATRIBUTOS * dolar1, ATRIBUTOS * dolar3,
		string varTamDolarDolar, string varTamDolar1, string varTamDolar3)
	{
		string retorno = "";

		//não dá para fazer switch case com string em C++. Essa funcionalidade é do Java 7 +;

		if(necessidaDeclaracaoDinamica(*dolar1,*dolar3))
		{
			retorno = "\t" + varTamDolar1 + " = sizeof("+ dolar1->label +");\n";
			retorno += "\t" + varTamDolar3 + " = sizeof("+ dolar3->label +");\n";
			retorno += "\t" + varTamDolarDolar + " = " + varTamDolar1 + " + " + varTamDolar3 + ";\n";
			retorno += montarMallocString(dolarDolar->label,varTamDolarDolar);
		}


		if (operacao == "+")
		{
			retorno += montarCopiarString(dolarDolar->label,"\"\"") + ";\n";
			retorno += montarConcatenarString(dolarDolar->label, dolar1->label) + ";\n";
			retorno += montarConcatenarString(dolarDolar->label, dolar3->label) + ";\n";
			dolarDolar->tamanho = dolar1->tamanho + dolar3->tamanho - 1; //para remover um dos '\0'


		}
		//TODO - fazer para outras operações aritméticas

		return retorno;


	}

	bool necessidaDeclaracaoDinamica(ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
	/*	std::cout << "neces dolar1.ehDinamica:" << dolar1.ehDinamica << '\n';
		std::cout << "neces dolar3.ehDinamica:" << dolar3.ehDinamica << '\n';*/
		if(dolar1.ehDinamica || dolar3.ehDinamica)  //necessidade de fazer assim, pq valores que deviam ser 0 estavam vindo como numero 252, por exemplo.
		{
			return true;
		}
		return false;

	}


}
