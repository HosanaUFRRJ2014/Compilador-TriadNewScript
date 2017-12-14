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
		string tipo; //Tipo da variável.
		string nome; //Nome que o usuário deu a variável no programa.
		string nomeTraducao; //Nome da variável no código intermediário.
		int tamanho = 0; //Para string
		bool ehDinamica = false; //Para string
		int escopo;
		vector<string> pilhaTamanhoDimensoesArray; //Para arrays
		
	};


	namespace MapaDeContexto
	{
		#define prefixo_variavel_usuario "VARUSER_"
//		#define constante_TamanhoInicialPilha 5
		int numeroEscopoAtual = 0;
		vector<map<string, DADOS_VARIAVEL>*> pilhaDeMapas(0);
		map<string, DADOS_VARIAVEL> *mapaDeContexto;
		map<string, string> dicionarioNomeTraducaoParaNome;

		void inicializarMapaDeContexto();
		bool incluirNoMapa(string,int, string);
		bool atualizarNoMapa(DADOS_VARIAVEL, int escopo = numeroEscopoAtual);
		bool variavelJaDeclarada(string, bool varrerEscopo = true, int escopo = numeroEscopoAtual);
		DADOS_VARIAVEL recuperarDadosVariavel(string, int escopo = numeroEscopoAtual);
		string gerarNomeTraducaoVariavelUsuario();
		string recuperarNomeTraducao(string nome, int escopo = numeroEscopoAtual);
		string recuperarNome(string nomeTraducao, int escopo = numeroEscopoAtual);


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
			//map<string, DADOS_VARIAVEL> *mapa = (map<string, DADOS_VARIAVEL>*) malloc(sizeof(map<string, DADOS_VARIAVEL>));
			//mapa->clear();
			map<string, DADOS_VARIAVEL> *mapa = new map<string, DADOS_VARIAVEL>();
			pilhaDeMapas.push_back(mapa);
		}

		void aumentarEscopo(){
			//map<string, DADOS_VARIAVEL> *novoMapa = (map<string, DADOS_VARIAVEL>*) malloc(sizeof(map<string, DADOS_VARIAVEL>));
			map<string, DADOS_VARIAVEL>* novoMapa = new map<string, DADOS_VARIAVEL>();

			DADOS_VARIAVEL abc;

			numeroEscopoAtual = numeroEscopoAtual+1;
//			cout << novoMapa->size();
//			novoMapa->clear();
			pilhaDeMapas.push_back(novoMapa);

		}

		void diminuirEscopo(){
			numeroEscopoAtual = numeroEscopoAtual-1;
			pilhaDeMapas.pop_back();//desempilha

		}

		string adicionaPrefixo(string nome)
		{
			if(nome.find(prefixo_variavel_usuario) != 0)
				nome = prefixo_variavel_usuario + nome;
			return nome;
		}

		bool incluirNoMapa(string nome, int tamanho, string tipo = "")
		{
			nome = adicionaPrefixo(nome);
			if(!variavelJaDeclarada(nome, false))
			{
				DADOS_VARIAVEL variavel;
				variavel.nome = nome;
				variavel.tamanho = tamanho;
				variavel.tipo = tipo;
				variavel.escopo = numeroEscopoAtual;
				variavel.nomeTraducao = gerarNomeTraducaoVariavelUsuario();
				dicionarioNomeTraducaoParaNome.insert(pair<string, string>(variavel.nomeTraducao, nome));
				/*cout << variavel.nome;
				cout << variavel.ehDinamica;*/
				pilhaDeMapas[numeroEscopoAtual]->insert(pair<string,DADOS_VARIAVEL>(nome,variavel));
				return true;
			}
			return false;
		}

		bool atualizarNoMapa(DADOS_VARIAVEL variavel, int escopo)
		{

			if(variavelJaDeclarada(variavel.nome, true, escopo))
			{
				mapaDeContexto->at(variavel.nome).tamanho = variavel.tamanho;
				mapaDeContexto->at(variavel.nome).ehDinamica = variavel.ehDinamica;
				if(mapaDeContexto->at(variavel.nome).tipo == "")
				{
					mapaDeContexto->at(variavel.nome).tipo = variavel.tipo;
					return true;
				}

				/*if(mapaDeContexto->at(variavel.nome).tipo == constante_tipo_string){
					mapaDeContexto->at(variavel.nome).ehDinamica = variavel.ehDinamica;
				}*/
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

			return retorno;
		}

		string gerarNomeTraducaoVariavelUsuario(){
			static int num = 0;
			num++;
			string temp = "variavelDoUsuario";

			string numInt = to_string(num);
			return temp + numInt;
		}

		string recuperarNomeTraducao(string nome, int escopo){
			if(variavelJaDeclarada(nome, true, escopo))
			{
				return recuperarDadosVariavel(nome, escopo).nomeTraducao;
			}
			return nome;
		}

		string recuperarNome(string nomeTraducao, int escopo)
		{
			//operador curto circuitado para buscar a variavel nos mapas recursivamente
			return dicionarioNomeTraducaoParaNome.at(nomeTraducao);
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

		void adicionarDefinicaoDeTipo(string, string, int,bool, int);
		string substituirTodasAsDeclaracoesProvisorias(string);
		string montarTagTipoProvisorio(string, int);
		string recuperarIdPelaTag(string);

		string montarTagTipoProvisorio(string id, int escopo){
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string separador = slotIdVar;
			string idPrefixado = adicionaPrefixo(id);
			//primeiro insere o numero do escopo da variavel no primeiro slot e depois adiciona o nome da variavel no segundo slot
			string sufixoEscopo = constante_sufixo_escopo;
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), idPrefixado);
			return tipoProvisorio;
		}

		string construirDeclaracaoProvisoriaDeInferenciaDeTipo(string id)
		{
		/*
			string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string separador = slotIdVar;
			string idPrefixado = adicionaPrefixo(id);
			//primeiro insere o nome da variavel no primeiro slot e depois adiciona o numero do escopo no segundo slot
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(numeroEscopoAtual));
			*/
			//string tipoProvisorio = montarTagTipoProvisorio(id, numeroEscopoAtual);

			id = adicionaPrefixo(id);
			string tipoProvisorio = recuperarNomeTraducao(id, numeroEscopoAtual);
			mapaSubstituicaoDeTipoProvisorio[tipoProvisorio] = " ";
			return tipoProvisorio + " " + tipoProvisorio + "; //" + id + "\n";
		}


		//void adicionarDefinicaoDeTipo(string id, string tipo, int tamanho,  int escopo = numeroEscopoAtual)
		void adicionarDefinicaoDeTipo(string id, string tipo, int tamanho, bool ehDinamico, int escopo = numeroEscopoAtual)
		{
			/*string constanteMarcacao = constante_subst_tipo_declaracao_variavel;
			string idPrefixado = adicionaPrefixo(id);
			string separador = slotIdVar;
			string tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
			string sufixoEscopo = constante_sufixo_escopo;
			tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));*/
			id = adicionaPrefixo(id);

			string tipoProvisorio = recuperarNomeTraducao(id, escopo);

			//verificação a mais inserida pq havia problema na hora de definir o tipo de uma variavel global
			//pq o escopo da variavel global é 0 mas o C++ só aceita definição de valor de variavel global em algum escopo interno
			//então na hora de substituir o escopo é 1, mas deveria ser 0 ... então essa busca acha o lugar correto
			//cout << "label5.1.1\n";
			DADOS_VARIAVEL metadata;
			if(mapaSubstituicaoDeTipoProvisorio.find(tipoProvisorio) == mapaSubstituicaoDeTipoProvisorio.end()){

				while(escopo >= 0){
			//		cout << "label5.1.1.1\n";
					metadata = recuperarDadosVariavel(id, escopo);
			//		cout << "label5.1.1.2\n";
					escopo = metadata.escopo;
					if(metadata.tipo == "")
					{
			//			cout << "label5.x\n";
						metadata.tipo = tipo;
						atualizarNoMapa(metadata, escopo);
						break;
					}
				}
				/*
				constanteMarcacao = constante_subst_tipo_declaracao_variavel;

				tipoProvisorio = constanteMarcacao.replace(constanteMarcacao.find(separador), separador.length(), idPrefixado);
				sufixoEscopo = constante_sufixo_escopo;
				tipoProvisorio = tipoProvisorio.replace(tipoProvisorio.find(separador), separador.length(), sufixoEscopo + to_string(escopo));
				*/
				tipoProvisorio = recuperarNomeTraducao(id, escopo);
			}

			//cout << "label5.1.2\n";

			if(tipo == constante_tipo_string)
			{
				string charArray;
				if(ehDinamico)
					charArray = "char  *  " + tipoProvisorio;

				else
					charArray = "char " + tipoProvisorio + "[" + to_string(tamanho) + "]";

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

				if(value == "") continue;

				int pos = declaracoes.find(key);

				if(pos >= 0)
				{

					/*infelizmente não tem como fazer verificação com a string, pois o value não é constante_tipo_string
					 e sim uma combinação do nome da váriável e seu respectivo tamanho.
					Por isso a verificação de todos os outros tipos em lugar disso.*/
					if(value == " "){
						string id = recuperarNome(key);
						string prefix = prefixo_variavel_usuario;
						string params[1] = {id.replace(0, prefix.length(), "")};
						MensagensDeErro::yywarning(MensagensDeErro::montarMensagemDeErro(MSG_WARINING_VARIAVEL_DECLARADA_NAO_UTILIZADA ,params, 1));

						value = constante_tipo_inteiro;
					}

					string intBarrat = constante_tipo_inteiro;
					intBarrat = "\t" + intBarrat;

					if(value == constante_tipo_inteiro || value == constante_tipo_flutuante || value == constante_tipo_caracter || value == constante_tipo_booleano || value == intBarrat)
					{
						declaracoes.replace(pos, key.length(), value);
					}
					else
					{

						//-7 para eliminar o char    [*] da string estática
						declaracoes.replace(pos, key.length() + value.length() -7, value);
					}
					mapaSubstituicaoDeTipoProvisorio[key] = "";

				}
			}

// tinhas posto o clear pra ajudar no gerenciamento de chaves repetidas... mas deu problema
//			mapaSubstituicaoDeTipoProvisorio.clear();
			if(numeroEscopoAtual == 0 && mapaSubstituicaoDeTipoProvisorio.size() > 0){

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
	using namespace DeclaracaoProvisoriaInferenciaTipo;

}
