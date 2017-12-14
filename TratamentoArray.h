#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <stdarg.h>

using namespace Atributos;
using namespace MapaTipos;
//using namespace std;

namespace TratamentoArray
{
	
	namespace TraducaoArray{
	
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
	
	namespace PilhaIndiceDimensaoArray{
		vector<string> pilhaIndiceDimensaoArray(0);

		void adicionarIndiceDimensaoArray(string);
		void removerTopoIndiceDimensaoArray();
		bool pilhaIndiceDimensaoArrayVazia();
		string obterTopoIndiceDimensaoArray();
		string obterElementoIndiceDimensaoArray(int);
		int obterDimensaoArray();

		void adicionarIndiceDimensaoArray(ATRIBUTOS *dolardolar,string indiceDimensao){
			pilhaIndiceDimensaoArray.push_back(indiceDimensao);
		}
		
		void removerTopoIndiceDimensaoArray(ATRIBUTOS *dolardolar){
			pilhaIndiceDimensaoArray.pop_back();
		}
		
		bool pilhaIndiceDimensaoArrayVazia(ATRIBUTOS *dolardolar){
			return pilhaIndiceDimensaoArray.empty();
		}
				
		string obterTopoIndiceDimensaoArray(ATRIBUTOS *dolardolar){
			return pilhaIndiceDimensaoArray.at(pilhaIndiceDimensaoArray.size() -1);
		}
		
		string obterElementoIndiceDimensaoArray(ATRIBUTOS* dolardolar,int ind){
			if(!(ind < 0 && ind >= pilhaIndiceDimensaoArray.size()))
				return pilhaIndiceDimensaoArray.at(ind);
			else
				cout << "ERRO NO ACESSO AO ÍNDICE" << endl << endl;
		}
		
		//int obterDimensaoArray(ATRIBUTOS* dolar); 
		
	}
	
	using namespace PilhaIndiceDimensaoArray;
	using namespace TraducaoArray;

}
