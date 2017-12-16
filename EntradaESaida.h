#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>


using namespace ControleDeVariaveis;
using namespace MapaTipos;
//using namespace VariaveisTemporarias;

namespace EntradaESaida
{

	string constroiPrint(string);
	string constroiScan(string);
	ATRIBUTOS validarEntradaBooleanEmTempoExecucao(ATRIBUTOS);
	ATRIBUTOS traducaoStringDinamica(ATRIBUTOS, string);
	string constroiTraducaoOperacao(string, string , string , string);
	string constroiTraducaoAtribuicao(string , string );
	string constroiTraducaoIF(string , string );

	string constroiPrint(string label)
	{
		string print = "\tstd::cout << " + label + " << "+ " \"\\n\"" +";\n\n";
		return print;
	}


	string constroiScan(string label,string tipo)
	{
		string scan;// = "\tstd::cin >> " + label + ";\n";

		if(tipo == constante_tipo_string)
			scan = "\tscanf(\"%s\","+ label + ");\n";

		else
			scan = "\tstd::cin >> " + label + ";\n";
		return scan;
	}

	//Verificação se o valor digitado é 0 ou 1. Caso seja diferente, termina o programa.
	ATRIBUTOS validarEntradaBooleanEmTempoExecucao(ATRIBUTOS atrib)
	{
		ATRIBUTOS atributos;
		//string tempa, tempb,tempc,tempd;
		int numVariaveis = 4;
		string temps[numVariaveis];
		string label = atrib.label;
		atributos = atrib;

		for(int i = 0 ; i < numVariaveis; i++)
		{
			temps[i] = gerarNovaVariavel();
			atributos.traducaoDeclaracaoDeVariaveis +=  "\tint " + temps[i] + ";\n";

		}

		/*atributos.traducao += "\t" + temps[0] + " = TRUE == " + label + ";\n";
		atributos.traducao += "\t" + temps[1] + " = FALSE == " + label + ";\n";
		atributos.traducao += "\t" + temps[2] +" = " + temps[0] + " || " + temps[1] + ";\n";
		atributos.traducao += "\t" + temps[3] +" = !" + temps[2] + ";\n";
		atributos.traducao += "\tif(" + temps[3] + ") goto fimCodInter;\n";*/


		atributos.traducao += constroiTraducaoOperacao(temps[0], "TRUE", label, "==");
		atributos.traducao += constroiTraducaoOperacao(temps[1], "FALSE",label , "==");
		atributos.traducao += constroiTraducaoOperacao(temps[2], temps[0], temps[1], "||");
		atributos.traducao += constroiTraducaoAtribuicao(temps[3], "!" + temps[2]);
		atributos.traducao += constroiTraducaoIF(temps[3], "FIMCODINTER");

		return atributos;


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

		return atributos;

	}


	string constroiTraducaoOperacao(string labelReceptora, string operando1, string operando2, string operador)
	{

		return "\t" + labelReceptora + " = " + operando1 + " " + operador + " " + operando2 + ";\n";

	}

	string constroiTraducaoAtribuicao(string labelReceptora, string valor)
	{
		return "\t" + labelReceptora + " = " + valor + ";\n";

	}


	string constroiTraducaoIF(string label, string addr)
	{
		return "\tif(" + label + ") goto " + addr + ";\n";

	}


}
