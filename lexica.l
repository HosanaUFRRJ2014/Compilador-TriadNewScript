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
OP_RELACIONAL_MENOR_MAIOR "<"|">"
ID {LETRA}({LETRA}|{NUM})*
TEXTO ({LETRA}{DIGITO}{ESPACO})*


%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}
"int"		{return TK_TIPO_INT;}

"var"		{return TK_PALAVRA_VAR;}


"//"		{return TK_COMENTARIO_1L;}
"/*"		{return TK_ABRE_COMENTARIO_NL;}
"*/"		{return TK_FECHA_COMENTARIO_NL;}


"(int)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_CONVERSAO_EXPLICITA;}
"(float)"	{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_CONVERSAO_EXPLICITA;}
"(char)"		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CONVERSAO_EXPLICITA;}


[(){}[\];,]	{ return *yytext; }
[+\-*/=]	{ return *yytext; }

"and"		{ yylval.label = "&&"; return TK_OP_LOGICO_BIN;}
"or"		{ yylval.label = "||"; return TK_OP_LOGICO_BIN;}
"not"		{ yylval.label = "!"; return TK_OP_LOGICO_UNA;}

{OP_RELACIONAL_MENOR_MAIOR} { yylval.label = yytext ; return TK_OP_RELACIONAL_MENOR_MAIOR; }

"<="					{ yylval.label = yytext ; return TK_MENOR_IGUAL; }
">="					{ yylval.label = yytext ; return TK_MAIOR_IGUAL; }
"=="					{ yylval.label = yytext ; return TK_IGUAL_IGUAL; }
"!="					{ yylval.label = yytext ; return TK_DIFERENTE; }

{NUM}		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_NUM; }
"-"{NUM}		{ yylval.label = yytext; yylval.tipo = constante_tipo_inteiro; return TK_NUM; }
{REAL}		{ yylval.label = yytext; yylval.tipo = constante_tipo_flutuante; return TK_NUM; }
{BOOLEAN}	{ yylval.label = yytext; yylval.tipo = constante_tipo_booleano; return TK_BOOL; }
{CHAR}		{ yylval.label = yytext; yylval.tipo = constante_tipo_caracter; return TK_CHAR; }
{ID}		{ yylval.label = yytext; return TK_ID; }

\"{TEXTO}\""\n"	{ yylval.label = yytext; return TK_TEXTO; }

.			{ *yytext; }

%%
