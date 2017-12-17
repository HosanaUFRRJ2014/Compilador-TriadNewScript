#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <stdarg.h>

using namespace Atributos;
using namespace ControleDeVariaveis;
using namespace ConstanteTipos;
//using namespace std;

namespace TratamentoArray
{	

	string tipoArray = "";
	string tipoArrayCodInterm = "";
	//int tamVetorArrayCodInterm = -1;
	
	namespace PilhaTamanhoDimensoesArray{
		//Pilha global para obter os valores durante o parser do código e depois passar para a pilha de DADOS_VARIAVEL associado ao Array.
		vector<string> pilhaTamanhoDimensoesArray(0);

		void adicionarTamanhoDimensoesArray(string,vector<string>*,bool);
		void removerTopoTamanhoDimensoesArray(vector<string>*,bool);
		bool pilhaTamanhoDimensoesArrayVazia(vector<string>*,bool);
		string obterTopoTamanhoDimensoesArray(vector<string>*,bool);
		string obterElementoTamanhoDimensoesArray(int,vector<string>*,bool);
		void resetarTamanhoDimensoesArray();
		//int obterDimensaoArray();

		void adicionarTamanhoDimensoesArray(string indiceDimensao,vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){
		
			if(!acaoPilhaVar)
				pilhaTamanhoDimensoesArray.push_back(indiceDimensao);
			else
				pilhaDadosVar->push_back(indiceDimensao);
	
		}
		
		void removerTopoTamanhoDimensoesArray(vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){
		
			if(!acaoPilhaVar)
				pilhaTamanhoDimensoesArray.pop_back();
			else
				pilhaDadosVar->pop_back();
		}
		
		bool pilhaTamanhoDimensoesArrayVazia(vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){
		
			if(!acaoPilhaVar)
				return pilhaTamanhoDimensoesArray.empty();
			else
				return pilhaDadosVar->empty();
		}
				
		string obterTopoTamanhoDimensoesArray(vector<string> *pilhaDadosVar = NULL, bool acaoPilhaVar = false){
		
			if(!acaoPilhaVar)
				return pilhaTamanhoDimensoesArray.at(pilhaTamanhoDimensoesArray.size() -1);
			else
				return pilhaDadosVar->at(pilhaDadosVar->size() -1);
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
		}
		
		//int obterDimensaoArray(ATRIBUTOS* dolar); 
		
	}
	
	namespace TraducaoArray{
	
		string traducaoFree = "\n\n";
	
		void resetarVarGlobaisArray();
		void definicaoTipoArray(string, string);
		pair<string,string> traducaoCriacaoArray(string,vector<string>*,int);
		void adicionarTraducaoComandosFree(string);
		string retornarTraducaoFrees();
		
		string traducaoCalculoIndiceArray(); //...
		string traducaoArrayCodIntermediario(int, ...); //...
	
		void resetarVarGlobaisArray(){
			tipoArray = "";
			tipoArrayCodInterm = "";
			//tamVetorArrayCodInterm = -1;
		}
		
		void definicaoTipoArray(string tipo, string tipoCodInterm){
			tipoArray = tipo;
			tipoArrayCodInterm = tipoCodInterm;
			//tamVetorArrayCodInterm = tamanhoVetor;
		}
				
		/*
		#define qtd_elementos_tarja 5		
		#define tarja_tipo "%%%%%"  //%%%%%

		string substituirTiposArray(string traducao,string label,string tipo){

			string novaTraducao;
			string tarja = tarja_tipo + label;
			int qtd_elem = qtd_elementos_tarja + label.length();
			int indexTipo = traducao.find(tarja);

			while(indexTipo != std::string::npos){
				traducao.replace(indexTipo,qtd_elem,tipo);
				indexTipo = traducao.find(tarja);
			}

			novaTraducao = traducao;
			return novaTraducao;

		}
		
		string traducaoDefinesDimensoes()
		{
			//...

		}
		*/
		
		pair<string,string> traducaoCriacaoArray(string varUser,vector<string> *dim = NULL,int tamArray = -1){
		
			pair<string,string> traducaoFinal; //first == traducaoDeclaracao ; second == traducao 
			string traducao = "";
			string aux_label;
			
			//string last_label = TratamentoArray::PilhaTamanhoDimensoesArray::obterElementoTamanhoDimensoesArray(0,dim,true);
			
			traducaoFinal.first = "";
			traducaoFinal.second = "";
			
			if(tamArray == -1)
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
			return traducaoFree;
		}
	
		string traducaoCalculoIndiceArray()
		{
			//...

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
