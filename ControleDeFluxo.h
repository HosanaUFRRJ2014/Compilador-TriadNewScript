#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>

using namespace std;

namespace ControleDeFluxo
{
	namespace TagsFluxo{
		#define tag_if_fim "FIM_IF"
		#define tag_if_else "IF_TRUE"
		#define tag_while_inicio "INICIO_WHILE"
		#define tag_while_fim "FIM_WHILE"
		#define tag_dowhile_inicio "INICIO_DOWHILE"
		#define tag_dowhile_fim "FIM_DOWHILE"
		#define tag_for_inicio "INICIO_FOR"
		#define tag_for_fim "FIM_FOR"
		#define tag_switch_fim "FIM_SWITCH"
		#define tag_case_inicio "INICIO_CASE"
		#define tag_condicao_case "CONDICAO_CASE"
		#define tag_update_for "UPDATE_FOR"
		//(...)
		
		string gerarNovaTagIf(bool fim);
		string gerarNovaTagWhile(bool fim); 
		string gerarNovaTagDoWhile(bool fim);
		string gerarNovaTagFor(bool fim); 
		string gerarNovaTagUpdateFor();
		pair<string,int> gerarNovaTagSwitch(bool tagCase);

		pair<string,string> gerarNovaTagCondicaoCase();

		
		string criarNovaTag(int *num1,int *num2,string tagCmd1,string tagCmd2,bool fim){

			string numInt, tag;

			if(fim)
			{
				*num1 += 1;
				tag = tagCmd1;
				numInt = to_string(*num1);
			}
			else
			{
				*num2 += 1;
				tag = tagCmd2;
				numInt = to_string(*num2);
			}

			return tag + numInt;

		}
		
		
		
		string gerarNovaTagIf(bool fim){
			static int numFim = 0;
			static int numElse = 0;
			//string tag;
			//string numInt;
			string resultado;
			
			resultado = criarNovaTag(&numFim,&numElse,tag_if_fim,tag_if_else,fim);

			/*
			if(fim)
			{
				numFim++;
				tag = tag_if_fim;
				numInt = to_string(numFim);
			}
			else
			{
				numElse++;
				tag = tag_if_else;
				numInt = to_string(numElse);
			}
			
			return tag + numInt;
			*/
			
			return resultado;
			
		}

		string gerarNovaTagWhile(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			//string tag;
			//string numInt;
			string resultado;
			
			resultado = criarNovaTag(&numFim,&numInicio,tag_while_fim,tag_while_inicio,fim);
			
			/*
			if(fim)
			{
				numFim++;
				tag = tag_while_fim;
				numInt = to_string(numFim);
			}
			else
			{
				numInicio++;
				tag = tag_while_inicio;
				numInt = to_string(numInicio);
			}
	
			return tag + numInt;
			*/
			
			return resultado;
		}

		string gerarNovaTagDoWhile(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			//string tag;
			//string numInt;
			string resultado;
			
			resultado = criarNovaTag(&numFim,&numInicio,tag_dowhile_fim,tag_dowhile_inicio,fim);

			/*
			if(fim)
			{
				numFim++;
				tag = tag_dowhile_fim;
				numInt = to_string(numFim);
			}
			else
			{
				numInicio++;
				tag = tag_dowhile_inicio;
				numInt = to_string(numInicio);
			}
	
			return tag + numInt;
			
			*/
			
			return resultado;
		}

		string gerarNovaTagFor(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			//string tag;
			//string numInt;
			string resultado;
			
			resultado = criarNovaTag(&numFim,&numInicio,tag_for_fim,tag_for_inicio,fim);

			/*
			if(fim)
			{
				numFim++;
				tag = tag_for_fim;
				numInt = to_string(numFim);
			}
			else
			{
				numInicio++;
				tag = tag_for_inicio;
				numInt = to_string(numInicio);
			}
	
			return tag + numInt;
			*/
			
			return resultado;
		}
		
		string gerarNovaTagUpdateFor(){
			static int numUpdate = 0;
			string tag;
			string numInt;

			numUpdate++;
			tag = tag_update_for;
			numInt = to_string(numUpdate);
			
			return tag + numInt;
		}
		

