%{
#include <iostream>
#include <string>
#include <algorithm> 
#include <sstream>
#include <map>
#include <vector>

#include "MapaTipos.h"

#include "controleDeVariaveis.h"

#include "MensagensDeErro.h"

#include "controleDeFluxo.h"

#define YYSTYPE ATRIBUTOS

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo booelan"
#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_TIPOS_DIFERENTES "Os operandos de expressões relacionais precisam ser do mesmo tipo"

using namespace std;
using namespace MapaTiposLib;
using namespace ControleDeVariaveis;
using namespace MensagensDeErro;
using namespace ControleDeFluxo;

struct ATRIBUTOS
{
	string label; //Texto lido do lex.
	string traducaoDeclaracaoDeVariaveis; //Para colocação do atributo no início do código.
	string traducao; //Tradução do código atual.
	string tipo; //Tipo resultante atual da tradução.
};

int yylex(void);
void yyerror(string);
bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
string constroiPrint(string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);

int l = 0;

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL
%token TK_MAIN TK_ID TK_TIPO_INT TK_PALAVRA_VAR
%token TK_FIM TK_ERROR
%token TK_CONVERSAO_EXPLICITA
%token TK_TEXTO

%token TK_IF
%token TK_ELSE
%token TK_WHILE
%token TK_DO
%token TK_FOR
%token TK_SWITCH
%token TK_CASE
%token TK_DEFAULT
%token TK_BREAK
%token TK_CONTINUE

%start S

%nonassoc IFX
%nonassoc TK_ELSE //Eliminar a ambiguidade inerente do if-else. O yacc por naturalidade já o faz, mas isso evita o reconhecimento do mesmo do conflito de shift/reduce.
%left TK_OP_LOGICO_UNA
%left TK_OP_LOGICO_BIN
%right '='
%nonassoc "==" "!=" //Confiando precedência ao yacc. Como isso é feito para os aritméticos, o mesmo deve valer para os relacionais.
%nonassoc '<' '>' "<=" ">="
%left '+' '-'
%left '*' '/'


%%


S	 		: DECLARACOES TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include<string.h>\n#include<stdio.h>\n\n#define TRUE 1\n#define FALSE 0\n\n" << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << $1.traducao << endl << $6.traducao << "\treturn 0;\n}" << endl;
			}
			;

UP_S		:
			{
				aumentarEscopo();
			}
			;

BLOCO		: UP_S '{' COMANDOS '}'
			{
				$$.traducao =  substituirTodasAsDeclaracoesProvisorias($3.traducaoDeclaracaoDeVariaveis);
				$$.traducao =  $$.traducao + "\n" + $3.traducao;
				diminuirEscopo();
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				cout << l << ":" << endl << "Tradução de COMANDO:" << endl << endl << $1.traducao << endl << endl << "Tradução de COMANDOS" <<
				endl << endl << $2.traducao << endl << endl << "---------------------------------" << endl << endl;
				l++;
				

				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				if($1.traducao != "" && $1.tipo != constante_tipo_bloco){
					$$.traducao = $1.traducao + "\n" + constroiPrint($1.tipo, $1.label);
				}
				$$.traducao = $$.traducao + $2.traducao;

				//cout << "Tradução Geral:" << $$.traducao << endl << endl << "---------------------------------FIM DE TUDO" << endl << endl;
			}
			|
			COMANDO
			;

COMANDO 	: E ';'
			|
			E_UNARIA ';'
			|
			E_REL ';'
			|
			E_LOGICA ';'
			|
			E_FLUXO_CONTROLE
			|
			E_BREAK_CONTINUE ';'
			|
			DECLARACOES
			|
			BLOCO
			{
				$$.traducao = "\t{\n" + $1.traducao + "\t}\n";
				$$.tipo = constante_tipo_bloco;
				$$.label = "";
				$$.traducaoDeclaracaoDeVariaveis = "";
			}
			;
			
