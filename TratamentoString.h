#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace Atributos;
using namespace ControleDeVariaveis;
using namespace EntradaESaida;
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
	string constroiDefinesParaStringDinamica();
	ATRIBUTOS traducaoStringDinamica(ATRIBUTOS, string);

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

	string constroiDefinesParaStringDinamica()
	{
		return "#define TAMANHO_INICIAL_STRING 10\n#define FATOR_CARGA_STRING 1\n#define FATOR_MULTIPLICADOR_STRING 2\n\n\n";

	}

	ATRIBUTOS traducaoStringDinamica(ATRIBUTOS atrib, string labelUsuario)
	{

		ATRIBUTOS atributos;
		//string tempa, tempb,tempc,tempd;
		int numVariaveis = 9, i;
		string temps[numVariaveis];
		string label = atrib.label;
		atributos = atrib;


		for(i = 0 ; i < numVariaveis; i++)
		{
			temps[i] = gerarNovaVariavel();

			if(i == 1)
				atributos.traducaoDeclaracaoDeVariaveis +=  "char " + temps[i] + ";\n";
			else
				atributos.traducaoDeclaracaoDeVariaveis +=  "int " + temps[i] + ";\n";

		}

		atributos.traducao += constroiTraducaoAtribuicao(temps[0], "0");
		atributos.traducao += constroiTraducaoAtribuicao(temps[2], "1");
		atributos.traducao += constroiTraducaoAtribuicao(temps[3], "TAMANHO_INICIAL_STRING");
		atributos.traducao += "\t" + label    + " = (char *) malloc(TAMANHO_INICIAL_STRING);\n";
		atributos.traducao += constroiTraducaoAtribuicao(temps[1], "1");
		atributos.traducao += constroiTraducaoAtribuicao(temps[4], "1");
		atributos.traducao += constroiTraducaoAtribuicao(temps[8], "\'\\n\'");

		atributos.traducao += "\nWHILESTR" + label + ":\n";
		atributos.traducao += "\tscanf(\"%c\",&" + temps[1] + ");\n";
		atributos.traducao += "\t" + label + "[" + temps[0] + "] = " + temps[1] +";\n";
		atributos.traducao += constroiTraducaoOperacao(temps[0], temps[0], temps[2], "+");
		atributos.traducao += constroiTraducaoOperacao(temps[5], temps[3], "FATOR_CARGA_STRING", "*");
		atributos.traducao += constroiTraducaoOperacao(temps[6], temps[0], temps[5], "<");

		atributos.traducao += constroiTraducaoIF(temps[6], "TAMINALTR" + label);
		atributos.traducao += "\t" + constroiTraducaoOperacao(temps[3], temps[3], "FATOR_MULTIPLICADOR_STRING", "*");
		atributos.traducao += "\t\t" + label + " = (char *) realloc(" + label + "," + temps[3] + ");\n";
		atributos.traducao += "TAMINALTR" + label + ":\n";
		atributos.traducao += constroiTraducaoOperacao(temps[7], temps[1], temps[8], "==");
		atributos.traducao += constroiTraducaoIF(temps[7], "FIMWHILESTR" + label);
		atributos.traducao += constroiTraducaoIF(temps[4], "WHILESTR" + label);
		atributos.traducao += "FIMWHILESTR" + label + ":\n\n";
		atributos.traducao += "\t" + label + "[" + temps[0] + "] = " + "\'\\0\'" +";\n";
		atributos.traducao += "\t" + labelUsuario + " = (char *) realloc(" + label + "," + temps[3] + ");\n";


		atributos.labelTamanhoDinamicoString = temps[0];
		return atributos;

	}



}
