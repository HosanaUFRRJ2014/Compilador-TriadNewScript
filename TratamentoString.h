#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>


namespace TratamentoString
{

	
	long global_numCaracteresEspeciais = 0;



	string tratarCaracteresEspeciais(string, string, long *);
	string geraDeclaracaoString(string, string);
	
	
		
	
	
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
	
		
		return retorno;
		
	}
	

}