DECLARACOES: TK_PALAVRA_VAR TK_ID ';'
			{
				if(variavelJaDeclarada($2.label, false)){
					//mensagem de erro dupla declaração
					string params[1] = {$2.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}else{
					$$.traducaoDeclaracaoDeVariaveis = "\t" + construirDeclaracaoProvisoriaDeInferenciaDeTipo($2.label);
					incluirNoMapa($2.label);
				}
			}
			|
			TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
			{	
				if(variavelJaDeclarada($2.label, false)){
					//mensagem de erro dupla declaração
					string params[1] = {$2.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}else{
					string tipo = $4.tipo;
					if(tipo == constante_tipo_booleano){
						tipo = constante_tipo_inteiro;
						tipo = "\t" + tipo;
					}
					$2.label = prefixo_variavel_usuario + $2.label;
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + $2.label + ";\n";
					$$.traducao = $4.traducao + "\t" + $2.label + " = " + $4.label + ";\n";
					incluirNoMapa($2.label, $4.tipo);
					$$.label = $2.label;
					$$.tipo = $4.tipo;
				}
				
			}
			|
			ID '=' VALOR_ATRIBUICAO ';'
			{				
				if($1.label != $3.label){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					if(metaData.tipo == ""){
//isso aqui também pode causar problema no futuro devido as lacunas
						metaData.tipo = $3.tipo;
						atualizarNoMapa(metaData);
						string tipo = metaData.tipo;
						if(tipo == constante_tipo_booleano){
							tipo = constante_tipo_inteiro;
							tipo = "\t" + tipo;
						}
						adcionarDefinicaoDeTipo($1.label, tipo);
					}
					$1.tipo = metaData.tipo;
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
					if(metaData.tipo == $3.tipo){
						$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $$.traducao + $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
					}
					else{
						string strPrefixoVarUsuario = prefixo_variavel_usuario;
						string params[3] = {$1.label.replace(0, strPrefixoVarUsuario.length(), ""), $1.tipo, $3.tipo};
						yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
					}
					$$.label = $1.label;
					$$.tipo = $1.tipo;
				}
				else{
					$$ = $3;
				}
			}
			|
			;

//REGRA CRIADA PRA DIMINUIR A QUANTIDADE DE REPETIÇÕES DAS VERIFICAÇÕES DE EXISTENCIA DE VARIAVEL
ID		: TK_ID
			{
				if(variavelJaDeclarada($1.label)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
				}else{
					string params[1] = {$1.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA ,params, 1));
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
			| 
			ID
			|
			TK_CHAR
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			;
			
VALOR_ATRIBUICAO: E
			{
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra TERMO: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if($1.label.find(prefixo_variavel_usuario) == 0 && $1.tipo == ""){
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {$1.label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}
				$$ = $1;
			}
			|
			//o id tmb pode vir pelas regras de expressão logica, mas não parece ter acontecido alguma vez
			E_UNARIA
			|
			E_LOGICA
			|
			TK_CONVERSAO_EXPLICITA VALOR_ATRIBUICAO
			{
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao;
				if(verificarPossibilidadeDeConversaoExplicita($2.tipo, $1.tipo)){
					$$.label = gerarNovaVariavel();
					$$.tipo = $1.tipo;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $$.tipo + " " + $$.label + ";\n";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
				}else{
					string params[2] = {$2.tipo, $1.tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}
			}
			;

E 			: E '+' E
			{
				$$ = tratarExpressaoAritmetica("+", $1, $3);							
			}
			|
			E '-' E
			{
				$$ = tratarExpressaoAritmetica("-", $1, $3);
			}
			|
			E1
			;

E1 			: E1 '*' E1
			{
				$$ = tratarExpressaoAritmetica("*", $1, $3);
			}
			|
			E1 '/' E1
			{
				$$ = tratarExpressaoAritmetica("/", $1, $3);
			}
			|
			'(' E ')'
			{
				$$ = $2;
			}
			|
			'(' E1 ')'
			{
				$$ = $2;
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
			|
			TK_CONVERSAO_EXPLICITA E
			{
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao;
				if(verificarPossibilidadeDeConversaoExplicita($2.tipo, $1.tipo)){
					$$.label = gerarNovaVariavel();
					$$.tipo = $1.tipo;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $$.tipo + " " + $$.label + ";\n";
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
				}else{
					string params[2] = {$2.tipo, $1.tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}	
			}
			

			;
E_UNARIA	: '-' TERMO
			{
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + $$.label + " * (-1);\n";
				$$.tipo = $2.tipo; 
			}
			|
			'+' '+' TERMO
			{
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $$.label + " + 1;\n";
				$$.tipo = $3.tipo;
			}
			|
			'-' '-' TERMO
			{
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $$.label + " - 1;\n";
				$$.tipo = $3.tipo;
			}
			;

E_LOGICA	: E_LOGICA TK_OP_LOGICO_BIN E_LOGICA
			{
				if($1.tipo == constante_tipo_booleano && $3.tipo == constante_tipo_booleano){
					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
					string tipo = constante_tipo_inteiro;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t\t" + tipo + " " + $$.label + ";\n";
					$$.traducao = $1.traducao + $3.traducao;
					$$.traducao = $$.traducao + "\t\t" + $$.label + " = " + $1.label + " " + $2.label + " " + $3.label + ";\n";
					$$.tipo = constante_tipo_booleano;
				}
				else{
					yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
			|
			//derivacao ambigua [usar %nonassoc]
			TK_OP_LOGICO_UNA E_LOGICA
			{
				if($2.tipo == constante_tipo_booleano){
					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
					string tipo = constante_tipo_inteiro;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t\t" + tipo + " " + $$.label + ";\n";
					$$.traducao = $2.traducao;
					$$.traducao = $$.traducao + "\t\t" + $$.label + " = " + $1.label + $2.label + ";\n";
					$$.tipo = constante_tipo_booleano;
				}
				else{
					yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
			|
			ID
			|
			TK_BOOL
			{
				string nomeUpperCase = $1.label;
				transform(nomeUpperCase.begin(), nomeUpperCase.end(), nomeUpperCase.begin(), ::toupper);
				$$.label = nomeUpperCase;
				incluirNoMapa($$.label, $1.tipo);
				$$.tipo = $1.tipo;
			}
			|
			'(' E_LOGICA ')'
			{
				$$ = $2;
			}
			|
			E_REL
			;

TERMO_REL	: E //------> Isso é uma regra inútil. Mas se quiser colocar pra legibilidade do código, que seja...
			|
			E E_REL
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $2.traducao;
			}
			;

E_REL	: TERMO_REL TK_OP_RELACIONAL TERMO_REL
			{
				//cout << "/*"  << $1.label << endl << $3.label << endl << "*/";
				//cout << "/*"  << $1.traducaoDeclaracaoDeVariaveis << endl << $3.traducaoDeclaracaoDeVariaveis << endl << "*/" << endl;
				$$ = tratarExpressaoRelacional($2.label,$1,$3);
				//cout << "/*" << $$.label << endl << $1.label << endl << $3.label << endl << "*/";
				//cout << "/*" << $$.traducaoDeclaracaoDeVariaveis << endl << $1.traducaoDeclaracaoDeVariaveis << endl << $3.traducaoDeclaracaoDeVariaveis << endl << "*/" << endl;
				//cout << "/*" << $$.traducao << endl << $1.traducao << endl << $3.traducao << endl << "*/" << endl;
			}
			|
			'(' E_REL ')'
			{
				$$ = $2;
			}
			;

E_FLUXO_CONTROLE	: COMANDO_IF
				|
				COMANDO_WHILE
				|
				COMANDO_DOWHILE
				|
				COMANDO_FOR
				|
				COMANDO_SWITCH
				;

COMANDO_IF	: TK_IF '(' E_REL ')' COMANDO %prec IFX
			{
				//cout << $5.traducaoDeclaracaoDeVariaveis << endl;
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis + "\t" +
													constante_tipo_inteiro + " " + $$.label + ";\n";
				//cout << $$.traducaoDeclaracaoDeVariaveis << endl;
				
				string tagFim = gerarNovaTagIf(true);				

				$$.traducao = $3.traducao + "\t" + $$.label + " = " + "!" + $3.label + ";\n" + 
							"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" + 
							$5.traducao + "\t" + tagFim + ":\n";

				//Para o break e continue.
				//if(haBreakNoBloco($$.traducao)){
				//	yyerror(MSG_ERRO_BREAK_NAO_PERMITIDO);
				//}else if(haContinueNoBloco($$.traducao)){
				//	yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
				//} 
 			
			}
			|
			TK_IF '(' E_REL ')' COMANDO TK_ELSE COMANDO
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis +
													$7.traducaoDeclaracaoDeVariaveis + "\t" +
													constante_tipo_inteiro + " " + $$.label + ";\n";
				
				//Criar tag para pular o bloco do else (que ficara logo em seguida no cod. interm.)
				string tagBlocoIf = gerarNovaTagIf(false);
				//Criar tag de fim do if.
				string tagFim = gerarNovaTagIf(true);
								
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $3.label + ";\n" + 
								"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagBlocoIf + ";\n" + 
								$7.traducao + "\t" + "goto " + tagFim + ";\n" + "\t" + tagBlocoIf + ":\n" +
								$5.traducao + "\t" + tagFim + ":\n";

				//Para o break e continue.
				//if(haBreakNoBloco($$.traducao)){
				//	yyerror(MSG_ERRO_BREAK_NAO_PERMITIDO);
				//}else if(haContinueNoBloco($$.traducao)){
				//	yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
				//} 			
				
			}
			;

EMPILHAR_TAG_WHILE	:
					{ 
						string tagInicio = gerarNovaTagWhile(false);
						string tagFim = gerarNovaTagWhile(true);
						pilhaTagsBreak->empilhar(tagFim);
						pilhaTagsContinue->empilhar(tagInicio); 
					}
					;

COMANDO_WHILE	: EMPILHAR_TAG_WHILE TK_WHILE '(' E_REL ')' COMANDO
				{
					//string tagInicio = gerarNovaTagWhile(false);
					//string tagFim = gerarNovaTagWhile(true);

					string tagInicio = pilhaTagsContinue->obterTopo();
					string tagFim = pilhaTagsBreak->obterTopo();

					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + $6.traducaoDeclaracaoDeVariaveis + 
														"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";

					$$.traducao = "\t" + tagInicio + ":\n" + $4.traducao + "\t" + $$.label + " = " + "!" + $4.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									$5.traducao + "\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":\n";

					//Para o break e continue.
					//$$.traducao = incluirBreakEContinue($$.traducao,tagInicio,tagFim,false);
					pilhaTagsContinue->desempilhar();
					pilhaTagsBreak->desempilhar();  

				}
				;

EMPILHAR_TAG_DOWHILE	:
					{ 
						string tagInicio = gerarNovaTagDoWhile(false);
						string tagFim = gerarNovaTagDoWhile(true);
						pilhaTagsBreak->empilhar(tagFim);
						pilhaTagsContinue->empilhar(tagInicio); 
					}
					;

COMANDO_DOWHILE	: EMPILHAR_TAG_DOWHILE TK_DO COMANDO TK_WHILE '(' E_REL ')' ';' //PROBLEMAS COM O COMANDO ----> RESOLVIDO, COM GAMBIARRA!
				{

					//string tagInicio = gerarNovaTagDoWhile(false);
					//string tagFim = gerarNovaTagDoWhile(true);

					string tagInicio = pilhaTagsContinue->obterTopo();
					string tagFim = pilhaTagsBreak->obterTopo();

					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $6.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis + 
														"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";

					$$.traducao = "\t" + tagInicio + ":\n" + $3.traducao + 
									$6.traducao + "\t" + $$.label + " = " + "!" + $6.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									"\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":\n";

					//Para o break e continue.
					//$$.traducao = incluirBreakEContinue($$.traducao,tagInicio,tagFim,false);
					pilhaTagsContinue->desempilhar();
					pilhaTagsBreak->desempilhar();
				}
				;

/*INIT	: MULTI_ATRIBUICAO
		{ (...) }

UPDATE: E ';' 
		{...}
		| 
		E ',' UPDATE
		{...}
		;
*/

INIT	: DECLARACOES
		;

T_UPDATE	: ID '=' VALOR_ATRIBUICAO
			{						
				if($1.label != $3.label){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					if(metaData.tipo == ""){
//isso aqui também pode causar problema no futuro devido as lacunas
						metaData.tipo = $3.tipo;
						atualizarNoMapa(metaData);
						string tipo = metaData.tipo;
						if(tipo == constante_tipo_booleano){
							tipo = constante_tipo_inteiro;
							tipo = "\t" + tipo;
						}
						adcionarDefinicaoDeTipo($1.label, tipo);
					}
					$1.tipo = metaData.tipo;
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
					if(metaData.tipo == $3.tipo){
						$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $$.traducao + $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
					}
					else{
						string strPrefixoVarUsuario = prefixo_variavel_usuario;
						string params[3] = {$1.label.replace(0, strPrefixoVarUsuario.length(), ""), $1.tipo, $3.tipo};
						yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
					}
					$$.label = $1.label;
					$$.tipo = $1.tipo;
				}
				else{
					$$ = $3;
				}
			}
			| 
			E_UNARIA
			;

UPDATE	:	T_UPDATE ',' UPDATE 
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $3.traducao;
			}
			| 
			T_UPDATE 
			|
			;

EMPILHAR_TAG_FOR	: 
					{	
						string tagInicio = gerarNovaTagFor(false);
						string tagFim = gerarNovaTagFor(true);
						pilhaTagsContinue->empilhar(tagInicio);
						pilhaTagsBreak->empilhar(tagFim);
					}
					;
 
//TK_FOR '(' INIT ';' E_REL ';' UPDATE ')' COMANDO
COMANDO_FOR	: EMPILHAR_TAG_FOR TK_FOR '(' INIT E_REL ';' UPDATE ')' COMANDO
			{
				//string tagInicio = gerarNovaTagFor(false);
				//string tagFim = gerarNovaTagFor(true);
				
				string tagInicio = pilhaTagsContinue->obterTopo();
				string tagFim = pilhaTagsBreak->obterTopo();
				
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis +
													$7.traducaoDeclaracaoDeVariaveis + $9.traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";

				$$.traducao = $4.traducao + "\t" + tagInicio + ":\n" + 
								$5.traducao + "\t" + $$.label + " = " + "!" + $5.label + ";\n" +
								"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
								$9.traducao + $7.traducao + "\t" + "goto " + tagInicio + ";\n" + 
								"\t" + tagFim + ":\n";

				//Para o break e continue.
				//$$.traducao = incluirBreakEContinue($$.traducao,tagInicio,tagFim,false);
				pilhaTagsContinue->desempilhar();
				pilhaTagsBreak->desempilhar();			
			}
			;

COMANDO_SWITCH	: TK_SWITCH '(' ID ')' '{' CASES '}' //FASE DE CONSTRUÇÃO!
				{

					if($3.tipo != constante_tipo_string && $3.tipo != constante_tipo_flutuante) {
						//(...)
						string tagFim = gerarNovaTagSwitch();

						//$$.label = gerarNovaVariavel();
						
						//Outra parte da árvore já tera a $3.traducaoDeclaracaoDeVariaveis salva. Portanto, teríamos repetição.
						$$.traducaoDeclaracaoDeVariaveis = $6.traducaoDeclaracaoDeVariaveis;

						$$.traducao = $3.traducao + $6.traducao;
						
						//$$.traducao = incluirBreakEContinue($$.traducao,"",tagFim,true);									
						//$$.traducao = substituirVariaveisCase($$.traducao, $3.label);									
						
					}
					else{
						yyerror(MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO);	
					}
				}
				;

CASES	: CASE CASES
		{
			if($1.tipo == $2.tipo){
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $2.traducao;
				$$.tipo = $1.tipo;	
			}else{
				yyerror(MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO);
			}
			
		}
		|
		CASE
		;

CASE	: TK_CASE TERMO ':' COMANDO
		{

			if( ($2.tipo == constante_tipo_inteiro || $2.tipo == constante_tipo_caracter) && 
				$2.label.find(prefixo_variavel_usuario) != -1 ){
				
				$$.label = gerarNovaVariavel();

				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis + $4.traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";
				$$.tipo = $2.tipo;
				
				//if($2.tipo == constante_tipo_break)

				$$.traducao = "\t" + $$.label + " = " + tarja_variavel + " == " + $2.label + ";\n" +
								"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + $4.traducao; //+  
								//"\t" + "goto " + tarja_tagFim + ";\n";			

				if(haContinueNoBloco($4.traducao)){
					yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
				}else{
					$$.traducao = "\t" + $$.label + " = " + tarja_variavel + " == " + $2.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + $4.traducao; //+  
									//"\t" + "goto " + tarja_tagFim + ";\n";
				}

			}else{
				yyerror(MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO);
			}
		}
		;

//incluirBreakEContinue(string traducao, string tagInicio, string tagFim, bool ehSwitch)

				/*

				#define tarja_variavel .....  //.....
				#define tarja_tagFim **********  //**********
				
				temp3 = USER_var(.....) == temp2;
				if(temp3) 
					BLOCO 1;	
				*/

E_BREAK_CONTINUE	: TK_BREAK
					{	
						string salvadorPatria = "\t";
						$$.traducao = salvadorPatria + "goto " + tarja_break + ";\n";

						//EXECUTAR AQUI A FUNÇÃO QUE VAI DESEMPILHA
						//string tagBreak = pilhaTagsBreak->obterTopo();
						//pilhaTagsBreak->desempilhar();
						/*
						$$.traducao = "\t" + "goto " + tagBreak + ";\n"
						$$.tipo = constante_tipo_break;
						*/
						/*
						if(tagBreak.find(tag_while_fim) != std::string::npos || tagBreak.find(tag_dowhile_fim) != std::string::npos
							|| tagBreak.find(tag_for_fim) != std::string::npos || tagBreak.find(tag_switch_fim) != std::string::npos){
							
							$$.traducao = "\t" + "goto " + tagBreak + ";\n"
							$$.tipo = constante_tipo_break; 
						}else{
							yyerror(MSG_ERRO_BREAK_NAO_PERMITIDO);
						}
						*/
					}
					|
					TK_CONTINUE
					{
						string salvadorPatria = "\t";
						$$.traducao = salvadorPatria + "goto " + tarja_continue + ";\n";

						//EXECUTAR AQUI A FUNÇÃO QUE VAI DESEMPILHA
						//string tagContinue = pilhaTagsContinue->obterTopo();
						//pilhaTagsContinue->desempilhar();
						/*
						$$.traducao = "\t" + "goto " + tagContinue + ";\n"
						$$.tipo = constante_tipo_continue;
						*/
						/*
						if(tagContinue.find(tag_while_inicio) != std::string::npos || 
							tagContinue.find(tag_dowhile_inicio) != std::string::npos || 
							tagContinue.find(tag_for_inicio) != std::string::npos){
							
							$$.traducao = "\t" + "goto " + tagContinue + ";\n"
							$$.tipo = constante_tipo_continue; 
						}else{
							yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
						}
						*/
					}
					;

/* break ---> do-while, while, for, switch
	continue ----> do-while, while, for

	#define tag_if_fim "FIM_IF"
	#define tag_if_else "IF_TRUE"
	#define tag_while_inicio "INICIO_WHILE"
	#define tag_while_fim "FIM_WHILE"
	#define tag_dowhile_inicio "INICIO_DOWHILE"
	#define tag_dowhile_fim "FIM_DOWHILE"
	#define tag_for_inicio "INICIO_FOR"
	#define tag_for_fim "FIM_FOR"
	#define tag_switch_fim "FIM_SWITCH"

	if (s1.find(s2) != std::string::npos) {
		std::cout << "found!" << '\n';
	}

*/

/*TERMO	: TK_NUM ; ID ; TK_CHAR*/

/*

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


*for ---> for(Init;Test;Update)

INIT
INICIO_FOR:
	E_REL
	tempA = !tempE_REL;
	if(tempA)
		goto FIM_FOR;
	COMANDO;
	UPDATE;
	goto INICIO_FOR;
FIM_FOR:

struct ATRIBUTOS
{
	string label; //Texto lido do lex (para tokens) e variável temporária referente a expressão.
	string traducaoDeclaracaoDeVariaveis; //Para colocação do atributo no início do código.
	string traducao; //Tradução do código atual.
	string tipo; //Tipo resultante atual da tradução.
};

*/ 
			
%%

#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL > tabelaDeVariaveis;
extern int yylineno; //Mostra a linha atual do arquivo fonte.
//extern int yychar; //Mostra o número do token responsável pelo erro.

int yyparse();

int main( int argc, char* argv[] )
{
	
	mapaTipos = criarMapa();
	inicializarMapaDeContexto();
	//pilhaTags;
	yyparse();
	
	

	return 0;
}

ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;				
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
	
	string label_old = dolarDolar.label;
	
	if(resultado == constante_erro)
	{
		string params[3] = {dolar1.tipo, dolar3.tipo, op};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
	}
		
	else if(dolar1.tipo == dolar3.tipo && (dolar1.tipo == resultado)) //se não houver necessidade de conversão
	{
				
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
	}
	
	
	else if(dolar3.tipo == resultado) 
	{
		
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
		
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + label_old + " " + op + " " + dolar3.label + ";\n";
	}
	else if(dolar1.tipo == resultado)
	{
			
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + label_old + ";\n";
		
	}
	
	dolarDolar.tipo = resultado;
	return dolarDolar;	
}



ATRIBUTOS tratarExpressaoRelacional(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t\t" + constante_tipo_inteiro + " " + dolarDolar.label + ";\n";
	
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo,op);
	
	string label_old = dolarDolar.label;
	string operador = op;
	
/*	string varConvert = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
	*/
	if(resultado == constante_erro)
	{
		string params[3] = {dolar1.tipo, dolar3.tipo, op};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
		
	else if(dolar1.tipo == dolar3.tipo)
	{
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
			string varConvert = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
	
			dolar1.label = varConvert;
			varConvert = gerarNovaVariavel();
	
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
			dolar3.label = varConvert;
		}
							
	}
	
	
	else if(dolar3.tipo == resultado)
	{
		string varConvert = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
		dolar1.label = varConvert;
	}
	
	else if(dolar1.tipo == resultado)
	{
		string varConvert = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
		dolar3.label = varConvert;
		
	}
	
	dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label +" "+ op +" "+ dolar3.label + ";\n";
	
	dolarDolar.tipo = constante_tipo_booleano;
	
	
	return dolarDolar;
	
}


string constroiPrint(string tipo, string label){
	string print = "printf(\"\%";
	if(tipo == constante_tipo_flutuante){
		print = print + "f\\n\\n\", ";
	} else if( tipo == constante_tipo_inteiro || constante_tipo_booleano){
		print = print + "d\\n\\n\", ";	
	}else if(tipo == constante_tipo_caracter){
		print = print + "c\\n\\n\", ";
	}
	
	print = print + label + ");\n\n";
	return print;
}

bool verificarPossibilidadeDeConversaoExplicita(string tipoOrigem, string tipoDestino){
	
	return tipoOrigem != constante_tipo_booleano;
}

void yyerror( string MSG )
{
	cout << "Linha " << yylineno << ": " << MSG << endl;
	exit (0);
}				
