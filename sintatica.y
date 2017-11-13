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

#include "Atributos.h"

#include "TratamentoString.h"

#include "EntradaESaida.h"

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo boolean"
#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_TIPOS_DIFERENTES "Os operandos de expressões relacionais precisam ser do mesmo tipo"

using namespace std;

using namespace MapaTipos;
using namespace ControleDeVariaveis;
using namespace MensagensDeErro;
using namespace Atributos;
using namespace TratamentoString;
using namespace EntradaESaida;

int yylex(void);
void yyerror(string);
bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_STRING

%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL

%token TK_MAIN TK_ID TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL TK_TIPO_STRING TK_PALAVRA_VAR TK_PALAVRA_PRINT TK_PALAVRA_SCAN
%token TK_BACKSCOPE TK_PALAVRA_GLOBAL
%token TK_FIM TK_ERROR
%token TK_CONVERSAO_EXPLICITA

%start S

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
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n" << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << $1.traducao << endl << $6.traducao << "\treturn 0;\n}" << endl;
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
					$$.traducao = $1.traducao + "\n" ;//+ constroiPrint($1.tipo, $1.label);
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
			DECLARACAO
			|
			BLOCO
			{
				$$.traducao = "\t{\n" + $1.traducao + "\t}\n";
				$$.tipo = constante_tipo_bloco;
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
			|
			ARG_SCAN
			{
				//cout << $3.traducao << " *******\n";
				
				$$ = $1;
			
			}
			;
			
ARG_SCAN		: ID  TIPO	
			{
				cout << "\n//Entrou em ID  TIPO\n";
				
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $2.traducao;
				
				$$.traducao = $$.traducao + "\n" + constroiScan($2.label);
				$$.traducao = $$.traducao + "\n\t" + $$.label + " = " + $2.label + ";\n"; 
				
		
			}
			;

TIPO			:  TK_TIPO_INT     //criar tipo flutuante
			{
				//cout << "//Entrou em TK_TIPO_INT\n";
				$1.tipo = constante_tipo_inteiro;
				$$.traducaoDeclaracaoDeVariaveis = construirTraducaoEntrada($$.label, $1.label, $1.tipo, $1.tamanho);
				
			
			}
			|
			 TK_TIPO_FLOAT 
			{
				$1.tipo = constante_tipo_flutuante;
				$$.traducaoDeclaracaoDeVariaveis = construirTraducaoEntrada($$.label, $1.label, $1.tipo, $1.tamanho);
			}
			|
			TK_TIPO_CHAR
			{
				$1.tipo = constante_tipo_caracter;
				$$.traducaoDeclaracaoDeVariaveis = construirTraducaoEntrada($$.label, $1.label, $1.tipo, $1.tamanho);
			
			}
			|
			TK_TIPO_BOOL
			{
				//TODO - Implementar o booleano corretamente
				$1.tipo = constante_tipo_inteiro;
				$$.traducaoDeclaracaoDeVariaveis = construirTraducaoEntrada($$.label, $1.label, $1.tipo, $1.tamanho);
			}
			|
			TK_TIPO_STRING
			{
				//TODO - Implementar String dinâmica
				cout << "TK_STRING\n";
				$1.tipo = constante_tipo_caracter;
				$$.traducaoDeclaracaoDeVariaveis = construirTraducaoEntrada($$.label, $1.label, $1.tipo, $1.tamanho);
			
			}
			;

DECLARACOES: DECLARACAO DECLARACOES
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $1.traducao + $2.traducao;
			}
			|
			;
