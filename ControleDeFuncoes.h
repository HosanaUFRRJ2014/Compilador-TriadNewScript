#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace std;
using namespace ControleDeVariaveis;

namespace ControleDeFuncoes
{
	struct BODY{
		string traducao;
	};
	
	struct HEADER{
		string nome;
		map<string, DADOS_VARIAVEL> parametros;
	};
	
	struct FUNCTION{
		HEADER cabecalho;
		BODY corpo;
		string nomeTraducao;
	};
	
	
}
