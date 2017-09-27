%{
#include <iostream>
#include <string>
#include <sstream>

#define YYSTYPE atributos
#define constante_tipo_inteiro "inteiro"
#define constante_tipo_real "flutuante"
#define constante_tipo_booleano "booleano"
#define constante_tipo_caracter "caracter"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo booelan"

using namespace std;

struct atributos
{
	string label;
	string traducao;
	string tipo;
};

int yylex(void);
void yyerror(string);
string gerarNovaVariavel();
string verificarTipoResultanteDeCoercao(string, string, string);
void disparaErro(string);

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
				$$.traducao =  $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
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
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			| TK_ID
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
			}
			;


E 			: E '+' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
			}
			|
			E '-' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
			}
			|
			E1

E1 			: E1 '*' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
			}
			|
			E1 '/' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " / " + $3.label + ";\n";
			}
			|
			'(' E ')'
			{
				$$.label = $2.label;
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
			'(' E1 ')'
			{
				$$.label = $2.label;
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
//ainda em duvida sobre este caso
//talvez seja somente usar o proprio E1 
			'(' '-' TERMO ')'
			{
				$$.label = $3.label;
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
				$$.traducao = $$.traducao + $2.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " * (-1);\n";
				$$.tipo = $2.tipo; 
			}
			|
			'+' '+' TERMO
			{
				$$.label = $3.label;
				$$.traducao = $$.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " + 1;\n";
				$$.tipo = $3.tipo;
			}
			|
			'-' '-' TERMO
			{
				$$.label = $3.label;
				$$.traducao = $$.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $$.label + " - 1;\n";
				$$.tipo = $3.tipo;
			}
			;
E_LOGICA	: E_LOGICA TK_OP_LOGICO_BIN E_LOGICA
			{
				if($1.tipo == constante_tipo_booleano && $3.tipo == constante_tipo_booleano){
					$$.label = gerarNovaVariavel();
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
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			


%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
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

string gerarNovaVariavel(){
	static int num = 0;
	num++;
	//cout << num << endl;
	string temp = "temp";
	string numInt = to_string(num);
	return temp + numInt;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