		pair<string,int> gerarNovaTagSwitch(bool tagCase){
			static int numFim = 0;
			static int numCaseInicio = 0;
			string tag;
			string numInt;
			pair<string,int> resultado;
				
			if(tagCase)
			{
				numCaseInicio++;
				tag = tag_case_inicio;
				numInt = to_string(numCaseInicio);
			}
			else
			{
				numFim++;
				tag = tag_switch_fim;
				numInt = to_string(numFim);
			}

			resultado.first = tag + numInt;
			resultado.second = numCaseInicio + 1;
		
			return resultado;
			//return tag + numInt;
		}
		
		pair<string,string> gerarNovaTagCondicaoCase(){
			static int numCondicao = 0;
			string tag;
			string numInt;
			pair<string,string> resultado;

			numCondicao++;
			tag = tag_condicao_case;
			numInt = to_string(numCondicao);
			
			resultado.first = tag + numInt;
			resultado.second = to_string(numCondicao + 1);
			
			return resultado;
		}

	}

	namespace TraducaoControleFluxo{

		//#define qtd_elementos_tarja_tempUSER 5 //.....
		//#define qtd_elementos_tarja_tagFim 5 //**********
		//#define qtd_elementos_tarja_break 5 //**********
		//#define qtd_elementos_tarja_continue 5 //**********
		
		#define qtd_elementos_tarja 5		

		#define tarja_variavel "....."  //.....
		#define tarja_tagFim "*****"  //**********

		#define tarja_break "%%%%%"  //**********
		#define tarja_continue "#####"  //**********

		string substituirVariaveisCase(string traducao, string varUser){

			string novaTraducao;
			int indexVar = traducao.find(tarja_variavel);

			while(indexVar != std::string::npos){
				traducao.replace(indexVar,qtd_elementos_tarja,varUser);
				indexVar = traducao.find(tarja_variavel);
			}

			novaTraducao = traducao;
			return novaTraducao;

		}
		
		/*
		string incluirBreakEContinue(string traducao, string tagInicio, string tagFim, bool ehSwitch)
		{			

			string novaTraducao;
			int index = traducao.find(tarja_break);
			
			//Substituir as tarjas do Break.
			while(index != std::string::npos){
				traducao.replace(index,qtd_elementos_tarja,tagFim);
				index = traducao.find(tarja_break);
			}
			
			if(!ehSwitch) //Switches não suportam continue.
			{
				index = traducao.find(tarja_continue);
				
				//Substituir as tarjas do Continue.
				while(index != std::string::npos){
					traducao.replace(index,qtd_elementos_tarja,tagInicio);
					index = traducao.find(tarja_continue);
				}
			}
			novaTraducao = traducao;

			return novaTraducao; 
		}
		
		bool haBreakNoBloco(string traducao)
		{
			if(traducao.find(tarja_break) != std::string::npos)
				return true;
			else
				return false;
		}

		bool haContinueNoBloco(string traducao)
		{
			if(traducao.find(tarja_continue) != std::string::npos)
				return true;
			else
				return false;
		}
		*/

	}
	
	namespace PilhaControleFluxo{
		vector<string> pilhaTagInicio(0);
		vector<string> pilhaTagFim(0);

		void adicionarTagInicio(string);
		void adicionarTagFim(string);
		void removerTopoTagInicio();
		void removerTopoTagFim();
		string obterTopoPilhaInicio();
		string obterTopoPilhaFim();

		void adicionarTagInicio(string tag){
			pilhaTagInicio.push_back(tag);
		}
		void adicionarTagFim(string tag){
			pilhaTagFim.push_back(tag);
		}
		
		void removerTopoTagInicio(){
			pilhaTagInicio.pop_back();
		}
		void removerTopoTagFim(){
			pilhaTagFim.pop_back();
		}
		
		bool pilhaInicioVazia(){
			return pilhaTagInicio.empty();
		}
		
		bool pilhaFimVazia(){
			return pilhaTagFim.empty();
		}
		
		string obterTopoPilhaInicio(){
			return pilhaTagInicio.at(pilhaTagInicio.size() -1);
		}
		
