%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "MapaTipos.h"

#define YYSTYPE atributos
#define constante_tipo_inteiro "int"
#define constante_tipo_real "float"
#define constante_tipo_booleano "bool"
#define constante_tipo_caracter "char"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo booelan"

using namespace std;
using namespace MapaTiposLib;

struct atributos
{
	string label;
	string traducaoDeclaracaoDeVariaveis;
	string traducao;
	string tipo;
};

struct DADOS_VARIAVEL
{
	string tipo;
	string nome;
	string valor;
};

int yylex(void);
void yyerror(string);
string gerarNovaVariavel();
string verificarTipoResultanteDeCoercao(string, string, string);
void disparaErro(string);

map<string, string> mapaTipos;

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL
%token TK_MAIN TK_ID TK_TIPO_INT
%token TK_FIM TK_ERROR

%start S

%left '+' '-'
%left '/' '*'

//%nonassoc 

%left '<'
%left '>'
%left "=="
%left "<="
%left ">="
%left "<>"
%left "and"
%left "or"
%left "not"

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao =  $$.traducao + "\n" + $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + "\n" + $2.traducao;
			}
			|
			;

COMANDO 	: E ';'
			|
			E_UNARIA ';'
			|
			E_REL ';'
			|
			E_LOGICA ';'
			|
			TERMO_CARACTER ';'
			;


TERMO		: TK_NUM
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t"  + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			| TK_ID
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			;


E 			: E '+' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				
				$$.traducao = $1.traducao + $3.traducao;
				
				if($1.tipo == $3.tipo)
				{
					
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
				}
				
				else //necessita conversão de tipo
				{
					string chaveFinal = gerarChaveFinal($1.tipo, $3.tipo,"+");
					string resultado = mapaTipos[chaveFinal];
					
					//caso a chave não exista para a primeira ordem de tipos, testar com a ordem invertida
					if (resultado == "")
					{
						chaveFinal = gerarChaveFinal($3.tipo, $1.tipo,"+");
						resultado = mapaTipos[chaveFinal];
					}
					
					if(resultado == constante_erro)
						yyerror("Tipos incompátiveis para se realizar operação");
					
					
					
					string label_old = $$.label;
					if($3.tipo == resultado)
					{
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
						
						$$.label = gerarNovaVariavel();
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " + " + label_old + ";\n";
					}
					else if($1.tipo == resultado)
					{
							
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
						$$.label = gerarNovaVariavel();
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + label_old + ";\n";
						
					}
					
	
					$$.tipo = resultado;	
				
						
				}
			}
			|
			E '-' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				if($1.tipo == $3.tipo)
				{
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
				}
				
				else //necessita conversão de tipo
				{
					string chaveFinal = gerarChaveFinal($1.tipo, $3.tipo,"-");
					string resultado = mapaTipos[chaveFinal];
					
					//caso a chave não exista para a primeira ordem de tipos, testar com a ordem invertida
					if (resultado == "")
					{
						chaveFinal = gerarChaveFinal($3.tipo, $1.tipo,"-");
						resultado = mapaTipos[chaveFinal];
					}
					
					if(resultado == constante_erro)
						yyerror("Tipos incompátiveis para se realizar operação");
					
					
					
					string label_old = $$.label;
					if($3.tipo == resultado)
					{
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
						
						$$.label = gerarNovaVariavel();
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " - " + label_old + ";\n";
					}
					else if($1.tipo == resultado)
					{
							
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
						$$.label = gerarNovaVariavel();
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + label_old + ";\n";
						
					}
					
	
					$$.tipo = resultado;	
				
						
				}
				
				
				
				
			}
			|
			E1

