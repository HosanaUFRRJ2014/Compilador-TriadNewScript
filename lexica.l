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
TEXTO ({LETRA}{DIGITO}{ESPACO})*


%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}
"int"		{return TK_TIPO_INT;}
"var"		{return TK_PALAVRA_VAR;}

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

{OP_RELACIONAL} { yylval.label = yytext ; return TK_OP_RELACIONAL; }

{INT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_NUM; }
{FLOAT}		{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_NUM; }
{BOOLEAN}	{ yylval.label = yytext; yylval.tipo = constante_tipo_booleano; return TK_BOOL; }
{CHAR}		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID; }

.			{ *yytext; }

%%
