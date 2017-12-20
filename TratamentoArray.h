#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <stdarg.h>

using namespace Atributos;
using namespace ControleDeVariaveis;
using namespace ConstanteTipos;
using namespace EntradaESaida;

namespace TratamentoArray
{
	namespace PilhaTamanhoDimensoesArray{
		//Pilha global para obter os valores durante o parser do código e depois passar para a pilha de DADOS_VARIAVEL associado ao Array.
		vector<string> pilhaTamanhoDimensoesArray(0);
		vector<pair<string,bool>> valoresReaisDim(0);
		vector<string> labelsDosElementosLidos(0);

		void adicionarTamanhoDimensoesArray(string,vector<string>*,bool);
		string obterElementoTamanhoDimensoesArray(int,vector<string>*,bool);
		void resetarTamanhoDimensoesArray();
		pair<string,bool> obterDimInteiraArray(int,vector<pair<string,bool>> *,bool);
		void adicionarValoresReaisDim(string, bool,vector<pair<string,bool>> *,bool);

		void adicionarTamanhoDimensoesArray(string indiceDimensao,vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){

			if(!acaoPilhaVar)
				pilhaTamanhoDimensoesArray.push_back(indiceDimensao);
			else
				pilhaDadosVar->push_back(indiceDimensao);
		}

		string obterElementoTamanhoDimensoesArray(int ind,vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){

			if(!acaoPilhaVar)
			{
				if(!(ind < 0 && ind >= pilhaTamanhoDimensoesArray.size()))
					return pilhaTamanhoDimensoesArray.at(ind);
				else
					cout << "ERRO NO ACESSO AO ÍNDICE" << endl << endl;
			}
			else
			{
				if(!(ind < 0 && ind >= pilhaDadosVar->size()))
					return pilhaDadosVar->at(ind);
				else
					cout << "ERRO NO ACESSO AO ÍNDICE" << endl << endl;
			}
		}

		void resetarTamanhoDimensoesArray(){
			pilhaTamanhoDimensoesArray.clear();
			valoresReaisDim.clear();
			labelsDosElementosLidos.clear();
		}

		pair<string,bool> obterDimInteiraArray(int ind,vector<pair<string,bool>> *dadosVar = NULL,bool acaoDadosVar = false){

			if(!acaoDadosVar)
			{
				if(!(ind < 0 && ind >= valoresReaisDim.size()))
					return valoresReaisDim.at(ind);
				else
					cout << "ERRO NO ACESSO AO ÍNDICE" << endl << endl;
			}
			else
			{
				if(!(ind < 0 && ind >= dadosVar->size()))
					return dadosVar->at(ind);
				else
					cout << "ERRO NO ACESSO AO ÍNDICE" << endl << endl;
			}
		}

		void adicionarValoresReaisDim(string dim, bool ehInteira,vector<pair<string,bool>> *dadosVar = NULL,bool acaoDadosVar = false){

			pair<string,bool> novoElem;
			novoElem.first = dim;
			novoElem.second = ehInteira;

			if(!acaoDadosVar)
				valoresReaisDim.push_back(novoElem);
			else
				dadosVar->push_back(novoElem);
		}

	}

	namespace TraducaoArray{

		#define tag_erro_index "INDEX_FORA_LIMITE"
		#define tag_erro_alocacao "ALOCACAO_NEG_ZERO" //DEFINE NOVA
		//#define msg_fim_execucao_array "\"Acesso ou alocação de memória indevida (Memory fault).\""
		#define msg_fim_execucao_array_alocacao "\"Alocação de memória indevida (Memory fault).\"" //DEFINE NOVA
		#define msg_fim_execucao_array_acesso "\"Acesso a memória indevido (Memory fault).\"" //DEFINE NOVA

		string fimCodInter = "\tFIMCODINTER:\n";
		string tab = "\t";
		//string traducaoFree = "\n\n" + tab + tag_erro_index + ":\n" + constroiPrint(msg_fim_execucao_array) + fimCodInter;
		string traducaoFree = "\n\n" + tab + tag_erro_index + ":\n" + constroiPrint(msg_fim_execucao_array_acesso) +
													"\n" + tab + tag_erro_alocacao + ":\n" + constroiPrint(msg_fim_execucao_array_alocacao) + fimCodInter;
		bool acessoArray = false;
		string tipoArray = "";
		string tipoArrayCodInterm = "";
		int count_dim = 0;
		DADOS_VARIAVEL dadosArray;
		bool atribuicaoArrayEsq = false;