DECLARACAO: TK_PALAVRA_VAR TK_ID ';'
			{
				if(variavelJaDeclarada($2.label, false))
				{
					//mensagem de erro dupla declaração
					string params[1] = {$2.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}
				
				else
				{
					$$.traducaoDeclaracaoDeVariaveis = "\t" + construirDeclaracaoProvisoriaDeInferenciaDeTipo($2.label);
					incluirNoMapa($2.label);
				}
			}
			|
			TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
			{	
				//cout << "Entrou em TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';': \n\n\n";
				if(variavelJaDeclarada($2.label, false))
				{
					//mensagem de erro dupla declaração
					string params[1] = {$2.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL, params, 1));
				}
				else
				{
					//cout << "Entrou no else: \n\n\n";
					string tipo = $4.tipo;
					string label = prefixo_variavel_usuario;
					label = label + $2.label;
					if(tipo == constante_tipo_booleano)
					{
						tipo = constante_tipo_inteiro;
						tipo = "\t" + tipo;
						label = prefixo_variavel_usuario;
						label = label + "_" + $2.label;
					}
					if(tipo == constante_tipo_string)
					{
						tipo = constante_tipo_caracter;
						tipo = "\t" + tipo;
						
					//	$2.label = prefixo_variavel_usuario + $2.label;
					
						$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + $2.label + "[" + to_string($4.tamanho) + "];\n";
						$$.traducao = $4.traducao + montarCopiarString($2.label, $4.label) + ";\n";
					
					}
					
					else
					{
					//	$2.label = prefixo_variavel_usuario + $2.label;
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + label + ";\n";
					$$.traducao = $4.traducao + "\t" + label + " = " + $4.label + ";\n";
					incluirNoMapa($2.label, $4.tipo);
					$$.label = label;
					}
					$$.tipo = $4.tipo;
				}
				
			}
			|
			ID '=' VALOR_ATRIBUICAO ';'
			{
				//cout << "Entrou em ID '=' VALOR_ATRIBUICAO ';': \n\n\n";			
				if($1.label != $3.label)
				{
					DADOS_VARIAVEL metaData;
					if($1.escopoDeAcesso >= 0){
						metaData = recuperarDadosVariavel($1.label, $1.escopoDeAcesso);
					}
					else{
						metaData = recuperarDadosVariavel($1.label);
					}
					if(metaData.tipo == "")
					{
						//isso aqui também pode causar problema no futuro devido as lacunas
						metaData.tipo = $3.tipo;
						
						string tipo = $3.tipo;
						if(tipo == constante_tipo_booleano)
						{
							tipo = constante_tipo_inteiro;
							tipo = "\t" + tipo;
						}
						if($1.escopoDeAcesso >= 0){
							adcionarDefinicaoDeTipo($1.label, tipo, $1.escopoDeAcesso);
							atualizarNoMapa(metaData, $1.escopoDeAcesso);
						}
							adcionarDefinicaoDeTipo($1.label, tipo);
							atualizarNoMapa(metaData);
						}
						
						
						
						adicionarDefinicaoDeTipo($1.label, tipo, $1.tamanho + $3.tamanho);
						
						
						$1.tipo = $3.tipo;
					}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
					if($1.tipo == $3.tipo){
						$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
						if($3.tipo == constante_tipo_string)
							$$.traducao = $$.traducao + $3.traducao + montarCopiarString($1.label, $3.label) + ";\n";	
						else
						$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
					}
					else
					{
						
						string strPrefixoVarUsuario = prefixo_variavel_usuario;
						string params[3] = {$1.label.replace(0, strPrefixoVarUsuario.length(), ""), $1.tipo, $3.tipo};
						yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
					}
					$$.label = $1.label;
					$$.tipo = $1.tipo;
				}
				else
				{
					$$ = $3;
				}
			}
			|
			;

