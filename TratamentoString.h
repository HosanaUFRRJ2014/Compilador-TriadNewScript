#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>



using namespace Atributos;
using namespace MapaTipos;


namespace TratamentoString
{
	#define constante_TamanhoInicialPilhaString 1
	#define constante_TamanhoDeAumentoDaPilhaString 5

	//FIXME - Remover essas globais do código
	long global_numCaracteresEspeciais = 0;
	long global_tamanhoStringConcatenada = 0;
	
	struct STRING
	{
		string label;
		string valor;
		int tamanho;
		
	};
	
	
	STRING criarString(string,string,int);
	string montarCopiarString(string, string);
	string montarConcatenarString(string, string);
	string tratarCaracteresEspeciais(string, string, long *);
	string geraDeclaracaoString(string, string);
	string realizarTraducaoDeclaracaoDeString(string, ATRIBUTOS, ATRIBUTOS, ATRIBUTOS);
	string realizarOperacaoAritmeticaString(string, ATRIBUTOS, ATRIBUTOS, ATRIBUTOS);
	ATRIBUTOS tratarConversaoImplicitaString(string , ATRIBUTOS , ATRIBUTOS );
	
	
	
	
	
	void inicializarMapaDeStrings();
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
	string tratarCaracteresEspeciais(string nomeVar, string valor, long *i) 
	{
		string retorno = "";
		
		if(valor[*i] == '\\' && (valor[*i+1] == '\\'|| valor[*i+1] == '\"'|| valor[*i+1] == 'n' || valor[*i+1] == 't' || valor[*i+1] == '0')) 
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-global_numCaracteresEspeciais) + "] = \'" + "\\" + valor[*i+1] + "\';\n";
			*i = *i + 1;
			global_numCaracteresEspeciais = global_numCaracteresEspeciais + 1;
			//incrementarglobal_numCaracteresEspeciais(1);
				
			
		}	
		else if(valor[*i] == '\'')
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-global_numCaracteresEspeciais) + "] = \'" + "\\" + valor[*i] + "\';\n";
			
		}
		
		else
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-global_numCaracteresEspeciais) + "] = \'" + valor[*i] + "\';\n";
		}
		
		
		return retorno;
	}
	
	
	string geraDeclaracaoString(string nomeVar, string valor)
	{
		string retorno = "";
		long tamString = valor.length();
		
		
		STRING novaString = criarString(nomeVar,valor,valor.length());		
		mapaStrings.insert(make_pair(nomeVar, novaString));

		
		for(long i = 1; i < tamString-1; i++)
		{
			retorno = retorno + tratarCaracteresEspeciais(nomeVar,valor,&i);		
			
		}
		
		
		retorno = retorno + "\t" + nomeVar + "[" + to_string(tamString-2-global_numCaracteresEspeciais) + "] = \'" + "\\"+ "0" + "\';\n";
	
	
		return retorno;
		
	}
	
	
	string realizarTraducaoDeclaracaoDeString(string operacao, ATRIBUTOS dolarDolar, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
	
		string retorno = "";
		//não dá para fazer switch case com string em C++. Essa funcionalidade é do Java 7 +;
		if (operacao == "+")
		{
			global_tamanhoStringConcatenada = dolar1.tamanho + dolar3.tamanho + 1;
			retorno = "\tchar " + dolarDolar.label + "[" +  to_string(global_tamanhoStringConcatenada) + "]" + ";\n";
			
		
		
		}
		
		//fazer para outras operações aritméticas
		
		
		return retorno;
	
	
	}
	
	string realizarOperacaoAritmeticaString(string operacao,ATRIBUTOS dolarDolar, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		string retorno = "";
		
		//não dá para fazer switch case com string em C++. Essa funcionalidade é do Java 7 +;
		if (operacao == "+")
		{
			retorno = montarConcatenarString(dolarDolar.label, dolar1.label) + ";\n";
			retorno = retorno + montarConcatenarString(dolarDolar.label, dolar3.label) + ";\n";
		
		
		}
		//fazer para outras operações aritméticas
		
		return retorno;
	
	
	}
	
		
		
		
		
		
		
		
		
//*********************************************************************************************************************************	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	//CóDIGO INúTIL DAQUI POR DIANTE - Não apaguei porque pode ainda se tornar útil	
	string realizarConversaoImplicitaString(ATRIBUTOS dolar)
	{
		string retorno;
		
		STRING novaString;

		/*Conversões, caso necessárias*/
		if(dolar.tipo != constante_tipo_string)
		{
			novaString.label = dolar.label;
			novaString.valor = dolar.traducao;
			novaString.tamanho = (dolar.traducao).length(); 
		
			retorno = geraDeclaracaoString(novaString.label, novaString.valor);
		}

		
		return retorno;
	}
	
	
	
	
	void inicializarMapaDeStrings()
	{
		empilharString(&mapaStrings);
		//numeroEscopoAtual = numeroEscopoAtual-1;
		
	
	}
	
	/*bool incluirNoMapaStrings(string, string, int tamanho)
	{
	
		return false;
	}
	
	bool atualizarNoMapaStrigs(STRING)
	{
		return false;
	}
	
	STRING recuperarString(string id)
	{
		
		return mapaString[id];
	
	}*/
	
		



	void empilharString(map<string, STRING> * novoMapaString)
	{
		if(pilhaDeMapasString.size() + 1 > pilhaDeMapasString.capacity())
			pilhaDeMapasString.reserve(pilhaDeMapasString.size() + constante_TamanhoDeAumentoDaPilhaString);
			
		//numeroEscopoAtual = numeroEscopoAtual+1;
		pilhaDeMapasString.push_back(*novoMapaString);
	
	}
	
	
	/*map<string, STRING> recuperarMapaStrings(int)
	{
		map<string, STRING> mapa;
	
		return mapa;
	}
	
	
	bool desempilarString()
	{
	
		return false;
	
	}*/
	
	/*vector<map<string, STRING>> pilhaDeMapasString(constante_TamanhoInicialPilhaString)
	{
		vector<map<string, STRING>> vetor;
	
		return vetor;
	
	}*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*ATRIBUTOS realizarOperacaoAritmeticaString(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		ATRIBUTOS retorno;
		
	
		if(op == "+")
		{
			retorno.label = gerarNovaVariavel();
			
			
		}
		
	
	}*/
	
	
	/*ATRIBUTOS tratarConversaoImplicitaString(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
	{
		string dolar1Convertido = "";
		string dolar3Convertido = "";
		
		if(dolar1.tipo != constante_tipo_string)
			dolar1 = converterVariavelParaString(dolar1); //acho que não precisa fazer retornar, creio que vá alterar lá dentro
			
		if(dolar3.tipo != constante_tipo_string)
			dolar3 = converterVariavelParaString(dolar3);
			
		if(dolar1.tipo == constante_erro || dolar3.tipo == constante_erro)
		{
			//disparar erro ou sinalizar erro para o sintática
			return NULL;
		}
		
		return dolar1;
	}*/
	

}
