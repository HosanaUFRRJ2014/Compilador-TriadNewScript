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
		int escopo;
	};
	
	
	namespace MapaDeContexto
	{
		#define prefixo_variavel_usuario "VARUSER_"
		#define constante_TamanhoInicialPilha 1
		#define constante_TamanhoDeAumentoDaPilha 5
		int numeroEscopoAtual = 0;
		vector<map<string, DADOS_VARIAVEL>> pilhaDeMapas(constante_TamanhoInicialPilha);
		map<string, DADOS_VARIAVEL> mapaDeContexto;
		
		void inicializarMapaDeContexto();
		bool incluirNoMapa(string, string);
		bool atualizarNoMapa(DADOS_VARIAVEL, int escopo = numeroEscopoAtual);
		bool variavelJaDeclarada(string, bool varrerEscopo = true, int escopo = numeroEscopoAtual);
		DADOS_VARIAVEL recuperarDadosVariavel(string, int escopo = numeroEscopoAtual);
		
		//escopo
		void aumentarEscopo();
		void empilha(map<string, DADOS_VARIAVEL>*);
		void diminuirEscopo();
		map<string, DADOS_VARIAVEL> recuperarMapa(int);
		bool ehMaiorIgualQueEscopoAtual(int);
		int escopoResultante(int);
		

		bool ehMaiorIgualQueEscopoAtual(int qtdRetornoEscopo)
		{
			return qtdRetornoEscopo >= numeroEscopoAtual;
		}
		
		int escopoResultante(int qtdRetornoEscopo)
		{
			return numeroEscopoAtual - qtdRetornoEscopo;
		}
		
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
				
		bool incluirNoMapa(string nome, string tipo = "")
		{
			nome = adcionaPrefixo(nome);
			
			if(!variavelJaDeclarada(nome, false))
			{
				DADOS_VARIAVEL variavel;
				variavel.nome = nome;
				variavel.tipo = tipo;
				variavel.escopo = numeroEscopoAtual;
				pilhaDeMapas[numeroEscopoAtual][variavel.nome] = variavel;
				return true;
			}
			return false;
		}
		
		bool atualizarNoMapa(DADOS_VARIAVEL variavel, int escopo)
		{
			
			if(variavelJaDeclarada(variavel.nome, true, escopo))
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
			if(variavelJaDeclarada(nome, true, escopo))
			{
				return mapaDeContexto[nome];
			}
		}
		
	}
	
	namespace DeclaracaoProvisoriaInferenciaTipo
	{
		using namespace MapaDeContexto;
		
		#define constante_subst_tipo_declaracao_variavel "//#TIPOP_VAR_\t_\t#"
		#define slotIdVar "\t"
		#define constante_sufixo_escopo "SCOPE"
		map<string, string> mapaSubstituicaoDeTipoProvisorio;
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string);
		void adcionarDefinicaoDeTipo(string, string, int);
		string substituirTodasAsDeclaracoesProvisorias(string);
		
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string id)
		{
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string separador = slotIdVar;
			string idPrefixado = adcionaPrefixo(id);
			//primeiro insere o nome da variavel no primeiro slot e depois adciona o numero do escopo no segundo slot
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(numeroEscopoAtual));
			mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = " ";
			return tipoProvisorio + " " + idPrefixado + ";\n";
		}
			
		void adcionarDefinicaoDeTipo(string id, string tipo, int escopo = numeroEscopoAtual)
		{
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string idPrefixado = adcionaPrefixo(id);
			string separador = slotIdVar;
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
			
			//verificação a mais inserida pq havia problema na hora de definir o tipo de uma variavel global
			//pq o escopo da variavel global é 0 mas o C++ só aceita definição de valor de variavel global em algum escopo interno
			//então na hora de substituir o escopo é 1, mas deveria ser 0 ... então essa busca acha o lugar correto
			if(mapaSubstituicaoDeTipoProvisorio.find(tipoProvisorio) == mapaSubstituicaoDeTipoProvisorio.end()){
				while(escopo > 0){
					DADOS_VARIAVEL metadata = recuperarDadosVariavel(id, escopo);
					escopo = metadata.escopo;
					if(metadata.tipo == "") break;			
				}
				
				constanteMarcacao = constante_subst_tipo_declaracao_variavel;
				tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
				sufixoEscopo = constante_sufixo_escopo;
				tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
			}
				
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
// tinhas posto o clear pra ajudar no gerenciamento de chaves repetidas... mas deu problema
//			mapaSubstituicaoDeTipoProvisorio.clear();
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
	using namespace DeclaracaoProvisoriaInferenciaTipo;

}

