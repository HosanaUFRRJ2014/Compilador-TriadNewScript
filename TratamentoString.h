#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>



using namespace Atributos;
using namespace MapaTipos;


namespace TratamentoString
{
	/*#define constante_TamanhoInicialPilhaString 1
	#define constante_TamanhoDeAumentoDaPilhaString 5

	
	struct STRING
	{
		string label;
		string valor;
		int tamanho;
		
	};*/
	
	
	//STRING criarString(string,string,int);
	bool ehStringVazia(int );
	string montarCopiarString(string, string);
	string montarConcatenarString(string, string);
	string tratarCaracteresEspeciais(string, string, int *, int *);
	string geraDeclaracaoString(string, string, int *);
	string realizarTraducaoDeclaracaoDeString(string, ATRIBUTOS , ATRIBUTOS , ATRIBUTOS );
	string realizarOperacaoAritmeticaString(string, ATRIBUTOS, ATRIBUTOS, ATRIBUTOS);
	ATRIBUTOS tratarConversaoImplicitaString(string , ATRIBUTOS , ATRIBUTOS );
	bool necessidaDeclaracaoDinamica(ATRIBUTOS , ATRIBUTOS );
	
	
	
	
	/*void inicializarMapaDeStrings();
	bool incluirNoMapaStrings(string, string, int tamanho);
	bool atualizarNoMapaStrigs(STRING);
	STRING recuperarString(string);
	
	//escopo
	//void aumentarEscopo();
	void empilharString(map<string, STRING> * );
	map<string, STRING> recuperarMapaStrings(int);
	bool desempilarString();
	vector<map<string, STRING>> pilhaDeMapasString(constante_TamanhoInicialPilhaString);
		


	map<string, STRING> mapaStrings;
	
	
	
	
	STRING criarString(string label,string valor,int tamanho)
	{
		STRING nova;
		
		nova.label = label;
		nova.valor = valor;
		nova.tamanho = tamanho;
		
		
		return nova;
	
	}*/
	
	bool ehStringVazia(int tamanhoString)
	{
		if(tamanhoString == 2) return true;
	
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
	string tratarCaracteresEspeciais(string nomeVar, string valor, int *i, int * numCaracteresEspeciais) 
	{
		string retorno = "";
		
		if(valor[*i] == '\\' && valor[*i+1] == '\"')
		{
			if(*i+2 != valor.length())
			{
				retorno = "\t" + nomeVar + "[" + to_string(*i-1-*numCaracteresEspeciais) + "] = \'" + "\\" + valor[*i+1] + "\';\n";
				*i = *i + 1;
				*numCaracteresEspeciais = *numCaracteresEspeciais + 1;
			}
		
			else
				retorno = "\t" + nomeVar + "[" + to_string(*i-1-*numCaracteresEspeciais) + "] = \'" + "\\\\" + "\';\n";	
		
			
		
		}
		
		else if(valor[*i] == '\\' && (valor[*i+1] == '\\' || valor[*i+1] == 'n' || valor[*i+1] == 't' || valor[*i+1] == '0')) 
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-*numCaracteresEspeciais) + "] = \'" + "\\" + valor[*i+1] + "\';\n";
			*i = *i + 1;
			*numCaracteresEspeciais = *numCaracteresEspeciais + 1;
				
		}	
		else if(valor[*i] == '\'')
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-*numCaracteresEspeciais) + "] = \'" + "\\" + valor[*i] + "\';\n";
			
		}
		
		else
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-*numCaracteresEspeciais) + "] = \'" + valor[*i] + "\';\n";
		
		
		
		return retorno;
	}
	
	string geraDeclaracaoString(string nomeVar, string valor, int * tamString)
	{
		string retorno = "";
		int numCaracteresEspeciais = 0;
		
		if(!ehStringVazia(*tamString))
		{
			for(int i = 1; i < *tamString-1; i++)
			{
				retorno = retorno + tratarCaracteresEspeciais(nomeVar,valor,&i,&numCaracteresEspeciais);		
			
			}
		
			*tamString = *tamString - 2 - numCaracteresEspeciais;
			retorno = retorno + "\t" + nomeVar + "[" + to_string(*tamString) + "] = \'" + "\\"+ "0" + "\';\n";
		}
		
		else
		{ 
			*tamString = 1;
			retorno = retorno + "\t" + nomeVar + "[" + to_string(0) + "] = \'" + "\\"+ "0" + "\';\n";
		}
		
			
		
		return retorno;
		
	}
	
	
	string realizarTraducaoDeclaracaoDeString(string operacao, ATRIBUTOS dolarDolar, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
	
		string retorno = "";
		
		
		if(necessidaDeclaracaoDinamica(dolar1, dolar3))
		{
			//cout << dolarDolar.label;
			retorno = "\tchar * " + dolarDolar.label + ";\n";
		
		}
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
			dolarDolar->tamanho = dolar1->tamanho + dolar3->tamanho; 
			if(dolar1->ehDinamica == true || dolar3->ehDinamica == true)
				dolarDolar->ehDinamica = true;
		/*	cout << "*realizarOperacaoAritmeticaString**************\n";
			cout << "label1: " << dolar1->label << " tamaho: " << dolar1->tamanho << endl;
			cout << "label3: " << dolar3->label << " tamaho: " << dolar3->tamanho << endl;
			cout << "label$$: " << dolarDolar->label << " tamaho: " << dolarDolar->tamanho << endl;
			cout << "***************\n";*/
		
		
		}
		//TODO - fazer para outras operações aritméticas
		
		return retorno;
	
	
	}
	
	bool necessidaDeclaracaoDinamica(ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		//cout << dolar1.ehDinamica << endl;
		//cout << dolar3.ehDinamica << endl;
		if(dolar1.ehDinamica || dolar3.ehDinamica)  //necessidade de fazer assim, pq valores que deviam ser 0 estavam vindo como numero 252, por exemplo.
		{
			return true;
		}	
		return false;
	
	}
	

}
