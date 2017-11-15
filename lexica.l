%{
#include <string>

%}

%option yylineno

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

DELIM {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM})\'
BOOLEAN "true"|"false"
INT {NUM}|"-"{NUM}	
FLOAT {REAL}|"-"{REAL}
OP_RELACIONAL "=="|"!="|"<"|">"|">="|"<=" 
ID {LETRA}({LETRA}|{NUM})*
STRING \"([^\"\n]|\\\")*\"


%%

{STRING}	{yylval.label = yytext; yylval.tipo = constante_tipo_string; return TK_STRING;}

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}
"int"		{return TK_TIPO_INT;}
"float"		{return TK_TIPO_FLOAT;}
"char"		{return TK_TIPO_CHAR;}
"bool"		{return TK_TIPO_BOOL;}
"string"	{return TK_TIPO_STRING;}
"var"		{return TK_PALAVRA_VAR;}
"backscope" {return TK_BACKSCOPE;}
"global"		{return TK_PALAVRA_GLOBAL;}
"show"		{return TK_PALAVRA_PRINT;}
"read"		{return TK_PALAVRA_SCAN;}

"//".*		{/*Não faça nada. 
			  OBS: Lembrando que o '.' não considera a quebra de linha, por isso funciona.*/}
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]		{/*Não faça nada.*/}
[/][*]                                    {yyerror(montarMensagemDeErro(MSG_ERRO_COMENTARIO));}

"(int)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_CONVERSAO_EXPLICITA;}
"(float)"	{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_CONVERSAO_EXPLICITA;}
"(char)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CONVERSAO_EXPLICITA;}
"(string)"  { yylval.label = yytext; yylval.tipo = constante_tipo_string; return TK_CONVERSAO_EXPLICITA;}

[(){}[\];,]	{ return *yytext; }
[+\-*/=]	{ return *yytext; }

"and"		{ yylval.label = "&&"; return TK_OP_LOGICO_BIN;}
"or"		{ yylval.label = "||"; return TK_OP_LOGICO_BIN;}
"not"		{ yylval.label = "!"; return TK_OP_LOGICO_UNA;}

{OP_RELACIONAL} { yylval.label = yytext ; return TK_OP_RELACIONAL; }

{INT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_NUM; }
{FLOAT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_NUM; }
{BOOLEAN}	{ yylval.label = yytext; yylval.tipo = constante_tipo_booleano; return TK_BOOL; }
{CHAR}		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID; }



.			{ *yytext; }

%%