E1 			: E1 '*' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				if($1.tipo == $3.tipo)
				{
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
				}
				
				else //necessita conversão de tipo
				{
					string chaveFinal = gerarChaveFinal($1.tipo, $3.tipo,"*");
					string resultado = mapaTipos[chaveFinal];
					
					//caso a chave não exista para a primeira ordem de tipos, testar com a ordem invertida
					if (resultado == "")
					{
						chaveFinal = gerarChaveFinal($3.tipo, $1.tipo,"*");
						resultado = mapaTipos[chaveFinal];
					}
					
					if(resultado == constante_erro)
						yyerror("Tipos incompátiveis para se realizar operação");
					
					
					
					string label_old = $$.label;
					if($3.tipo == resultado)
					{
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
						
						$$.label = gerarNovaVariavel();
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " * " + label_old + ";\n";
					}
					else if($1.tipo == resultado)
					{
							
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
						$$.label = gerarNovaVariavel();
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + label_old + ";\n";
						
					}
					
	
					$$.tipo = resultado;	
				
						
				}
			}
			|
			E1 '/' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				if($1.tipo == $3.tipo)
				{
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " / " + $3.label + ";\n";
				}
				
				else //necessita conversão de tipo
				{
					string chaveFinal = gerarChaveFinal($1.tipo, $3.tipo,"/");
					string resultado = mapaTipos[chaveFinal];
					
					//caso a chave não exista para a primeira ordem de tipos, testar com a ordem invertida
					if (resultado == "")
					{
						chaveFinal = gerarChaveFinal($3.tipo, $1.tipo,"/");
						resultado = mapaTipos[chaveFinal];
					}
					
					if(resultado == constante_erro)
						yyerror("Tipos incompátiveis para se realizar operação");
					
					
					
					string label_old = $$.label;
					if($3.tipo == resultado)
					{
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
						
						$$.label = gerarNovaVariavel();
						
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " / " + label_old + ";\n";
					}
					else if($1.tipo == resultado)
					{
							
						$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
						$$.label = gerarNovaVariavel();
						$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " / " + label_old + ";\n";
						
					}
					
	
					$$.tipo = resultado;	
				
						
				}
			}
			|
			'(' E ')'
			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
			'(' E1 ')'
			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
//ainda em duvida sobre este caso
//talvez seja somente usar o proprio E1 
			'(' '-' TERMO ')'
			{
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " * (-1);\n";
				$$.tipo = $3.tipo; 
			}
			|
			TERMO
			;
E_UNARIA	: '-' TERMO
			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " * (-1);\n";
				$$.tipo = $2.tipo; 
			}
			|
			'+' '+' TERMO
			{
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " + 1;\n";
				$$.tipo = $3.tipo;
			}
			|
			'-' '-' TERMO
			{
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " - 1;\n";
				$$.tipo = $3.tipo;
			}
			;
E_LOGICA	: E_LOGICA TK_OP_LOGICO_BIN E_LOGICA
			{
				if($1.tipo == constante_tipo_booleano && $3.tipo == constante_tipo_booleano){
					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
					$$.traducao = $1.traducao + $3.traducao;
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " " + $2.label + " " + $3.label + ";\n";
					$$.tipo = constante_tipo_booleano;
				}
				else{
					disparaErro(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
			|
			//derivacao ambigua [usar %nonassoc]
			TK_OP_LOGICO_UNA E_LOGICA
			{
				if($2.tipo == constante_tipo_booleano){
					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $2.tipo + " " + $$.label + ";\n";
					$$.traducao = $2.traducao;
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
					$$.tipo = constante_tipo_booleano;
				}
				else{
					disparaErro(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
			|
			TK_BOOL
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			|
			E_REL
			{
			}
			;

TERMO_REL	: E
			;

E_REL		: TERMO_REL TK_OP_RELACIONAL TERMO_REL
			{
				//o tipo resultante deve ser constante_tipo_booleano
			}
			;
			
TERMO_CARACTER: TK_CHAR
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			


%%

#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL > tabelaDeVariaveis;


int yyparse();

int main( int argc, char* argv[] )
{
	
	mapaTipos = criarMapa();
	yyparse();
	
	

	return 0;
}

void disparaErro(string mensagem){
	cout << mensagem;
	exit(0);
}

string verificarResultanteDeCoercao(string tipo1, string tipo2, string operacao){
	//a principio será feito com if devido a pouca quantidade de tipo e falta de noção de como fazer o certo
	// mas depois vai ser preciso trocar para matriz
	
	if(tipo1 == constante_tipo_real || tipo2 == constante_tipo_real){
		return constante_tipo_real;
	}else{
		return constante_tipo_inteiro;
	}
}
//declaração de variaveis var <nome variavel>;
string gerarNovaVariavel(){
	static int num = 0;
	num++;
	//cout << num << endl;
	string temp = "temp";
	
	/*d.nome = "var1";
	d.valor = "10";
	d.tipo = constante_tipo_inteiro;
	
	tabelaDeVariaveis[d.nome] = d;
	cout << tabelaDeVariaveis[d.nome].valor << endl;
	DADOS_VARIAVEL A = tabelaDeVariaveis["aaa"];
	cout << (A.nome == "") << endl;*/
	
	string numInt = to_string(num);
	return temp + numInt;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
