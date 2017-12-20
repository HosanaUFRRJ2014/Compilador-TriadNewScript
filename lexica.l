%{
#include <string>
//CHAR \'({LETRA}|{NUM})\'
//ARRAY {NOME_ARRAY}\({TIPOS},\[{DIGITO}+(,{DIGITO}+)*\]\)
%}

%option yylineno

ESPACO [ \t]
DIGITO [0-9]
LETRA [A-Za-z_]

DELIM {ESPACO}+
NUM {DIGITO}+
REAL {NUM}+("."{NUM}+)?
CHAR \'([^\"\n]|\\\")\'
BOOLEAN "true"|"false"
INT {NUM}|"-"{NUM}
FLOAT {REAL}|"-"{REAL}
OP_RELACIONAL_P1 "=="|"!="
OP_RELACIONAL_P2 "<"|">"|">="|"<="

OP_COMPOSTO_ARITMETICO_P1 "+="|"-="
OP_COMPOSTO_ARITMETICO_P2 "*="|"/="
OP_COMPOSTO_LOGICO_P1 "or="
OP_COMPOSTO_LOGICO_P2 "and="

ID {LETRA}({LETRA}|{NUM})*
STRING \"([^\"\n]|\\\")*\"

%%

{STRING}	{yylval.label = yytext; yylval.tipo = constante_tipo_string; return TK_STRING;}
"len"		{return TK_LEN;}

"\n"		{}

{DELIM} 	{}

"int"		{yylval.label = "int"; yylval.tipo = constante_tipo_inteiro; return TK_TIPO_INT;}
"float"		{yylval.label = "float"; yylval.tipo = constante_tipo_flutuante; return TK_TIPO_FLOAT;}
"char"		{yylval.label = "char"; yylval.tipo = constante_tipo_caracter; return TK_TIPO_CHAR;}
"bool"		{yylval.label = "int"; yylval.tipo = constante_tipo_booleano; return TK_TIPO_BOOL;}
"string"	{yylval.label = "char *"; yylval.tipo = constante_tipo_string; return TK_TIPO_STRING;}

"var"		{return TK_PALAVRA_VAR;}
"backscope" {return TK_BACKSCOPE;}
"global"		{return TK_PALAVRA_GLOBAL;}
"show"		{return TK_PALAVRA_PRINT;}
"read"		{return TK_PALAVRA_SCAN;}
"func"	{ yylval.tipo = constante_tipo_funcao; return TK_PALAVRA_FUNC;} //funciona como tipo ou como criacao de funcao
"return"		{yylval.label = yytext; return TK_PALAVRA_RETURN;}

"//".*		{/*Não faça nada.
			  OBS: Lembrando que o '.' não considera a quebra de linha, por isso funciona.*/}
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]		{/*Não faça nada.*/}
[/][*]                                    {string params[1] = {yytext};
											yyerror(montarMensagemDeErro(MSG_ERRO_COMENTARIO,params, 1));}
[*][/]                                    {	string params[1] = {yytext};
											yyerror(montarMensagemDeErro(MSG_ERRO_COMENTARIO,params, 1));}
["."]		{return '.';}

"(int)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_CONVERSAO_EXPLICITA;}
"(float)"	{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_CONVERSAO_EXPLICITA;}
"(char)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CONVERSAO_EXPLICITA;}
"(string)"  { yylval.label = yytext; yylval.tipo = constante_tipo_string; return TK_CONVERSAO_EXPLICITA;}

[\|(){}\[\];,:]	{ return *yytext; }

"++"	{yylval.label = yytext; return TK_OP_ARIT_UNA;}
"--"	{yylval.label = yytext; return TK_OP_ARIT_UNA;}
[+\-]	{ yylval.label = yytext; return TK_OP_ARIT_PRIO1; }
[*/]	{ yylval.label = yytext; return TK_OP_ARIT_PRIO2; }
[=]	{ return *yytext; }

"and"		{ yylval.label = "&&"; return TK_OP_LOG_BIN_PRIO2;}
"or"		{ yylval.label = "||"; return TK_OP_LOG_BIN_PRIO1;}
"not"		{ yylval.label = "!"; return TK_OP_LOG_UNA;}

"if"		{yylval.label = yytext; return TK_IF;}
"else"		{yylval.label = yytext; return TK_ELSE;}
"while"		{yylval.label = yytext; return TK_WHILE;}
"do"		{yylval.label = yytext; return TK_DO;}
"for"		{yylval.label = yytext; return TK_FOR;}
"switch"	{yylval.label = yytext; return TK_SWITCH;}
"case"		{yylval.label = yytext; return TK_CASE;}
"default"		{yylval.label = yytext; return TK_DEFAULT;}
"break"		{yylval.label = yytext; return TK_BREAK;}
"continue"	{yylval.label = yytext; return TK_CONTINUE;}

{OP_RELACIONAL_P1} { yylval.label = yytext ; return TK_OP_REL_PRIO1; }
{OP_RELACIONAL_P2} { yylval.label = yytext ; return TK_OP_REL_PRIO2; }

{OP_COMPOSTO_ARITMETICO_P1} { yylval.label = yytext ; return TK_OP_ARIT_COMP_PRIO1; }
{OP_COMPOSTO_ARITMETICO_P2} { yylval.label = yytext ; return TK_OP_ARIT_COMP_PRIO2; }
{OP_COMPOSTO_LOGICO_P1} { yylval.label = "||=" ; return TK_OP_LOG_COMP_PRIO1; }
{OP_COMPOSTO_LOGICO_P2} { yylval.label = "&&=" ; return TK_OP_LOG_COMP_PRIO2; }


{INT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_NUM; }
{FLOAT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_NUM; }
{BOOLEAN}	{ yylval.label = yytext; yylval.tipo = constante_tipo_booleano; return TK_BOOL; }
{CHAR}		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID; }



.			{ *yytext; }

%%
