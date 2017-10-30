#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

namespace ControleDeVariaveis
{
	struct DADOS_VARIAVEL
	{
		string tipo;
		string nome;
		int tamanho;
	};
	
	namespace MapaDeContexto
	{
		#define prefixo_variavel_usuario "USER_"
		#define constante_TamanhoInicialPilha 1
		#define constante_TamanhoDeAumentoDaPilha 5
		int numeroEscopoAtual = 0;
		vector<map<string, DADOS_VARIAVEL>> pilhaDeMapas(constante_TamanhoInicialPilha);
		map<string, DADOS_VARIAVEL> mapaDeContexto;
		
		void inicializarMapaDeContexto();
		bool incluirNoMapa(string, string, int escopo = numeroEscopoAtual);
		bool atualizarNoMapa(DADOS_VARIAVEL, int escopo = numeroEscopoAtual);
		bool variavelJaDeclarada(string, bool varrerEscopo = true, int escopo = numeroEscopoAtual);
		DADOS_VARIAVEL recuperarDadosVariavel(string, int escopo = numeroEscopoAtual);
		
		//escopo
		void aumentarEscopo();
		void empilha(map<string, DADOS_VARIAVEL>*);
		void diminuirEscopo();
		map<string, DADOS_VARIAVEL> recuperarMapa(int);
		
		
		
		void aumentarEscopo(){
			map<string, DADOS_VARIAVEL> novoMapa;
			empilha(&novoMapa);
			pilhaDeMapas[numeroEscopoAtual].clear();
		}
		
		void empilha(map<string, DADOS_VARIAVEL>* novoMapa){	
			if(pilhaDeMapas.size() + 1 > pilhaDeMapas.capacity())
				pilhaDeMapas.reserve(pilhaDeMapas.size() + constante_TamanhoDeAumentoDaPilha);
				
			numeroEscopoAtual = numeroEscopoAtual+1;
			pilhaDeMapas.push_back(*novoMapa);
		}
		
		void diminuirEscopo(){
			numeroEscopoAtual = numeroEscopoAtual-1;
			if(numeroEscopoAtual == -1) 
				numeroEscopoAtual = 0;
				//dispara erro e retorna
			pilhaDeMapas.pop_back();//desempilha
			
		}

		void inicializarMapaDeContexto()
		{
			empilha(&mapaDeContexto);
			numeroEscopoAtual = numeroEscopoAtual-1;
		}
		
		string adcionaPrefixo(string nome)
		{
			if(nome.find(prefixo_variavel_usuario) != 0)
				nome = prefixo_variavel_usuario + nome;
			return nome;
		}
				
		bool incluirNoMapa(string nome, string tipo = "", int escopo)
		{
			nome = adcionaPrefixo(nome);
			
			if(!variavelJaDeclarada(nome, false))
			{
				DADOS_VARIAVEL variavel;
				variavel.nome = nome;
				variavel.tipo = tipo;
				pilhaDeMapas[escopo][variavel.nome] = variavel;
				return true;
			}
			return false;
		}
		
		bool atualizarNoMapa(DADOS_VARIAVEL variavel, int escopo)
		{
			
			if(variavelJaDeclarada(variavel.nome))
			{
				if(mapaDeContexto[variavel.nome].tipo == "")
				{
					mapaDeContexto[variavel.nome].tipo = variavel.tipo;
					return true;
				}
			}
			return false;
		}
		
		bool variavelJaDeclarada(string nome, bool varrerEscopo, int escopo)
		{
			if(varrerEscopo)
			{
				//ponto de parada
				if(escopo < 0)
					return false;

				nome = adcionaPrefixo(nome);
				//variavel que vai manter qual foi o ultimo mapa acessado
				mapaDeContexto = pilhaDeMapas[escopo];
				//operador curto circuitado para buscar a variavel nos mapas recursivamente
				return (mapaDeContexto.find(nome) != mapaDeContexto.end()) || variavelJaDeclarada(nome, varrerEscopo, escopo - 1);
			}
			else
			{
				nome = adcionaPrefixo(nome);
				return pilhaDeMapas[escopo].find(nome) != pilhaDeMapas[escopo].end();
			}
		}
		
		DADOS_VARIAVEL recuperarDadosVariavel(string nome, int escopo)
		{
			nome = adcionaPrefixo(nome);
			if(variavelJaDeclarada(nome))
			{
				return mapaDeContexto[nome];
			}
		}
		
	}
	
	namespace declaracaoProvisoriaInferenciaTipo
	{
		#define constante_subst_tipo_declaracao_variavel "//#TIPOP_VAR_\t_#"
		#define slotIdVar "\t"
		map<string, string> mapaSubstituicaoDeTipoProvisorio;
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string);
		void adcionarDefinicaoDeTipo(string, string);
		string substituirTodasAsDeclaracoesProvisorias(string);
		
		string adcionaPrefixo(string id)
		{
			if(id.find(prefixo_variavel_usuario) != 0)
				id = prefixo_variavel_usuario + id;
			return id;
		}
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string id)
		{
			
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string separador = slotIdVar;
			string idPrefixado = adcionaPrefixo(id);
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = " ";
			return tipoProvisorio + " " + idPrefixado + ";\n";
		}
			
		void adcionarDefinicaoDeTipo(string id, string tipo)
		{
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string idPrefixado = adcionaPrefixo(id);
			string separador = slotIdVar;
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			
			mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = tipo;
		}
		
		string substituirTodasAsDeclaracoesProvisorias(string declaracoes)
		{
			for(map<string, string>::iterator it=mapaSubstituicaoDeTipoProvisorio.begin();it!=mapaSubstituicaoDeTipoProvisorio.end(); ++it)
			{
				string key = it->first;
				string value = it->second;
						
				int pos = declaracoes.find(key);
				if(pos >= 0)
					declaracoes.replace(pos, key.length(), value);
			}
			
			return declaracoes;
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
	using namespace declaracaoProvisoriaInferenciaTipo;

}

