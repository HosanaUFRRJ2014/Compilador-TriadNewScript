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
//		#define constante_TamanhoInicialPilha 5
		int numeroEscopoAtual = 0;
		vector<map<string, DADOS_VARIAVEL>*> pilhaDeMapas(0);
		map<string, DADOS_VARIAVEL> *mapaDeContexto;
		
		void inicializarMapaDeContexto();
		bool incluirNoMapa(string, string);
		bool atualizarNoMapa(DADOS_VARIAVEL, int escopo = numeroEscopoAtual);
		bool variavelJaDeclarada(string, bool varrerEscopo = true, int escopo = numeroEscopoAtual);
		DADOS_VARIAVEL recuperarDadosVariavel(string, int escopo = numeroEscopoAtual);
		
		//escopo
		void aumentarEscopo();
		void empilha(map<string, DADOS_VARIAVEL>*);
		void diminuirEscopo();
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
		
		
		void inicializarMapaDeContexto()
		{
			map<string, DADOS_VARIAVEL> *mapa = (map<string, DADOS_VARIAVEL>*) malloc(sizeof(map<string, DADOS_VARIAVEL>));
			mapa->clear();
			pilhaDeMapas.push_back(mapa);
		}
		
		void aumentarEscopo(){
			map<string, DADOS_VARIAVEL> *novoMapa = (map<string, DADOS_VARIAVEL>*) malloc(sizeof(map<string, DADOS_VARIAVEL>));
			numeroEscopoAtual = numeroEscopoAtual+1;
			novoMapa->clear();
			pilhaDeMapas.push_back(novoMapa);
			
		}
		
		void diminuirEscopo(){
			numeroEscopoAtual = numeroEscopoAtual-1;
			pilhaDeMapas.pop_back();//desempilha
			
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
				
				pilhaDeMapas[numeroEscopoAtual]->insert(pair<string,DADOS_VARIAVEL>(nome,variavel));
				return true;
			}
			return false;
		}
		
		bool atualizarNoMapa(DADOS_VARIAVEL variavel, int escopo)
		{
			
			if(variavelJaDeclarada(variavel.nome, true, escopo))
			{
				if(mapaDeContexto->at(variavel.nome).tipo == "")
				{
					mapaDeContexto->at(variavel.nome).tipo = variavel.tipo;
					return true;
				}
			}
			return false;
		}
		
		bool variavelJaDeclarada(string nome, bool varrerEscopo, int escopo)
		{
			//ponto de parada
			if(escopo < 0)
				return false;
			//variavel que vai manter qual foi o ultimo mapa acessado
			mapaDeContexto = pilhaDeMapas[escopo];
			if(varrerEscopo)
			{
				nome = adicionaPrefixo(nome);

				//operador curto circuitado para buscar a variavel nos mapas recursivamente
				return (mapaDeContexto->count(nome) > 0) || variavelJaDeclarada(nome, varrerEscopo, escopo - 1);
			}
			else
			{
				nome = adicionaPrefixo(nome);
				return mapaDeContexto->count(nome) > 0;
			}
		}
		
		DADOS_VARIAVEL recuperarDadosVariavel(string nome, int escopo)
		{
			DADOS_VARIAVEL retorno;
			nome = adicionaPrefixo(nome);
			if(variavelJaDeclarada(nome, true, escopo))
			{
				 return mapaDeContexto->at(nome);
			}
		}
		
	}
	
	namespace DeclaracaoProvisoriaInferenciaTipo
	{
		using namespace MapaDeContexto;
	
		#define constante_subst_tipo_declaracao_variavel "//#TIPOP_VAR_\t_\t#"
		#define constante_sufixo_escopo "SCOPE"
		#define slotIdVar "\t"
		map<string, string> mapaSubstituicaoDeTipoProvisorio;
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string);
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string);
		void adcionarDefinicaoDeTipo(string, string, int, int);
		string substituirTodasAsDeclaracoesProvisorias(string);
		
		
		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string id)
		{
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string separador = slotIdVar;
			string idPrefixado = adicionaPrefixo(id);
			//primeiro insere o nome da variavel no primeiro slot e depois adiciona o numero do escopo no segundo slot
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(numeroEscopoAtual));
			mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = " ";
			return tipoProvisorio + " " + idPrefixado + ";\n";
		}
			
		void adcionarDefinicaoDeTipo(string id, string tipo, int tamanho, int escopo = numeroEscopoAtual)
		{
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string idPrefixado = adicionaPrefixo(id);
			string separador = slotIdVar;
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
		
			//verificação a mais inserida pq havia problema na hora de definir o tipo de uma variavel global
			//pq o escopo da variavel global é 0 mas o C++ só aceita definição de valor de variavel global em algum escopo interno
			//então na hora de substituir o escopo é 1, mas deveria ser 0 ... então essa busca acha o lugar correto
			if(mapaSubstituicaoDeTipoProvisorio.find(tipoProvisorio) != mapaSubstituicaoDeTipoProvisorio.end()){
				while(escopo > 0){
					metadata = recuperarDadosVariavel(id, escopo);
					escopo = metadata.escopo;
					if(metadata.tipo == "")
					{
						metadata.tipo = tipo;
						atualizarNoMapa(metadata, escopo);
						break;
					}			
				}
				constanteMarcacao = constante_subst_tipo_declaracao_variavel;
				
				tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
				sufixoEscopo = constante_sufixo_escopo;
				tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
			}
				
			if(tipo == constante_tipo_string)
			{
				int tamanho = 0;
				string charArray = "char " + idPrefixado + "[" + to_string(tamanho) + "]";

				mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = charArray;
			}
			else
			{
				mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = tipo;
			}
				
		}
		
		string substituirTodasAsDeclaracoesProvisorias(string declaracoes)
		{
			for(map<string, string>::iterator it=mapaSubstituicaoDeTipoProvisorio.begin();it!=mapaSubstituicaoDeTipoProvisorio.end(); ++it)
			{
				string key = it->first;
				string value = it->second;
						
				int pos = declaracoes.find(key);
				if(pos >= 0)
				{	
					
					/*infelizmente não tem como fazer verificação com a string, pois o value não é constante_tipo_string
					 e sim uma combinação do nome da váriável e seu respectivo tamanho. 
					Por isso a verificação de todos os outros tipos em lugar disso.*/
					if(value == constante_tipo_inteiro || value == constante_tipo_flutuante || value == constante_tipo_caracter || value == constante_tipo_booleano)
					{
						declaracoes.replace(pos, key.length(), value);
					}
					
					else
					{
						//-8 para eliminar o char    [*];
						declaracoes.replace(pos, key.length() + value.length() -8  + 1, value);
					}
					mapaSubstituicaoDeTipoProvisorio[key] = "";
					
				}
					
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

