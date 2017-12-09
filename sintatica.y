%{
#include <iostream>
#include <string>
#include <algorithm> 
#include <sstream>
#include <map>
#include <vector>



#include "MapaTipos.h"
#include "MensagensDeErro.h"
#include "ControleDeVariaveis.h"
#include "Atributos.h"
#include "TratamentoString.h"
#include "EntradaESaida.h"
#include "controleDeFluxo.h"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo boolean"
#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_TIPOS_DIFERENTES "Os operandos de expressões relacionais precisam ser do mesmo tipo"
//#define prefixo_variavel_sistema "temp"

#define YYDEBUG 0

using namespace std;

using namespace MapaTipos;
using namespace ControleDeVariaveis;
using namespace MensagensDeErro;
using namespace Atributos;
using namespace TratamentoString;
using namespace EntradaESaida;
using namespace ControleDeFluxo;

int yylex(void);
void yyerror(string);
bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);
//string gerarNovaVariavel();

ATRIBUTOS tratarDeclaracaoSemAtribuicao(ATRIBUTOS);
ATRIBUTOS tratarDeclaracaoComAtribuicao(ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS, ATRIBUTOS);

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_STRING

%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL

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

%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL TK_TIPO_STRING TK_PALAVRA_VAR TK_PALAVRA_PRINT TK_PALAVRA_SCAN
%token TK_BACKSCOPE TK_PALAVRA_GLOBAL
%token TK_FIM TK_ERROR
%token TK_CONVERSAO_EXPLICITA

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


S	 		: DECLARACOES_GLOBAIS TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n#define TAMANHO_INICIAL_STRING 10\n#define FATOR_MULTIPLICADOR_STRING 2\n#define FATOR_CARGA_STRING 1\n\n" << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << $1.traducao << endl << $6.traducao << "FIMCODINTER:\treturn 0;\n}" << endl;
			}
			;

UP_S		:
			{
				aumentarEscopo();
			}
			;

BLOCO		: UP_S '{' COMANDOS '}'
			{
				$$.traducao =  $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao =  $$.traducao + "\n" + $3.traducao;
				diminuirEscopo();
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducaoDeclaracaoDeVariaveis = substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) + $2.traducaoDeclaracaoDeVariaveis;
				if($1.traducao != "" && $1.tipo != constante_tipo_bloco){
					$$.traducao = $1.traducao + "\n";// + constroiPrint($1.tipo, $1.label);
				}
				$$.traducao = $$.traducao + $2.traducao;
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
			E_FLUXO_CONTROLE
			|
			E_BREAK_CONTINUE ';'
			|
			INICIO_DECLARACAO
			|
			BLOCO
			{
				$$.traducao = "\t{\n" + $1.traducao + "\t}\n";
				$$.tipo = constante_tipo_bloco;
				$$.label = "";
				$$.traducaoDeclaracaoDeVariaveis = "";
			}
			|
			PRINT
			|
			SCAN
			;
			
			
PRINT			: TK_PALAVRA_PRINT '(' ARG_PRINT ')' ';'
			{
			
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;
			
			}
			;

			
ARG_PRINT		: STRING
			{

				$$.traducao = $1.traducao + "\n" + constroiPrint($1.label);
				
			}
			|
			ID
			{	
				DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
				$$.label = metaData.nome;
				$$.tipo = metaData.tipo;
				$$.traducao = $1.traducao + "\n" + constroiPrint($$.label);
				
			}
			|
			E
			{
				
				$$.traducao = $1.traducao + "\n" + constroiPrint($1.label);
			}
			|
			E_LOGICA
			{
				
				$$.traducao = $1.traducao + "\n" + constroiPrint($1.label);
			}
			|
			E_REL
			{
				$$.traducao = $1.traducao + "\n" + constroiPrint($1.label);
			}
			;
SCAN			: TK_PALAVRA_SCAN '(' ARGS_SCAN ')'';'
			{
				//cout << " // Entrei em TK_PALAVRA_SCAN '(' ARGS_SCAN ')'';' \n";
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;
	
			}
			;		

ARGS_SCAN		: ARG_SCAN ',' ARGS_SCAN 
			{
				//cout << $3.traducao << " *******\n";
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis + $1.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao + $1.traducao;
			
			}
			|
			ARG_SCAN
			
			;
			
