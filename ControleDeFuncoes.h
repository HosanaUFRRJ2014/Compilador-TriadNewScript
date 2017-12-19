#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;
using namespace ControleDeVariaveis;

namespace ControleDeFuncoes
{
	struct BODY{
		string traducaoDeclaracaoDeVariaveis;
		string traducao;
		map<string, int> qtdDeRetornosDeTipos;
	};

	struct FUNCTION{
		map<string, DADOS_VARIAVEL> parametros;
		map<string, DADOS_VARIAVEL> vvariaveisDeRetorno;
		BODY corpo;
		string nomeDaFuncao;
		string label;
		int escopoDeDefinicao;
		int qtdCombinacoesParametros;
		vector<string>tiposDeRetorno;
		vector<string>variaveisDeRetorno;
		string nomeVariavelDeRetorno;
	};

	string gerarNomePadraoFuncao();
	string funcaoEmConstrucao();

	map<string, FUNCTION> mapaDeDadosDasFuncoes;
	map<string, string> dicionarioDeinonimosDasFuncoes;
	vector<string> pilhaFuncoesEmCriacao(0);
	vector<bool> inferirTipoRetorno(0);

	string nome_funcao_invocadora = "invocarFuncoes";

	string criarFuncao(string nomeFuncao = "")
	{
		FUNCTION f;
		string nomeTraducao = gerarNomePadraoFuncao();
		f.nomeDaFuncao = nomeTraducao;
		//acessando do namespace de variaveis pois sempre será no escopo atual
		f.escopoDeDefinicao = numeroEscopoAtual;
		f.label = nomeFuncao;
		pilhaFuncoesEmCriacao.push_back(f.nomeDaFuncao);
		mapaDeDadosDasFuncoes.insert(pair<string,FUNCTION>(f.nomeDaFuncao,f));
		dicionarioDeinonimosDasFuncoes.insert(pair<string,string>(nomeFuncao,f.nomeDaFuncao));
		dicionarioDeinonimosDasFuncoes.insert(pair<string,string>(f.nomeDaFuncao,f.nomeDaFuncao));
		return f.nomeDaFuncao;
	}

	string gerarLabelRetornosFuncao()
	{
		static int num = 0;
		num++;
		string temp = "retornoDeFuncao";

		string numInt = to_string(num);
		return temp + numInt;
	}

