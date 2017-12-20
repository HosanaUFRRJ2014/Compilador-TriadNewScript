#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace Atributos;
using namespace ControleDeVariaveis;
using namespace MapaTipos;

namespace EntradaESaida
{

	string constroiPrint(string);
	string constroiScan(string);
	ATRIBUTOS validarEntradaBooleanEmTempoExecucao(ATRIBUTOS);
	string constroiTraducaoOperacao(string, string , string , string);
	string constroiTraducaoAtribuicao(string , string );
	string constroiTraducaoIF(string , string );

	string constroiPrint(string label)
	{
		string print = "\tstd::cout << " + label + " << "+ " \'\\n\'" +";\n\n";
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