ARG_SCAN		: ID ':' TIPO	
			{
	//			cout << "\n//Entrou em ID TIPO\n";
				int tamanho = 0;
				bool ehDinamica = true;
				$$.label = gerarNovaVariavel();
				string dolarDolar = $$.label;
				
				//cout << "label1\n";
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $3.label + " " + $$.label + ";\n";
				//cout << "label2\n";
			//	cout << "$$label: " << $$.label << endl;
			//	cout << "$1label: " << $1.label << endl;
				DADOS_VARIAVEL metadata;
				if($1.escopoDeAcesso >= 0)
				{
					metadata = recuperarDadosVariavel($1.label, $1.escopoDeAcesso);
				}
				else
				{
					metadata = recuperarDadosVariavel($1.label);
				}	
				
				//cout << "label3\n";
				if(metadata.tipo == ""){
					metadata.tipo = $3.tipo;
					metadata.ehDinamica = ehDinamica;
					if($1.escopoDeAcesso >= 0)
					{
						adicionarDefinicaoDeTipo($1.label, $3.tipo, tamanho,ehDinamica, $1.escopoDeAcesso);
						atualizarNoMapa(metadata, $1.escopoDeAcesso);
					}
					else
					{	
						//cout << "label5.1\n";
						adicionarDefinicaoDeTipo($1.label, $3.tipo,tamanho,ehDinamica);
						//cout << "label5.2\n";
						atualizarNoMapa(metadata);
						//cout << "label5.3\n";
					}
				}
				else if(metadata.tipo != $3.tipo)
				{
				//TODO: criar mensagem de erro própria para o input
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[3] = {$1.label.replace(0, strPrefixoVarUsuario.length(), ""), $1.tipo, $3.tipo};
				yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
				}
				
				if($3.tipo == constante_tipo_string)
				{
					//adicionarDefinicaoDeTipo($1.label, $3.tipo,tamanho,ehDinamico);
					$$ = traducaoStringDinamica($$, $1.label);
					$$.traducao = $$.traducao + montarCopiarString($1.label, $$.label) + ";\n";
	
				}
		
				else
				{
					$$.traducao =  constroiScan($$.label, $3.tipo);
					if($3.tipo == constante_tipo_booleano)
					{
						$$ = validarEntradaBooleanEmTempoExecucao($$);
						
					}
								
					
					//adicionarDefinicaoDeTipo($1.label, $3.label,tamanho,ehDinamico);
					$$.traducao = $$.traducao + "\t" + $1.label + " = " + dolarDolar + ";\n";
				
				}	
				
				//cout << "label4\n";

				//cout << "label5\n";
			//	if(metadata.tipo == constante_tipo_string)
			//	{
				//cout << "labelx";

			//	}
				
				//cout << "label6\n";
				$1.tipo = $3.tipo;
				$1.ehDinamica = metadata.ehDinamica;
				//$$.ehDinamica = metadata.ehDinamica;
				//cout << "label7\n";
				
				
				
		
			}
			;
TIPO: TK_TIPO_INT
	|
	TK_TIPO_FLOAT
	|
	TK_TIPO_CHAR
	|
	TK_TIPO_BOOL
	|
	TK_TIPO_STRING
	;
					
//Para declaração de variáveis globais.
DECLARACOES_GLOBAIS: INICIO_DECLARACAO DECLARACOES_GLOBAIS
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			;


INICIO_DECLARACAO	: CRIACAO_VARIAVEL ',' MULTI_DECLARACAO ';'
					{
						$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $1.traducao + $3.traducao;
					}
					|
					CRIACAO_VARIAVEL ';'
					|
					ATRIBUICAO_VARIAVEL ';'
					;

MULTI_DECLARACAO	: ATRIBUICAO_VARIAVEL_CRIACAO ',' MULTI_DECLARACAO
					{
						$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $1.traducao + $3.traducao;
					}
					|
					ATRIBUICAO_VARIAVEL_CRIACAO 
					;

CRIACAO_VARIAVEL	: TK_PALAVRA_VAR TK_ID
					{
						$$ = tratarDeclaracaoSemAtribuicao($2);
						$$.tipo = constante_tipo_criacao_sem_atribuicao;
						$$.label = $2.label;
					}
					|
					TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO
					{
						$$ = tratarDeclaracaoComAtribuicao($2,$4);
					}
					;
					
ATRIBUICAO_VARIAVEL_CRIACAO	:  TK_ID '=' VALOR_ATRIBUICAO
					{
						$$ = tratarDeclaracaoComAtribuicao($1,$3);
					}
					|
					TK_ID
					{
						$$ = tratarDeclaracaoSemAtribuicao($1);
					}
					;
										
ATRIBUICAO_VARIAVEL	:  ID '=' VALOR_ATRIBUICAO
					{
						cout << "//Entrou em ID '=' VALOR_ATRIBUICAO\n";
						$$ = tratarAtribuicaoVariavel($1,$3);
						/*cout << "--ATRIBUICAO_VARIAVEL----------------\n";
						//cout << "label1: " << dolar1.label << " tamaho: " << dolar1.tamanho << endl;
						//cout << "label3: " << dolar3.label << " tamaho: " << dolar3.tamanho << endl;
						cout << "label$$: " << $$.label << " tamaho: " << $$.tamanho << endl;
						cout << "------------------\n";*/
					}
					;
			
