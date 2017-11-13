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
		//(...)
		
		string gerarNovaTagIf(bool fim);
		string gerarNovaTagWhile(bool fim); //...
		string gerarNovaTagDoWhile(bool fim); //...
		string gerarNovaTagFor(bool fim); //...
		string gerarNovaTagSwitch(); //...

		/*
		string criarNovaTag(int num1,int num2,string tagCmd1,string tagCmd2,bool fim){

			string tag;
			int numInt;

			if(fim)
			{
				num1++;
				tag = tagCmd1;
				numInt = to_string(num1);
			}
			else
			{
				num2++;
				tag = tagCmd2;
				numInt = to_string(num2);
			}

			return tag + numInt;

		}
		*/
		
		
		string gerarNovaTagIf(bool fim){
			static int numFim = 0;
			static int numElse = 0;
			string tag;
			string numInt;

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
			
		}

		string gerarNovaTagWhile(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			string tag;
			string numInt;

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
		}

		string gerarNovaTagDoWhile(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			string tag;
			string numInt;

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
		}

		string gerarNovaTagFor(bool fim){
			static int numFim = 0;
			static int numInicio = 0;
			string tag;
			string numInt;

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
		}

		string gerarNovaTagSwitch(){
			static int numFim = 0;
			string tag;
			string numInt;

			numFim++;
			tag = tag_switch_fim;
			numInt = to_string(numFim);
	
			return tag + numInt;
		}

		//(...)
	}

	namespace TraducaoControleFluxo{

		#define qtd_elementos_tarja_tempUSER 5 //.....
		#define qtd_elementos_tarja_tagFim 10 //**********
		#define tarja_variavel "....."  //.....
		#define tarja_tagFim "**********"  //**********

		void substituirVariaveisCase(string traducao, string varTemp, string tagFim){

			int indexVar = traducao.find(tarja_variavel);
			int indexTag = traducao.find(tarja_tagFim);

			while(indexVar != -1 || indexTag != -1){

				traducao.replace(indexVar,qtd_elementos_tarja_tempUSER,varTemp);
				traducao.replace(indexTag,qtd_elementos_tarja_tagFim,tagFim);
				indexVar = traducao.find(tarja_variavel);
				indexTag = traducao.find(tarja_tagFim);
			}

		}

	}

	namespace PilhaControleFluxo{
		  
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
				void display();
				string getTopo();
				~PilhaTagsControleFluxo();
		};

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

		string PilhaTagsControleFluxo::getTopo()
		{
			return top->data;
		}

		PilhaTagsControleFluxo *pilhaTags = new PilhaTagsControleFluxo();

		void executarBreakOuContinue(bool ehBreak)
		{
			if 
		} 

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

