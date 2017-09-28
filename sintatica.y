%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "controleDeVariaveis.h"

#define YYSTYPE atributos
#define constante_tipo_inteiro "int"
#define constante_tipo_real "float"
#define constante_tipo_booleano "bool"
#define constante_tipo_caracter "char"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo booelan"

using namespace std;
using namespace ControleDeVariaveis;

struct atributos
{
	string label;
	string traducaoDeclaracaoDeVariaveis;
	string traducao;
	string tipo;
};

/*struct DADOS_VARIAVEL
{
	string tipo;
	string nome;
	string valor;
};*/

int yylex(void);
void yyerror(string);
string verificarTipoResultanteDeCoercao(string, string, string);
void disparaErro(string);

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL
%token TK_MAIN TK_ID TK_TIPO_INT TK_PALAVRA_VAR
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
			|
			TK_PALAVRA_VAR TK_ID ';'
			{
				$$.label = $2.label;
				if(variavelJaDeclarada($2.label)){
					disparaErro("A variavel com id '" + $2.label + "' já existe");
				}else{
					incluirNoMapa($2.label);
				}
			}
			|
			TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
			{
				if(variavelJaDeclarada($2.label)){
					disparaErro("A variavel com id '" + $2.label + "' já existe");
				}else{
					$$.traducaoDeclaracaoDeVariaveis = "\t" + $4.tipo + " " + $2.label + ";\n";
					$$.traducao = $4.traducao + "\t" + $2.label + " = " + $4.label + "\n";
					incluirNoMapa($2.label, $4.tipo);
				}
			}
			|
			TK_ID '=' VALOR_ATRIBUICAO ';'
			{
				if(variavelJaDeclarada($1.label)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					if(metaData.tipo == ""){
//isso aqui também pode causar problema no futuro devido as lacunas
						metaData.tipo = $3.tipo;
						atualizarNoMapa(metaData);
						$$.traducaoDeclaracaoDeVariaveis = "\t" + metaData.tipo + " " + metaData.nome + ";\n";
					}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
					if(metaData.tipo == $3.tipo){
						$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
					}
					else{
						disparaErro("Os tipos da atribuição não são compativeis. O tipo da variavel de id '" + $1.label + "' é '" + $1.tipo + "' e o valor atribuido é do tipo '"+ $3.tipo + "'\n");
					}
				}
			}
			;


TERMO		: TK_NUM
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t"  + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			//provisoriamente deixar assim, mas talvez esse id suma
			| TK_ID
			{
				if(variavelJaDeclarada($1.label)){
					$$.label = $1.label;
					$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				}
			}
			;
			
VALOR_ATRIBUICAO: E
			|
			E_UNARIA
			|
			E_LOGICA
			|
			TERMO_CARACTER
			;

E 			: E '+' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
			}
			|
			E '-' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
			}
			|
			E1

E1 			: E1 '*' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
			}
			|
			E1 '/' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " / " + $3.label + ";\n";
			}
			|
			'(' E ')'
/*			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
			}*/
			|
			'(' E1 ')'
/*			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
			}*/
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
	yyparse();

	return 0;
}

void disparaErro(string mensagem){
	cout << mensagem << endl;
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

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
