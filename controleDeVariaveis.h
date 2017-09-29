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
		bool variavelReservadaDoSistema;
	};
	
	namespace MapaDeContexto{
		map<string, DADOS_VARIAVEL> mapaDeContexto;
		
		bool incluirNoMapa(string, string, bool);
		bool atualizarNoMapa(DADOS_VARIAVEL);
		bool variavelJaDeclarada(string);
		DADOS_VARIAVEL recuperarDadosVariavel(string);
		
		bool incluirNoMapa(string nome, string tipo = "", bool variavelReservadaDoSistema = false){
			if(!variavelJaDeclarada(nome)){
				DADOS_VARIAVEL variavel;
				variavel.nome = nome;
				variavel.tipo = tipo;
				variavel.variavelReservadaDoSistema = variavelReservadaDoSistema;
				mapaDeContexto[variavel.nome] = variavel;
				return true;
			}
			return false;
		}
		
		bool atualizarNoMapa(DADOS_VARIAVEL variavel){
			if(variavelJaDeclarada(variavel.nome)){
				if(mapaDeContexto[variavel.nome].tipo == "")
					mapaDeContexto[variavel.nome].tipo = variavel.tipo;
					return true;
				return false;
			}
			return false;
		}
		bool variavelJaDeclarada(string nome){
			return mapaDeContexto.find(nome) != mapaDeContexto.end();
		}
		DADOS_VARIAVEL recuperarDadosVariavel(string nome){
			if(variavelJaDeclarada(nome)){
				return mapaDeContexto[nome];
			}
		}
		
	}
	
	namespace VariaveisTemporarias{
		// a principio esse namespace não esta sendo usado aqui dentro, mas deixei aqui pra importar pro sintatico junto com esse e pq acho que pode ser interessante ter umas variaveis temporarias salvas na tabela (tipo uma com valor true e uma com false, por exemplo)
		using namespace MapaDeContexto;
		
		string gerarNovaVariavel();
		
		//declaração de variaveis var <nome variavel>;
		string gerarNovaVariavel(){
			static int num = 0;
			num++;
			//cout << num << endl;
			string temp = "temp";
	
			string numInt = to_string(num);
			return temp + numInt;
		}
	}
	
	
	using namespace VariaveisTemporarias;

}

