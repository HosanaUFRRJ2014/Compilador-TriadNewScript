#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>


namespace TratamentoString
{
	string geraDeclaracaoString(string, string);
	
	string geraDeclaracaoString(string nomeVar, string valor)
	{
		string retorno = "";
		int tamString = valor.length();
		for(int i=1; i < tamString-1; i++)
			retorno = retorno + "\t" + nomeVar + "[" + to_string(i-1) + "] = \'" + valor[i] + "\';\n";

		retorno = retorno + "\t" + nomeVar + "[" + to_string(tamString-2) + "] = \'" + "\\"+ "0" + "\';\n";
		
		return retorno;
		
	}

}