		string obterTopoPilhaFim(){
			return pilhaTagFim.at(pilhaTagFim.size() -1);
		}
		/*
		struct no
		{
			string data;
			no *next;
		};

		class PilhaTagsControleFluxo
		{
			no *top;
			public:
				PilhaTagsControleFluxo(){ 
					top = NULL;
				}
				void empilhar(string s);
				void desempilhar();
				bool vazia();
				void display();
				string obterTopo();
				~PilhaTagsControleFluxo();
		};

		bool PilhaTagsControleFluxo::vazia()
		{
			if(top != NULL)
				return false;
			else
				return true;
		}

		void PilhaTagsControleFluxo::empilhar(string s)
		{
			no *temp;
			temp = new no;
			temp->data = s;
			temp->next = top;
			top = temp;
		}

		void PilhaTagsControleFluxo::desempilhar()
		{
			if(top != NULL)
			{
				no *temp = top;
				top = top->next;
				//cout << endl << temp->data << ": Deletado" << endl;
				delete temp;
			}
			else
				cout << "Pilha Vazia. Operação que não deveria acontecer.";
		}

		void PilhaTagsControleFluxo::display()
		{
			no *temp = top;

			while(temp != NULL)
			{
				cout << temp->data << " " << endl;
				temp = temp->next;
			}
		}

		PilhaTagsControleFluxo::~PilhaTagsControleFluxo()
		{
			while(top != NULL)
			{
				no *temp = top;
				top = top->next;
				delete temp;
			}
		}

		string PilhaTagsControleFluxo::obterTopo()
		{
			return top->data;
		}

		PilhaTagsControleFluxo *pilhaTagsBreak = new PilhaTagsControleFluxo();
		PilhaTagsControleFluxo *pilhaTagsContinue = new PilhaTagsControleFluxo();
		*/

		


		/*
		#define qtd_elementos_tarja_tempUSER 5 //.....
		#define qtd_elementos_tarja_tagFim 10 //**********
		#define qtd_elementos_tarja_break 10 //**********
		#define qtd_elementos_tarja_continue 10 //**********		

		#define tarja_variavel "....."  //.....
		#define tarja_tagFim "**********"  //**********

		#define tarja_break "----------"  //**********
		#define tarja_continue "$$$$$$$$$$"  //**********

		void incluirContinue(string traducao,string inicio)
		{
		}
		*/

	}
	
	using namespace PilhaControleFluxo;
	using namespace TagsFluxo;
	using namespace TraducaoControleFluxo;
}

/*

*if:

temp1 = !EXP;
if(temp1)
	goto FIM_IF;
BLOCO 1
FIM_IF:

*if-else:

temp1 = EXP;
if(temp1) goto THEN_IF;
ELSE_BLOCO;
THEN_IF:
	BLOCO 1;
FIM_IF:

*while

INICIO_WHILE:
	temp1 = EXP;
	temp2 = !temp1;
	if(temp2) goto FIM_WHILE;
	BLOCO 1
	goto INICIO_WHILE
FIM_WHILE:

*do-while

INICIO_DOWHILE:
	BLOCO 1;
	temp1 = EXP;
	temp2 != temp1;
	if(temp2) goto FIM_DOWHILE;
	goto INICIO_DOWHILE;
FIM_DOWHILE:

*for ---> for(Init;Test;Update)

Init;
if(!Test) goto DONE;
LOOP:
	BLOCO;
	Update;
	if(Test) goto LOOP;
DONE:

*switch-case ---> OBS: "VALUES_CASE(number)" é o valor fornecido em cada case no código.

temp1 = USER_var;

temp2 = VALUE_CASE1;
temp3 = USER_var == temp2;
if(temp3) 
	BLOCO 1;	
	goto FIM_SWITCH;

temp4 = VALUE_CASE2;
temp5 = USER_var == temp4;
if(temp5)
	BLOCO 2;	
	goto FIM_SWITCH;

.
.
.

tempN = VALUE_CASEM;
tempN+1 = USER_var == tempN;
if(tempN+1)
	BLOCO N;	
	goto FIM_SWITCH;
BLOCO DEFAULT; (se tiver algo definido)

FIM_SWITCH:

*break

*continue

*/