		void resetarVarGlobaisArray();
		void definicaoTipoArray(string, string);
		pair<string,string> traducaoCriacaoArray(string,vector<string>*,int,bool);
		pair<string,string> traducaoCalculoIndiceArray(vector<string>,vector<string>,ATRIBUTOS *,vector<pair<string,bool>>,vector<pair<string,bool>>,bool);
		void adicionarTraducaoComandosFree(string);
		string retornarTraducaoFrees();

		string traducaoCalculoIndiceArray(); //...
		string traducaoArrayCodIntermediario(int, ...); //...

		void resetarVarGlobaisArray(){
			tipoArray = "";
			tipoArrayCodInterm = "";
			acessoArray = false;
			atribuicaoArrayEsq = false;
			//count_dim = 0;
		}

		void definicaoTipoArray(string tipo, string tipoCodInterm){
			tipoArray = tipo;
			tipoArrayCodInterm = tipoCodInterm;
		}

		pair<string,string> traducaoCriacaoArray(string varUser,vector<string> *dim = NULL,int tamArray = -1,bool criacaoPreDefinida = false){

			pair<string,string> traducaoFinal; //first == traducaoDeclaracao ; second == traducao
			string traducao = "";
			string aux_label;

			traducaoFinal.first = "";
			traducaoFinal.second = "";

			if(criacaoPreDefinida)
			{
					string label_dim_vetor = TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(0);
					//string tam_vetor = obterDimInteiraArray(0).first;

					string espaco = " ";

					traducaoFinal.first = constante_tipo_inteiro + espaco + label_dim_vetor + ";\n";
					traducaoFinal.second = "\t" + label_dim_vetor + " = " + to_string(tamArray) + ";\n";

					traducaoFinal.second = traducaoFinal.second + "\t" + varUser + " = " + "(" + tipoArrayCodInterm + "*) " +
											"malloc(" + label_dim_vetor + " * sizeof(" + tipoArrayCodInterm + "));\n";

					//Atribuir cada label de elementos lida dentro dos colchetes e atribuir a cada indice do vetor correspontende.
					for(int i = 0;i < dim->size();i++)
					{
							traducaoFinal.second = traducaoFinal.second + "\t" + varUser + "[" + to_string(i) + "] = " +
																		TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(i,dim,true) +
																		";\n";
					}
			}
			else if(tamArray == -1)
			{
				string last_label = TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(0,dim,true);

				//for (vector<string>::iterator it = dim.begin(); it != dim.end(); it++)
				for(int pos = 1;pos < dim->size();pos++)
				{
					aux_label = gerarNovaVariavel();
					traducaoFinal.first = traducaoFinal.first + constante_tipo_inteiro + " " + aux_label + ";\n";
					traducaoFinal.second = traducaoFinal.second + "\t" + aux_label + " = " + last_label + " * " +
										TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(pos,dim,true) +
										";\n";
					last_label = aux_label;
				}

				traducaoFinal.second = traducaoFinal.second + "\t" + varUser + " = " + "(" + tipoArrayCodInterm + "*) " +
										"malloc(" + last_label + " * sizeof(" + tipoArrayCodInterm + "));\n";

				//Adicionar o if para verificação em tempo de execução.
				string label_if_index = gerarNovaVariavel();
				string label_cond_if = gerarNovaVariavel();
				traducaoFinal.first = traducaoFinal.first + constante_tipo_inteiro + " " + label_if_index + ";\n" +
										constante_tipo_inteiro + " " + label_cond_if + ";\n";
				traducaoFinal.second = traducaoFinal.second + "\t" + label_if_index + " = " + last_label + " > 0;\n\t" +
										label_cond_if + " = !" + label_if_index + ";\n\t" + "if(" + label_cond_if + ")\n\t\t" +
										"goto " + tag_erro_alocacao + ";\n"; //tag_erro_index
			}
			else
			{
				traducaoFinal.second = traducaoFinal.second + "\t" + varUser + " = " + "(" + tipoArrayCodInterm + "*) " +
										"malloc(" + to_string(tamArray) + " * sizeof(" + tipoArrayCodInterm + "));\n";
			}

			return traducaoFinal;
		}

		void adicionarTraducaoComandosFree(string varUser){
			traducaoFree = traducaoFree + "\t" + "free(" + varUser + ");\n";
		}

		string retornarTraducaoFrees(){
			//traducaoFree = traducaoFree + "\t" + tag_erro_index + ":\n" + constroiPrint(msg_fim_execucao_array);

			return traducaoFree;
		}

