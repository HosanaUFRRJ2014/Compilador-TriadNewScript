#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>



using namespace Atributos;
using namespace MapaTipos;


namespace TratamentoString
{

	
	long global_numCaracteresEspeciais = 0;



	string tratarCaracteresEspeciais(string, string, long *);
	string geraDeclaracaoString(string, string);
	ATRIBUTOS tratarConversaoImplicitaString(string , ATRIBUTOS , ATRIBUTOS );
	
	
		
	
	
	string tratarCaracteresEspeciais(string nomeVar, string valor, long *i) 
	{
		string retorno = "";
		
		if(valor[*i] == '\\' && valor[*i+1] == '\"') //Pode ser que dê segmentation fault se já estiver na posição final.
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-global_numCaracteresEspeciais) + "] = \'" + "\\" + "\"" + "\';\n";
			*i = *i + 1;
			global_numCaracteresEspeciais = global_numCaracteresEspeciais + 1;
			//incrementarglobal_numCaracteresEspeciais(1);
				
			
		}	
		else if(valor[*i] == '\'')
		{
			retorno = "\t" + nomeVar + "[" + to_string(*i-1-global_numCaracteresEspeciais) + "] = \'" + "\\" + "\'" + "\';\n";
			
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
		
		for(long i = 1; i < tamString-1; i++)
		{
			retorno = retorno + tratarCaracteresEspeciais(nomeVar,valor,&i);
			
		}
		
		
		retorno = retorno + "\t" + nomeVar + "[" + to_string(tamString-2-global_numCaracteresEspeciais) + "] = \'" + "\\"+ "0" + "\';\n";
	
	//	cout << retorno << "        ********\n\n";
		return retorno;
		
	}
	
	
	
	//TODO - fazer com que a variável seja convertida, caso possível. Se impossível, setar o tipo como errado
	//FIXME - Converter para array char, ao invés de para uma string
	ATRIBUTOS converterVariavelParaString(ATRIBUTOS dolar1, ATRIBUTOS dolar3, string operador)
	{
		if(getTipoResultante(dolar1.tipo, dolar3.tipo, operador) != constante_erro)
		{
			dolar1.tipo = constante_tipo_string;
			dolar1.tamanho = (dolar1.traducao).length(); //verificar isso, pois pode estar muito errado
			dolar1.traducao = "\"" + dolar1.traducao + "\""; //verificar isso, pois pode estar muito errado
			
			cout << "Tamanho: \n" << dolar1.tamanho << "\n**********\n\n";
			cout << "Traducao: \n" << dolar1.traducao << "\n**********\n\n";
			
			
			dolar3.tipo = constante_tipo_string;
			dolar3.tamanho = (dolar3.traducao).length(); //verificar isso, pois pode estar muito errado
			dolar3.traducao = "\"" + dolar3.traducao + "\""; //verificar isso, pois pode estar muito errado
			
			cout << "Tamanho: \n" << dolar3.tamanho << "\n**********\n\n";
			cout << "Traducao: \n" << dolar3.traducao << "\n**********\n\n";
			
		}
	
		return dolar1;
	}
	
	
	ATRIBUTOS realizarConversaoImplicitaString(ATRIBUTOS dolar1, ATRIBUTOS dolar3, string op)
	{
		string dolarConvertido = "";
	
		
		/*Conversões, caso necessárias e possíveis*/
		if(dolar1.tipo != constante_tipo_string)
			dolar1 = converterVariavelParaString(dolar1, dolar3, op); //acho que não precisa fazer retornar, creio que vá alterar lá dentro
		
		if(dolar3.tipo != constante_tipo_string)
			dolar3 = converterVariavelParaString(dolar1, dolar3, op);	
			
		/*if(dolar1.tipo == constante_erro)
		{
			//disparar erro ou sinalizar erro para o sintática
			return NULL;
		}*/
		
		return dolar1;
	}
	
	
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