	void adicionarParametro(string nomeParametro, string tipo, int tamanho = 0, bool ehDinamica = true)
	{
		DADOS_VARIAVEL d;
		d.nome = nomeParametro;
		d.tipo = tipo;
		if(tipo == constante_tipo_string && !ehDinamica){
			d.tamanho = tamanho + 1;
			d.ehDinamica = ehDinamica;
		}
		string nomeFuncao = funcaoEmConstrucao();
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0)
			mapaDeDadosDasFuncoes.at(nomeFuncao).parametros.insert(pair<string,DADOS_VARIAVEL>(d.nome,d));
	}

	string funcaoEmConstrucao()
	{
		if(pilhaFuncoesEmCriacao.size() > 0)
			return pilhaFuncoesEmCriacao.back();
		return "";
	}

	string gerarNomePadraoFuncao()
	{
		static int num = 0;
		num++;
		string temp = "funcaoDoUsuario";

		string numInt = to_string(num);
		return temp + numInt;
	}

	bool adicionarTipoDeRetorno(string tipo, bool verificarInferencia = true, int tamanho = 0, bool ehDinamica = true)
	{
		string nomeFuncao = funcaoEmConstrucao();
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0)
		{
			if(verificarInferencia && !inferirTipoRetorno.back())
			{
				return true;
			}
			DADOS_VARIAVEL d;
			d.nome = gerarLabelRetornosFuncao();
			d.nomeTraducao = d.nome;
			d.tipo = tipo;
			d.ehDinamica = ehDinamica;
			if(tipo == constante_tipo_string){
				d.tamanho = tamanho;
				tipo = tipo + "(" + to_string(tamanho) + ")";
			}

			mapaDeDadosDasFuncoes.at(nomeFuncao).vvariaveisDeRetorno.insert(pair<string, DADOS_VARIAVEL>(d.nome, d));
			mapaDeDadosDasFuncoes.at(nomeFuncao).tiposDeRetorno.push_back(tipo);
			return true;
		}
		return false;
	}

	void imprimirTodosOsParametros()
	{
		string nomeFuncao = funcaoEmConstrucao();
		FUNCTION f;
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0)
			f = mapaDeDadosDasFuncoes.at(nomeFuncao);

		cout << endl;
		cout << "nome da funcao: " << nomeFuncao << endl;
		for(map<string, DADOS_VARIAVEL>::iterator it=f.parametros.begin();it!=f.parametros.end(); ++it)
		{
			string key = it->first;
			DADOS_VARIAVEL value = it->second;
			cout << "nome parametro: " << key  << " === tipo parametro: " << value.tipo << endl;
		}
		cout << endl;
	}

	void registrarParametrosDaFuncao()
	{
		string nomeFuncao = funcaoEmConstrucao();
		FUNCTION f;
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0)
		{
			f = mapaDeDadosDasFuncoes.at(nomeFuncao);
			if(f.tiposDeRetorno.size() > 0)
				inferirTipoRetorno.push_back(false);
			else
				inferirTipoRetorno.push_back(true);

			for(map<string, DADOS_VARIAVEL>::iterator it=f.parametros.begin();it!=f.parametros.end(); ++it)
			{
				string key = it->first;
				DADOS_VARIAVEL value = it->second;

				incluirNoMapa(value.nome, value.tamanho, value.tipo);
				bool ehDinamica = value.ehDinamica;
				mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key] = recuperarDadosVariavel(value.nome);
				mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key].ehDinamica = ehDinamica;
				mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key].escopo = numeroEscopoAtual;
				atualizarNoMapa(mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key]);

				string nome = mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key].nomeTraducao;
				string tipo = mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key].tipo;
				if(tipo == constante_tipo_string && !ehDinamica)
				{
					string t = "char " + nome + "[" + to_string(mapaDeDadosDasFuncoes.at(nomeFuncao).parametros[key].tamanho) + "]";
					mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis += t + ", ";
				}
				else
				{
					tipo = tipoCodigoIntermediario(tipo);
					mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis += tipo + " " + nome + ", ";
				}

			}
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis.pop_back();
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis.pop_back();
		}

	}

	void adcionarTraducaoDeclaracaoAoCorpoDaFuncao(string blocoDecVar)
	{
		string nomeFuncao = funcaoEmConstrucao();
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0)
		{
			vector<string> tipos = mapaDeDadosDasFuncoes.at(nomeFuncao).tiposDeRetorno;
			if(tipos.size() > 0)
			{
				int contador = 1;

				for(map<string, DADOS_VARIAVEL>::iterator it=mapaDeDadosDasFuncoes.at(nomeFuncao).vvariaveisDeRetorno.begin();it!=mapaDeDadosDasFuncoes.at(nomeFuncao).vvariaveisDeRetorno.end(); ++it, ++contador)
				{
					string tipo = it->first;
					DADOS_VARIAVEL d = it->second;

					string declaracao = "";
					if(!d.ehDinamica){
						declaracao = "char " + d.nome + "[" + to_string(d.tamanho) + "]; //reorno" + to_string(contador) + " tipo " + d.tipo + "\n";
					}
					else{
						declaracao = tipoCodigoIntermediario(d.tipo) + " " + d.nome + "; //reorno" + to_string(contador) + " tipo " + d.tipo + "\n";
					}

					mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis += declaracao;
					mapaDeDadosDasFuncoes.at(nomeFuncao).variaveisDeRetorno.push_back(d.nome);
				}
			}
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis += blocoDecVar;
		}
	}


	void adcionarTraducaoAoCorpoDaFuncao(string blocoTraducao)
	{
		string nomeFuncao = funcaoEmConstrucao();
		if(mapaDeDadosDasFuncoes.count(nomeFuncao) > 0){
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducao = "void " + nomeFuncao + "(";
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducao += mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis + ")\n{\n";
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducaoDeclaracaoDeVariaveis = "";
			mapaDeDadosDasFuncoes.at(nomeFuncao).corpo.traducao += blocoTraducao + "}";
		}

	}

	void finalizarCriacaoFuncao()
	{
		pilhaFuncoesEmCriacao.pop_back();
		inferirTipoRetorno.pop_back();
	}

	string definicoesDeFuncoes()
	{
		string traducaoFuncoes = "";
		/*string traducaoCaller;
		traducaoCaller = "void "+ nome_funcao_invocadora + "(" + tipoCodigoIntermediario(constante_tipo_funcao) + " nomeFuncao)\n";
		traducaoCaller += "{\n";*/

		for(map<string, FUNCTION>::iterator it=mapaDeDadosDasFuncoes.begin();it!=mapaDeDadosDasFuncoes.end(); ++it){
			string key = it->first;
			FUNCTION value = it->second;
			/*traducaoCaller += "\tif(nomeFuncao == \"" + key + "\")\n";
			traducaoCaller +=	"\t\treturn " + key + "();\n\n";*/


			traducaoFuncoes += value.corpo.traducaoDeclaracaoDeVariaveis + "\n";
			traducaoFuncoes += value.corpo.traducao + "\n";
		}
		//traducaoCaller += "}\n\n\n";

		return traducaoFuncoes + "\n"; //+ traducaoCaller;
	}

	string recuperarNomeDaFuncaoPorLabel(string label)
	{
		 if(dicionarioDeinonimosDasFuncoes.count(label) > 0)
		 {
			return dicionarioDeinonimosDasFuncoes.at(label);
		 }
		 return "";
	}

	bool existeFuncao(string nomeFuncao)
	{
		string nome = recuperarNomeDaFuncaoPorLabel(nomeFuncao);

		if(nome != "" && mapaDeDadosDasFuncoes.count(nome) > 0)
			return true;
		return false;
	}

	string tratarVerificacaoDeParametroString(string tipoEnviado, DADOS_VARIAVEL param, FUNCTION f, int contador){
		int pos = tipoEnviado.find("(");
		int tamanho = 0;

		pos++;
		int tamNumero = tipoEnviado.find(")") - pos;
		tamanho = stoi(tipoEnviado.substr(pos, tamNumero));

		if(param.tipo != constante_tipo_string || param.tamanho-1 != tamanho)
		{
			string p5 = param.tipo;

			if(p5 == constante_tipo_string && param.tamanho != 0)
				p5 += "("+ to_string(param.tamanho-1) +")";

			string p[5] = {recuperarNome(f.label), to_string(contador), param.nome, tipoEnviado, p5};
		 	return MensagensDeErro::montarMensagemDeErro(MSG_ERRO_PARAMETRO_ATRIBUIDO_POSSUI_TIPO_DIFERENTE,p,5);

		}

		return "";
	}

	bool verificacaoDeParametros(string nomeFuncao, string parametrosComTipo, string* msgErro)
	{
		vector<string> params;
		split(params, parametrosComTipo, is_any_of(";"));
		FUNCTION f;
		if(existeFuncao(nomeFuncao))
			f = mapaDeDadosDasFuncoes.at(recuperarNomeDaFuncaoPorLabel(nomeFuncao));

		vector<string>::iterator it=params.begin();
		map<string, DADOS_VARIAVEL>::iterator itf=f.parametros.begin();
		int contador = 1;
		for( ;it!=params.end() && itf!=f.parametros.end();	++it, ++itf, ++contador)
		{
			vector<string>nomeTipo;
			split(nomeTipo, *it, is_any_of(":"));
			int pos = nomeTipo.at(1).find("(");
			if(pos > 0 && pos < nomeTipo.at(1).length()){
				string msg = tratarVerificacaoDeParametroString(nomeTipo.at(1), itf->second, f, contador);
				if(msg != ""){
					(*msgErro) = msg;
					return false;
				}
			}
			else if(nomeTipo.at(1) != itf->second.tipo)
			{
				string p[5] = {recuperarNome(f.label), to_string(contador), itf->second.nome, nomeTipo.at(1), itf->second.tipo};
				(*msgErro) = MensagensDeErro::montarMensagemDeErro(MSG_ERRO_PARAMETRO_ATRIBUIDO_POSSUI_TIPO_DIFERENTE,p,5);
				return false;
			}
//			cout << "TIPO ENVIADO: " << nomeTipo.at(1) << " ==== tipo que deveria: " << itf->second.tipo << endl;
		}

		if(contador -1 != f.parametros.size())
		{
			string p[3] = {recuperarNome(f.label), to_string(contador-1), to_string(f.parametros.size())};
			(*msgErro) = MensagensDeErro::montarMensagemDeErro(MSG_ERRO_QUANTIDADE_DE_PARAMETROS_INCOPATiVEL, p, 3);
			return false;
		}
		return true;

	}

	string gerarTraducaoChamadaDaFuncao(string nomeFuncao, string parametros)
	{
		vector<string> params;
		split(params, parametros, is_any_of(";"));
		FUNCTION f;
		if(existeFuncao(nomeFuncao))
			f = mapaDeDadosDasFuncoes.at(recuperarNomeDaFuncaoPorLabel(nomeFuncao));

		vector<string>::iterator it=params.begin();
		map<string, DADOS_VARIAVEL>::iterator itf=f.parametros.begin();

		string traducao = "\t" + recuperarNomeDaFuncaoPorLabel(nomeFuncao) + "(";

		for( ;it!=params.end() && itf!=f.parametros.end();	++it, ++itf)
		{
			vector<string>nomeTipo;
			split(nomeTipo, *it, is_any_of(":"));

			traducao += nomeTipo.at(0) + ", ";
		}
		traducao.pop_back();
		traducao.pop_back();

		traducao += ");\n";

		return traducao;
	}

}