		//Cria a tradução do cálculo do índice correspontende do array no código do programa(conversão array --> vetor)
		pair<string,string> traducaoCalculoIndiceArray(vector<string>labelsInd,vector<string>labelsDim,ATRIBUTOS *dolarDolar,
			vector<pair<string,bool>>valRealInd,vector<pair<string,bool>>valRealDim,bool foiCriadoDinamicamente)
		{
			pair<string,string> traducao; //first = tradVar; second = traducao;
			string label_mult,label_add,last_label;

			traducao.first = "";
			traducao.second = "";

			if(foiCriadoDinamicamente || dolarDolar->ehDinamica) //Calcular de forma dinamica
			{
					if(labelsInd.size() > 1)
					{
						label_mult = gerarNovaVariavel();
						traducao.first = traducao.first + constante_tipo_inteiro + " " + label_mult + ";\n";
						traducao.second = traducao.second + "\t" + label_mult + " = " +
											TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(0,&labelsInd,true) +
											" * " +
											TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(1,&labelsDim,true) +
											";\n";
						last_label = label_mult;
					}
					else if(labelsInd.size() == 1)
					{
						label_add = gerarNovaVariavel();
						traducao.first = traducao.first + constante_tipo_inteiro + " " + label_add + ";\n";
						traducao.second = traducao.second + "\t" + label_add + " = " + dolarDolar->label + ";\n";
					}

					for(int pos = 1;pos < labelsInd.size();pos++) //É válido pq o tam deles sempre será igual na lógica.
					{
						if(pos != labelsInd.size() - 1)
						{
							label_mult = gerarNovaVariavel();
							traducao.second = traducao.second + "\t" + label_mult + " = " +
										TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(pos,&labelsInd,true) +
										" * " +
										TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(pos + 1,&labelsDim,true) + ";\n";

							label_add = gerarNovaVariavel();
							traducao.second = traducao.second + "\t" + label_add + " = " + label_mult + " + " + last_label + ";\n";
							traducao.first = traducao.first + constante_tipo_inteiro + " " + label_mult + ";\n" +
											+ constante_tipo_inteiro + " " + label_add + ";\n";
							last_label = label_add;
						}
						else
						{
							label_add = gerarNovaVariavel();
							traducao.second = traducao.second + "\t" + label_add + " = " +
											TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(pos,&labelsInd,true)
											+ " + " + last_label + ";\n";
							traducao.first = traducao.first + constante_tipo_inteiro + " " + label_add + ";\n";
						}
					}
			}
			else //Indice do vetor pode ser calculado em tempo de Compilacao.
			{
					int indice_vetor_cod_interm = 0;
					int mult = 0, add = 0, aux_dim,aux_ind;
					//vector<pair<string,bool>>valRealInd,vector<pair<string,bool>>valRealDim
					//TratamentoArray::PilhaTamanhoDimensoesArray::
					//pair<string,bool> obterDimInteiraArray(int,vector<pair<string,bool>> *,bool);

					if(valRealDim.size() == 1)
					{
						indice_vetor_cod_interm = stoi(TratamentoArray::PilhaTamanhoDimensoesArray::obterDimInteiraArray(0,&valRealInd,true).first);
						label_add = to_string(indice_vetor_cod_interm);
					}
					else
					{
						for(int pos = 0;pos < valRealDim.size();pos++) //vale pq a qtd de indices tem que ser igual ao de dimensoes
						{
							if(pos == valRealDim.size() - 1)
							{
									add = add + stoi(TratamentoArray::PilhaTamanhoDimensoesArray::obterDimInteiraArray(pos,&valRealInd,true).first);
									break;
							}

							aux_ind = stoi(TratamentoArray::PilhaTamanhoDimensoesArray::obterDimInteiraArray(pos,&valRealInd,true).first);
							aux_dim = stoi(TratamentoArray::PilhaTamanhoDimensoesArray::obterDimInteiraArray(pos + 1,&valRealDim,true).first);
							mult = aux_ind * aux_dim;
							add = add + mult;
						}

						label_add = to_string(add);
					}
			}

			dolarDolar->labelIndice = label_add;
			return traducao;

		}

		string traducaoArrayCodIntermediario(int qtd_dim, ...)
		{

			string traducao;
			va_list dimensoes;
			int aux_dim;

			va_start(dimensoes,qtd_dim);

			for(int i = 0;i < qtd_dim;i++)
			{
				aux_dim = va_arg(dimensoes,int);
				//...fazer lógica com as dimensões recebidas.
			}

			va_end(dimensoes);

			return traducao;
		}

	}

	using namespace PilhaTamanhoDimensoesArray;
	using namespace TraducaoArray;

}
