%{
#include <iostream>
#include <string>
#include <sstream>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string label;
	string traducao;
};

int yylex(void);
void yyerror(string);
string gerarNovaVariavel();
%}

%token TK_NUM
%token TK_MAIN TK_ID TK_TIPO_INT
%token TK_FIM TK_ERROR

%start S

%left '+'

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO			: '{' COMANDOS '}'
			{
				$$.traducao =  $2.traducao;
			}
			;

COMANDOS		: COMANDO COMANDOS
			{
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
			;

COMANDO 		: E ';'
			|
			E1 ';'
			;


NUM_OU_ID		: TK_NUM
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
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
			NUM_OU_ID
			|
			E '+' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
			}
			|
			E1 '+' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
			}
			;

E1 			: E1 '*' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
			}
			
			|
			NUM_OU_ID
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yyparse();

	return 0;
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