//REGRA CRIADA PRA DIMINUIR A QUANTIDADE DE REPETIÇÕES DAS VERIFICAÇÕES DE EXISTENCIA DE VARIAVEL
ID		: TK_ID
			{
				if(variavelJaDeclarada($1.label))
				{
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
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
			|
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
				//$$.tamanho = $1.label.length() +1 -2; //-2 exclui o tamanho das aspas
				string codigoTraduzido = geraDeclaracaoString($$.label, $1.label);
				$$.tamanho = $1.label.length() +1 -2 - global_numCaracteresEspeciais; //-2 exclui o tamanho das aspas a global vem do namespace TratamentoString
				$$.traducaoDeclaracaoDeVariaveis = "\tchar " + $$.label + "[" + to_string($$.tamanho) + "];\n";
				$$.traducao = codigoTraduzido;
				
			//	cout << mapaStrings[$$.label].valor << "\n";
				
				//cout << $$.traducaoDeclaracaoDeVariaveis << "\n";
				
				$$.tipo = $1.tipo;
				
				global_numCaracteresEspeciais = 0;
				
				
			}
			;			
E_UNARIA	: '-' TERMO
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
					adcionarDefinicaoDeTipo($1.label, constante_tipo_inteiro);
				$1.tipo = constante_tipo_booleano;
*/
				$$ = $1;
			}
			|
			TK_BOOL
			{
				//cout << "Entrou em TK_BOOL de E_LOGICA\n";
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
			;

E_REL	: TERMO_REL TK_OP_RELACIONAL TERMO_REL
			{
				//cout << "Entrou em TERMO_REL TK_OP_RELACIONAL TERMO_REL\n";
				$$ = tratarExpressaoRelacional($2.label,$1,$3);	
			}
			|
			'(' E_REL ')'
			{
				//cout << "Entrou em (E_REL) \n";
				$$ = $2;
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
	yyparse();
	
	

	return 0;
}

ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	
	dolarDolar.label = gerarNovaVariavel();
	
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;				
/*	
//remover esta verificação se for tratar como erro a não atribuição
	if(dolar1.tipo == "" && dolar3.tipo == "")
	{

		dolar1.tipo = constante_tipo_inteiro;
		dolar3.tipo = constante_tipo_inteiro;
		
	}	
	if(dolar1.tipo == "")
	{
		dolar1.tipo = dolar3.tipo;
	}
	if(dolar3.tipo == "")
	{
		dolar3.tipo = dolar1.tipo;
	}	
*/		
	
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);
	
	if(!(dolar1.tipo == constante_tipo_string || dolar3.tipo == constante_tipo_string))
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + dolarDolar.label + ";\n";
	
	string label_old = dolarDolar.label;
	
	if(resultado == constante_erro)
	{
		string params[3] = {op,dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
	
	/*
	*TODO	
	*Tratar caso de ser do tipo String
	*
	*/
	else if(dolar1.tipo == constante_tipo_string && dolar3.tipo == constante_tipo_string)
	{
		//realizando a soma das traduções fora das funções
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + realizarTraducaoDeclaracaoDeString(op, dolarDolar, dolar1,dolar3);
		
		string traducao = realizarOperacaoAritmeticaString(op, dolarDolar,dolar1,dolar3);
		
		if(traducao == "") //o operador ainda não está implementado. Fiz assim para não alterar no mapa, vou apagar o if
		{
			string params[3] = {op,dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
		
		}
			
		
		dolarDolar.traducao = dolarDolar.traducao + traducao;
			
	
	}
		
	else if((dolar1.tipo == dolar3.tipo) && (dolar1.tipo == resultado)) //se não houver necessidade de conversão
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
	
	string varConvert = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + resultado + " " + varConvert + ";\n";
	if(resultado == constante_erro)
	{
		
		string params[3] = {dolar1.tipo, dolar3.tipo, op};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
	}
		
	else if(dolar1.tipo == dolar3.tipo)
	{	
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
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
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
		
		dolar1.label = varConvert;
	}
	
	else if(dolar1.tipo == resultado)
	{
		dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + resultado + ")" + dolar3.label + ";\n";							
		dolar3.label = varConvert;
		
	}
	
	dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label +" "+ op +" "+ dolar3.label + ";\n";
	
	dolarDolar.tipo = constante_tipo_booleano;
	
	
	return dolarDolar;
	
}



bool verificarPossibilidadeDeConversaoExplicita(string tipoOrigem, string tipoDestino){
	
	return tipoOrigem != constante_tipo_booleano;
}


void yyerror( string MSG )
{
	cout << "Linha " << yylineno << ": " << MSG << endl;
	exit (0);
}				
