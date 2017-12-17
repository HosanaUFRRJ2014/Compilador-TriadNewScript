#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

namespace ControleDeFuncoes
{
	struct BODY{
		string traducaoDeclaracaoDeVariaveis;
		string traducao;
		bool utilizado;
	};
	
	struct HEADER{
		string nome;
		map<string, DADOS_VARIAVEL> parametros;
	};
	
	struct FUNCTION{
		HEADER cabecalho;
		vector<string, BODY> corpos;
		string nomeTraducao;
		int escopoDeDefinicao;
		int qtdCombinacoesParametros;
	};
	
	map<string, FUNCTION> mapaDeDadosDasFuncoes;
	vector<string> pilhaFuncoesEmCriacao;
	
	bool criarFuncao(string nomeFuncao){
		FUNCTION f;
		f.cabecalho.nome = nomeFuncao;
		f.escopoDeDefinicao = numeroEscopoAtual;
		pilhaFuncoesEmCriacao.push_back(f);
	}
	
	bool adicionarParametro(string nomeFuncao, string nomeParametro){
		
	}
	
	string funcaoEmConstrucao(){
	
	}
	
	string gerarNovoFuncaoCodigoIntermediario(){
		
	}
	
	
	
	
	
	
}
