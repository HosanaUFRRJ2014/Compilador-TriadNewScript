#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

namespace ControleDeVariaveis{
	struct DADOS_VARIAVEL
	{
		string tipo;
		string nome;
		int tamanho;
	};
	
	namespace MapaDeContexto{
		#define prefixo_variavel_usuario "USER_"
		int numeroEscopoAtual = 0;
		vector<map<string, DADOS_VARIAVEL>> pilhaDeMapas;
		map<string, DADOS_VARIAVEL> mapaDeContexto;
		
		void inicializarMapa();
		bool incluirNoMapa(string, string, int);
		bool atualizarNoMapa(DADOS_VARIAVEL, int);
		bool variavelJaDeclarada(string, int escopo = numeroEscopoAtual);
		DADOS_VARIAVEL recuperarDadosVariavel(string);
		
		void inicializarMapa(){
			map<string, DADOS_VARIAVEL> mapa0;
			pilhaDeMapas.push_back(mapa0);
		}
				
		bool incluirNoMapa(string nome, string tipo = "", int escopo = numeroEscopoAtual){
			if(!variavelJaDeclarada(nome)){
				DADOS_VARIAVEL variavel;
				variavel.nome = nome;
				variavel.tipo = tipo;
				mapaDeContexto[variavel.nome] = variavel;
				return true;
			}
			return false;
		}
		
		bool atualizarNoMapa(DADOS_VARIAVEL variavel, int escopo = numeroEscopoAtual){
			if(variavelJaDeclarada(variavel.nome)){
				if(mapaDeContexto[variavel.nome].tipo == "")
					mapaDeContexto[variavel.nome].tipo = variavel.tipo;
					return true;
				return false;
			}
			return false;
		}
		
		bool variavelJaDeclarada(string nome, int escopo){
			return mapaDeContexto.find(nome) != mapaDeContexto.end();
		}
		
		DADOS_VARIAVEL recuperarDadosVariavel(string nome){
			if(variavelJaDeclarada(nome)){
				return mapaDeContexto[nome];
			}
		}
		
	}
	
	namespace VariaveisTemporarias{
		#define prefixo_variavel_sistema "temp"
		
		string gerarNovaVariavel();
		
		//declaração de variaveis var <nome variavel>;
		string gerarNovaVariavel(){
			static int num = 0;
			num++;
			string temp = prefixo_variavel_sistema;
	
			string numInt = to_string(num);
			return temp + numInt;
		}
	}
	
	
	using namespace VariaveisTemporarias;
	using namespace MapaDeContexto;

}