//REGRA CRIADA PRA DIMINUIR A QUANTIDADE DE REPETIÇÕES DAS VERIFICAÇÕES DE EXISTENCIA DE VARIAVEL
ID			: TK_ID
			{
				if(variavelJaDeclarada($1.label))
				{
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
					$$.tamanho = metaData.tamanho;
				}
				else
				{
					string params[1] = {$1.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA ,params, 1));
				}
			}
			|
			'(' TK_BACKSCOPE TK_NUM ')' TK_ID
			{
				if($3.tipo != constante_tipo_inteiro){
					string params[1] = {$3.tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_PARAMETRO_BACKSCOPE_DEVE_SER_INTEIRO, params, 1));
				}
				
				int qtdRetornoEscopo = stoi($3.label);
				if(ehMaiorIgualQueEscopoAtual(qtdRetornoEscopo))
					yyerror(montarMensagemDeErro(MSG_ERRO_PARAMETRO_BACKSCOPE_MAIOR_OU_IGUAL_ESCOPO_ATUAL));
				
				int escopo = escopoResultante(qtdRetornoEscopo);

				if(variavelJaDeclarada($5.label, true, escopo)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($5.label, escopo);
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
					$$.escopoDeAcesso = escopo;
				}else{
					string params[1] = {$5.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
			|
			'(' TK_PALAVRA_GLOBAL ')' TK_ID
			{
				if(variavelJaDeclarada($4.label, false, 0)){
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($4.label, 0);
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
					$$.escopoDeAcesso = 0;
				}else{
					string params[1] = {$4.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
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
			{
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra ID: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if($1.label.find(prefixo_variavel_usuario) == 0 && $1.tipo == ""){
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {$1.label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}

				if($1.tipo == constante_tipo_booleano){
					$1.label.replace($1.label.find("_"), 1, "__");
				}
				
				DADOS_VARIAVEL metadata = recuperarDadosVariavel($1.label);
				
				if(metadata.ehDinamica > 1) //caso o metadata recuperado não existisse, bugava, colocando valor como 255
					metadata.ehDinamica = 0;
				
				$1.ehDinamica = metadata.ehDinamica;
				$1.tamanho = metadata.tamanho;
				//$1.tipo = metadata.tipo; //pode ser que precise
				
				$$ = $1;
			}
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
/*			{
				//cout << "Entrou em E de VALOR_ATRIBUICAO: \n\n\n";
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra TERMO: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if($1.label.find(prefixo_variavel_usuario) == 0 && $1.tipo == ""){
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {$1.label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}
				
				
				
				$$ = $1;
			}*/
			//|
			//E_UNARIA
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
					$$.tamanho = $1.tamanho;
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
				//cout << "Entrou em E+E: \n\n\n";
				$$ = tratarExpressaoAritmetica("+", $1, $3);
						
			}
			|
			E '-' E
			{
				//cout << "Entrou em E-E: \n\n\n";
				$$ = tratarExpressaoAritmetica("-", $1, $3);
			}
			|
			E1
			;

E1 			: E1 '*' E1
			{
				//cout << "Entrou em E*E: \n\n\n";
				$$ = tratarExpressaoAritmetica("*", $1, $3);
				
			}
			|
			E1 '/' E1
			{
				//cout << "Entrou em E/E: \n\n\n";
				$$ = tratarExpressaoAritmetica("/", $1, $3);
			}
			|
			'(' E ')'
			{
				//cout << "Entrou em (E): \n\n\n";
				$$ = $2;
			}
			|
			'(' E1 ')'
			{
			//	cout << "Entrou em (E1): \n\n\n";
				$$ = $2;
			}
			|
//ainda em duvida sobre este caso
//talvez seja somente usar o proprio E1
			 
			'(' '-' TERMO ')'
			{
			//	cout << "Entrou em (-TERMO): \n\n\n";
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
			//	cout << "Entrou em TK_CONVERSAO_EXPLICITA E: \n\n\n";
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
			
			|
			STRING
			;
			
STRING			: TK_STRING
			{
			//	cout << "Entrou em TK_STRING\n";
				$$.label = gerarNovaVariavel();
				int tamString = $1.label.length();
				string codigoTraduzido = geraDeclaracaoString($$.label, $1.label,&tamString);
				
				$$.tamanho = tamString; //tamanho modificado pelo tratamento caracteres especiais;
				$$.traducaoDeclaracaoDeVariaveis = "\tchar " + $$.label + "[" + to_string($$.tamanho) + "];\n";
				$$.traducao = codigoTraduzido;
				$$.tipo = $1.tipo;
				
				
			}
			;
						
E_UNARIA	:'-' TERMO
			{
				//cout << "Entrou em TERMO de E_UNARIA\n";
				$$.label = $2.label;
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao + "\t" + $$.label + " = " + $$.label + " * (-1);\n";
				$$.tipo = $2.tipo; 
			}
			|
			'+' '+' TERMO
			{
				//cout << "Entrou em ++TERMO de E_UNARIA\n";
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $$.label + " + 1;\n";
				$$.tipo = $3.tipo;
			}
			|
			'-' '-' TERMO
			{
				//cout << "Entrou em --TERMO de E_UNARIA\n";
				$$.label = $3.label;
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $3.traducao + "\t" + $$.label + " = " + $$.label + " - 1;\n";
				$$.tipo = $3.tipo;
			}
			;

E_LOGICA	: E_LOGICA TK_OP_LOGICO_BIN E_LOGICA
			{
				//cout << "Entrou em E_LOGICA TK_OP_LOGICO_BIN E_LOGICA de E_LOGICA\n";
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
				//cout << "Entrou em TK_OP_LOGICO_UNA E_LOGICA de E_LOGICA\n";
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
			{
				if($1.label.find(prefixo_variavel_usuario) == 0 && $1.tipo == "")
				{
					string strPrefixoVarUsuario = prefixo_variavel_usuario;
					string params[1] = {$1.label.replace(0, strPrefixoVarUsuario.length(), "")};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}
				
				$1.label.replace($1.label.find("_"), 1, "__");
/*
				if($1.tipo == "")
					adicionarDefinicaoDeTipo($1.label, constante_tipo_inteiro);
				$1.tipo = constante_tipo_booleano;
*/
				$$ = $1;
			}
			|
			TK_BOOL
			{
				string nomeUpperCase = $1.label;
				transform(nomeUpperCase.begin(), nomeUpperCase.end(), nomeUpperCase.begin(), ::toupper);
				$$.label = nomeUpperCase;
				incluirNoMapa($$.label,0, $1.tipo);
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
			;

E_REL	: TERMO_REL TK_OP_RELACIONAL TERMO_REL
			{
				cout << "//Entrou em TERMO_REL TK_OP_RELACIONAL TERMO_REL\n";
				$$ = tratarExpressaoRelacional($2.label,$1,$3);	
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

COMANDO_IF	: TK_IF '(' E_LOGICA ')' COMANDO %prec IFX
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis + "\t" +
													constante_tipo_inteiro + " " + $$.label + ";\n";
				
				string tagFim = gerarNovaTagIf(true);				

				$$.traducao = $3.traducao + "\t" + $$.label + " = " + "!" + $3.label + ";\n" + 
							"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" + 
							$5.traducao + "\t" + tagFim + ":;\n"; 			
			}
			|
			TK_IF '(' E_LOGICA ')' COMANDO TK_ELSE COMANDO
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
								$5.traducao + "\t" + tagFim + ":;\n";				
			}
			;

EMPILHAR_TAG_WHILE	:
					{ 
						string tagInicio = gerarNovaTagWhile(false);
						string tagFim = gerarNovaTagWhile(true);
						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);
					}
					;

COMANDO_WHILE	: EMPILHAR_TAG_WHILE TK_WHILE '(' E_LOGICA ')' COMANDO
				{					
					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();
					
					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + $6.traducaoDeclaracaoDeVariaveis + 
														"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";

					$$.traducao = "\t" + tagInicio + ":\n" + $4.traducao + "\t" + $$.label + " = " + "!" + $4.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									$6.traducao + "\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":;\n";

					removerTopoTagInicio();
					removerTopoTagFim();  
				}
				;

EMPILHAR_TAG_DOWHILE	:
					{ 
						string tagInicio = gerarNovaTagDoWhile(false);
						string tagFim = gerarNovaTagDoWhile(true);
						
						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);
					}
					;

COMANDO_DOWHILE	: EMPILHAR_TAG_DOWHILE TK_DO COMANDO TK_WHILE '(' E_LOGICA ')' ';' //PROBLEMAS COM O COMANDO ----> RESOLVIDO
				{					
					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();

					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $6.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis + 
														"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";

					$$.traducao = "\t" + tagInicio + ":\n" + $3.traducao + 
									$6.traducao + "\t" + $$.label + " = " + "!" + $6.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									"\t" + "goto " + tagInicio + ";\n" +
									"\t" + tagFim + ":;\n";

					removerTopoTagInicio();
					removerTopoTagFim();
				}
				;

INIT	: INIT_VAR
		|
		{ //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
			$$.traducaoDeclaracaoDeVariaveis = "";
			$$.traducao = "";
			$$.label = "";
			$$.tipo = "";
		}
		;


INIT_VAR	: INITS ',' INIT_VAR 
		{
			$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
			$$.traducao = $1.traducao + $3.traducao;
		}
		|
		INITS
		;

INITS	: CRIACAO_VARIAVEL
		{
			if($1.tipo == constante_tipo_criacao_sem_atribuicao){
			
				string params[1] = {$1.label};
				yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_SEM_ATRIBUICAO_FOR,params,1));
			}else{
				$$ = $1;
			}
		}
		/*
		TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO
		{
			$$ = tratarDeclaracaoComAtribuicao($2,$4);
		}
		*/
		|
		ATRIBUICAO_VARIAVEL
		;
		
CONDICAO	: E_LOGICA
			| 
			{ //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
				/*
				$$.traducaoDeclaracaoDeVariaveis = "";
				$$.traducao = "";
				$$.label = "";
				$$.tipo = constante_tipo_condicao_vazia_for;
				*/
				yyerror(MSG_ERRO_FOR_SEM_CONDICAO);			
			}
			;
		
//Separação feita para evitar o reconhecimento de sentenças que finalizem com ','.
UPDATE	: UPDATE_VAR
		| 
		{ //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
			$$.traducaoDeclaracaoDeVariaveis = "";
			$$.traducao = "";
			$$.label = "";
			$$.tipo = "";		
		}
		;

UPDATE_VAR	: UPDATES ',' UPDATE_VAR 
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $3.traducao;
			}
			| 
			UPDATES
			;

	
UPDATES	: ATRIBUICAO_VARIAVEL
		| 
		E_UNARIA
		/*
		{
			string numNeg = "(-1)";
			if($1.traducao.find(numNeg) == std::string::npos){
				$$ = $1;
			}else{
				yyerror(MSG_ERRO_UPDATE_FOR_SEM_ATRIBUICAO);
			}	
		}
		*/
		;


EMPILHAR_TAG_FOR	: 
					{	
						//string tagInicio = gerarNovaTagFor(false);
						string tagInicio = gerarNovaTagUpdateFor();
						string tagFim = gerarNovaTagFor(true);
						adicionarTagInicio(tagInicio);
						adicionarTagFim(tagFim);
						
						//cout << "TRADUCAO VAZIA DE EMPILHAR_TAG_FOR:" << endl << endl << $$.traducao;
					}
					;
 
COMANDO_FOR	: EMPILHAR_TAG_FOR TK_FOR '(' INIT ';' CONDICAO ';' UPDATE ')' COMANDO
			{				
				string tagInicio = gerarNovaTagFor(false);
				string tagUpdate = obterTopoPilhaInicio();
				string tagFim = obterTopoPilhaFim();
								
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + $6.traducaoDeclaracaoDeVariaveis +
													$8.traducaoDeclaracaoDeVariaveis + $10.traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";
					
				//if($6.tipo != constante_tipo_condicao_vazia_for){

					$$.traducao = $4.traducao + "\t" + tagInicio + ":\n" + 
									$6.traducao + "\t" + $$.label + " = " + "!" + $6.label + ";\n" +
									"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
									$10.traducao + "\t" + tagUpdate + ":\n" + 
									$8.traducao + "\t" + "goto " + tagInicio + ";\n" + 
									"\t" + tagFim + ":;\n";
				//}else{
					/*
					$$.traducao = $4.traducao + "\t" + tagInicio + ":\n" + 
									$10.traducao + $8.traducao + "\t" + "goto " + tagInicio + ";\n" + 
									"\t" + tagFim + ":\n";
					*/				
				//}

				removerTopoTagInicio();
				removerTopoTagFim();		
			}
			;

EMPILHAR_TAG_SWITCH	:
					{ 
						pair<string,int> tagFim = gerarNovaTagSwitch(false);						
						adicionarTagFim(tagFim.first);
					}
					;

COMANDO_SWITCH	: EMPILHAR_TAG_SWITCH TK_SWITCH '(' ID ')' '{' CASES DEFAULT'}'
				{				
					//$3.tipo != constante_tipo_string && $3.tipo != constante_tipo_flutuante
					if($4.tipo == $7.tipo) {
						//(...)
						//pair<string,int> tagFimENumProx = gerarNovaTagSwitch(false);
						//string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second);
						pair<string,int> tagFimENumProx = gerarNovaTagSwitch(true);
						string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second-1);
						
						
						//string tagFim = gerarNovaTagSwitch(false).first;
						
						//$$.label = gerarNovaVariavel();
						
						//Outra parte da árvore já tera a $3.traducaoDeclaracaoDeVariaveis salva. Portanto, teríamos repetição.
						$$.traducaoDeclaracaoDeVariaveis = $7.traducaoDeclaracaoDeVariaveis + $8.traducaoDeclaracaoDeVariaveis;

						if($8.tipo == constante_tipo_default){

							$$.traducao = $4.traducao + $7.traducao + $8.traducao +
										//"\t" + "goto " + tagFim + ";\n"
										//"\t" + tagFimENumProx.first + ":\n";
										"\t" + obterTopoPilhaFim() + ":;\n";
												
						}else{
							$$.traducao = $4.traducao + $7.traducao + $8.traducao +
										//"\t" + "goto " + tagFim + ";\n"
										"\t" + tagCaseAtual + ":\n" +
										//"\t" + tagFimENumProx.first + ":\n";
										"\t" + obterTopoPilhaFim() + ":;\n";
						}
															
						$$.traducao = substituirVariaveisCase($$.traducao, $4.label);
						removerTopoTagFim();									
						
					}
					else{
						yyerror(MSG_ERRO_TIPO_CASE_DISTINTO);	
					}
				}
				;

DEFAULT	: TK_DEFAULT ':' COMANDO
		{
			pair<string,int> tagFimENumProx = gerarNovaTagSwitch(true);
			string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second-1);
			
			$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
			$$.traducao = "\t" + tagCaseAtual + ":\n" + $3.traducao;
			$$.tipo = constante_tipo_default;
		}
		| //MESMO PROBLEMA DO BLOCO REPETIDO NO FINAL!
		{
			$$.traducaoDeclaracaoDeVariaveis = "";
			$$.traducao = "";
			//$$.label = "";
			//$$.tipo = "";
		}
		;


CASES	: CASE CASES
		{
			$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
			$$.traducao = $1.traducao + $2.traducao;
			$$.tipo = $2.tipo;				
		}
		|
		CASE
		;

CASE	: TK_CASE TERMO ':' COMANDO
		{		
			//Regra TERMO possui produção que leva em ID, o que não pode.
			if( ($2.tipo == constante_tipo_inteiro || $2.tipo == constante_tipo_caracter) && 
				$2.label.find(prefixo_variavel_usuario) == std::string::npos){
				
				pair<string,int> tagCaseENumProx = gerarNovaTagSwitch(true);
				string proxCase = tag_case_inicio + to_string(tagCaseENumProx.second);
								
				$$.label = gerarNovaVariavel();

				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis + $4.traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + $$.label + ";\n";
				$$.tipo = $2.tipo;
								
				//Adicionar a tag do inicio do case antes do comando em si.
				string salvadorDaPatria = "\t";
				$4.traducao = salvadorDaPatria + "{\n" + "\t" + tagCaseENumProx.first + ":\n" + $4.traducao + 
													"\t" + "goto " + proxCase + ";\n" + "\t" + "}\n"; 

				$$.traducao =  $2.traducao + "\t" + $$.label + " = " + tarja_variavel + " == " + $2.label + ";\n" +
								"\t" + "if" + "(" + $$.label + ")\n" + $4.traducao; //+
								//"\t" + "goto " + proxCase + ":\n"; //+  
								//"\t" + "goto " + tarja_tagFim + ";\n";			
			}else{
				yyerror(MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO);
			}
		}
		;

E_BREAK_CONTINUE	: TK_BREAK
					{	
						string salvadorDaPatria = "\t";
						if(!pilhaFimVazia()){
							$$.traducao = salvadorDaPatria + "goto " + obterTopoPilhaFim() + ";\n";
						}else{
							yyerror(MSG_ERRO_BREAK_NAO_PERMITIDO);
						}	
					}
					|
					TK_CONTINUE
					{
						string salvadorDaPatria = "\t";
						if(!pilhaInicioVazia()){
							$$.traducao = salvadorDaPatria + "goto " + obterTopoPilhaInicio() + ";\n";
						}else{
							yyerror(MSG_ERRO_CONTINUE_NAO_PERMITIDO);
						}
					}
					;
 			
%%

#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL> tabelaDeVariaveis;
extern int yylineno; //Define a linha atual do arquivo fonte.

int yyparse();

int main( int argc, char* argv[] )
{
	
	mapaTipos = criarMapa();
	inicializarMapaDeContexto();
	//inicializarMapaDeStrings();
	//PARA O DEBUG
	//yydebug = 1;
	yyparse();
	
	

	return 0;
}

ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	//cout << "Entrou em exp arti\n";
	ATRIBUTOS dolarDolar;
	
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;				
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);
	
	/*
	a + b
	if(erro)
		print erro;
	
	if(resultado == string)
		tratarString(op, a, b);
	else
		if(a.tipo != resultado)
			escreve conversao;
		if(b.tipo != resultado)
			escreve convesao;
	*/
	
	
	string label_old = dolarDolar.label;
	
	if(resultado == constante_erro)
	{
		//cout << "Deu erro no mapa\n";
		string params[3] = {op,dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
	
	/*
	*TODO	
	*Tratar conversão para tipo String
	*
	*/
	if(resultado == constante_tipo_string)
	{
			
		string traducao = realizarOperacaoAritmeticaString(op, &dolarDolar,&dolar1,&dolar3);
		
		if(traducao == "") //o operador ainda não está implementado. Fiz assim para não alterar no mapa, vou apagar o if
		{
			string params[3] = {op,dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
		
		}
		
		dolarDolar.traducao = dolarDolar.traducao + traducao;
		
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + realizarTraducaoDeclaracaoDeString(op, dolarDolar, dolar1,dolar3);
		
		
			
	
	}
	
	else
	{
		
		if((dolar1.tipo == dolar3.tipo) /*&& (dolar1.tipo == resultado)*/) //se não houver necessidade de conversão
		{
			//cout << "label0\n";	
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + dolar1.tipo + " " + dolarDolar.label + ";\n";
		}
	
	
		else if(dolar1.tipo != resultado) 
		{
			//cout << "label1\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + label_old +  ";\n" + "\t" + resultado + " " + dolarDolar.label +  ";\n";
		
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + label_old + " " + op + " " + dolar3.label + ";\n";
		}
		else if(dolar3.tipo != resultado)
		{
			//cout << "label3\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + label_old +  ";\n" + "\t" + resultado + " " + dolarDolar.label +  ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + label_old + ";\n";
		
		}
	
	}
	
	dolarDolar.tipo = resultado;
	return dolarDolar;	
}



ATRIBUTOS tratarExpressaoRelacional(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis += dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	/*dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t\t" + constante_tipo_inteiro + " " + dolarDolar.label + ";\n";*/
	
	//dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo,op);
	
	//string label_old = dolarDolar.label;
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
	string operador = op;
	
	//FIXME - remover a verificação de string daqui, após a implementação dessa operações corretamente.
	if(resultado == constante_erro || resultado == constante_tipo_string)
	{
		
		string params[3] = {op, dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
		
	if(dolar1.tipo == dolar3.tipo)
	{	
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
	
			//dolar1.label = dolarDolar.label;
			string novaVariavel = gerarNovaVariavel();
	
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + novaVariavel + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + novaVariavel + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
			dolar3.label = novaVariavel;
		}
							
	}
	
	else
	{
		string varConvert = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
	
		if(dolar1.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
			dolar1.label = varConvert;
		}
	
		else if(dolar3.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
			dolar3.label = varConvert;
		
		}
	
	}
	
	dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label +" "+ op +" "+ dolar3.label + ";\n";
	
	dolarDolar.tipo = constante_tipo_booleano;
	
	
	return dolarDolar;
	
}



//TK_PALAVRA_VAR TK_ID ';'
ATRIBUTOS tratarDeclaracaoSemAtribuicao(ATRIBUTOS dolar2){

	ATRIBUTOS dolarDolar;

	if(variavelJaDeclarada(dolar2.label, false)){
		//mensagem de erro dupla declaração
		string params[1] = {dolar2.label};
		yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
	}
	
	else
	{
		dolarDolar.traducaoDeclaracaoDeVariaveis = "\t" + construirDeclaracaoProvisoriaDeInferenciaDeTipo(dolar2.label);
		incluirNoMapa(dolar2.label,0);
	}
				
	return dolarDolar;

}

//TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
ATRIBUTOS tratarDeclaracaoComAtribuicao(ATRIBUTOS dolar2, ATRIBUTOS dolar4)
{

	ATRIBUTOS dolarDolar;
	
	if(variavelJaDeclarada(dolar2.label, false))
	{
		//mensagem de erro dupla declaração
		string params[1] = {dolar2.label};
		yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
	}
	else
	{
		//cout << "Entrou no else: \n\n\n";
		int tamanho = 0;
		string tipo = dolar4.tipo;
		string label = prefixo_variavel_usuario;
		label = label + dolar2.label;
		if(tipo == constante_tipo_booleano)
		{
			tipo = constante_tipo_inteiro;
			tipo = "\t" + tipo;
			label = prefixo_variavel_usuario;
			label = label + "_" + dolar2.label;
		}
		
		if(tipo == constante_tipo_string)
		{
			if(dolar4.ehDinamica)
			{
				tipo = constante_tipo_caracter;
					dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " * " + label+ ";\n";
			
					//cout << dolarDolar.traducaoDeclaracaoDeVariaveis << "EEEEEEEEEEEEEEEEEEE\n";
					//TENTATIVA ATRIBUICAO COM MALLOC
					//dolarDolar.traducao = dolar4.traducao + "\t" + label +" = (char*) malloc(" + to_string(dolar4.tamanho) + ");\n\t" + montarCopiarString(label, dolar4.label) + ";\n";
					
					//TENTATIVA ATRIBUINDO PONTEIRO
					dolarDolar.traducao = dolar4.traducao + "\t" + label +" = "+ dolar4.label + ";\n";
//					dolarDolar.traducao = dolar4.traducao + "\t strcpy(" + label +", \"\");\n\t strcat("+ label + ", "+ dolar4.label + ");\n";
					//dolarDolar.traducao = dolar4.traducao + "\t strcpy(" + label +", \"\");\n";
					
			}
			else
			{
				tipo = constante_tipo_caracter;
				dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + label + "[" + to_string(dolar4.tamanho) + "];\n";
			
				//cout << dolarDolar.traducaoDeclaracaoDeVariaveis << "EEEEEEEEEEEEEEEEEEE\n";
				dolarDolar.traducao = dolar4.traducao + montarCopiarString(label, dolar4.label) + ";\n";
			}
		
		}
		
		else
		{
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + label + ";\n";
			dolarDolar.traducao = dolar4.traducao + "\t" + label + " = " + dolar4.label + ";\n";
		}
		
		incluirNoMapa(dolar2.label,dolar4.tamanho, dolar4.tipo);
		//cout << dolar4.ehDinamica << endl;
		dolarDolar.label = label;
		dolarDolar.tipo = dolar4.tipo;
		dolarDolar.tamanho = dolar4.tamanho;
	}
	
	
	return dolarDolar;
	
}

//ID '=' VALOR_ATRIBUICAO ';'
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{		
	ATRIBUTOS dolarDolar;	
	string tipo = "";
	int tamanho = 0;
	bool ehDinamico = false;	
	if(dolar1.label != dolar3.label)
	{
		DADOS_VARIAVEL metaData;
		if(dolar1.escopoDeAcesso >= 0){
			metaData = recuperarDadosVariavel(dolar1.label, dolar1.escopoDeAcesso);
		}
		else{
			metaData = recuperarDadosVariavel(dolar1.label);
		}
		
		//cout <<"metadata.tamanho: " << metaData.tamanho << endl;
		if(metaData.tipo == "")
		{
			//isso aqui também pode causar problema no futuro devido as lacunas
			metaData.tipo = dolar3.tipo; 
			//atualizarNoMapa(metaData);
			tipo = metaData.tipo;
			if(tipo == constante_tipo_booleano)
			{
				tipo = constante_tipo_inteiro;
				tipo = "\t" + tipo;
			}
			
			if(tipo == constante_tipo_string)
			{		
				metaData.tamanho = dolar3.tamanho;
				
			}
			
			
			if(dolar1.escopoDeAcesso >= 0){
				adicionarDefinicaoDeTipo(dolar1.label, tipo, dolar3.tamanho,ehDinamico, dolar1.escopoDeAcesso);
				atualizarNoMapa(metaData, dolar1.escopoDeAcesso);
			}
			else{
				cout << "//Entrou else " << tipo << endl;;
				adicionarDefinicaoDeTipo(dolar1.label, tipo,dolar3.tamanho,ehDinamico);
				atualizarNoMapa(metaData);
			}
			
			dolar1.tipo = dolar3.tipo;
		}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
		if(dolar1.tipo == dolar3.tipo)
		{ 
			//$1.tamanho = $3.tamanho;
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar3.traducaoDeclaracaoDeVariaveis;

			if(dolar3.tipo == constante_tipo_string)
				dolarDolar.traducao = dolar3.traducao + montarCopiarString(dolar1.label, dolar3.label) + ";\n";	
			else
				dolarDolar.traducao = dolar3.traducao + "\t" + dolar1.label + " = " + dolar3.label + ";\n";
		}
		else
		{
			
			string strPrefixoVarUsuario = prefixo_variavel_usuario;
			string params[3] = {dolar1.label.replace(0, strPrefixoVarUsuario.length(), ""), dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
		}
		
			/*cout << "++tratarAtribuicaoVariavel++++++++++++++++\n";
			cout << "label1: " << dolar1.label << " tamaho: " << dolar1.tamanho << endl;
			cout << "label3: " << dolar3.label << " tamaho: " << dolar3.tamanho << endl;
			cout << "label$$: " << dolarDolar.label << " tamaho: " << dolarDolar.tamanho << endl;
			cout << "++++++++++++++++++\n";*/
		
		dolarDolar.label = dolar1.label;
		dolarDolar.tipo = dolar1.tipo;
		//dolarDolar.tamanho = dolar1.tamanho;
		dolarDolar.tamanho = dolar3.tamanho;
		dolarDolar.ehDinamica = dolar3.ehDinamica;
		
	}
	else
	{
		dolarDolar = dolar3;
	}

	
	return dolarDolar;

}


/*string constroiPrint(string tipo, string label){
	string print = "printf(\"\%";
	if(tipo == constante_tipo_flutuante){
		print = print + "f\\n\\n\", ";
	} else if( tipo == constante_tipo_inteiro || tipo == constante_tipo_booleano){
		print = print + "d\\n\\n\", ";	
	}else if(tipo == constante_tipo_caracter){
		print = print + "c\\n\\n\", ";
	}
	
	print = print + label + ");\n\n";
	return print;
}*/


//declaração de variaveis var <nome variavel>;
/*string gerarNovaVariavel(){
	static int num = 0;
	num++;
	string temp = prefixo_variavel_sistema;

	string numInt = to_string(num);
	return temp + numInt;
}*/

bool verificarPossibilidadeDeConversaoExplicita(string tipoOrigem, string tipoDestino){
	
	return tipoOrigem != constante_tipo_booleano;
}


void yyerror( string MSG )
{
	cout << "Linha " << yylineno << ": " << MSG << endl;
	exit (0);
}				
