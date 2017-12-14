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
#include "ControleDeFluxo.h"
#include "TratamentoArray.h"

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
using namespace TratamentoArray;

int yylex(void);
void yyerror(string);
string definicoesDeFuncoes();

bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);
ATRIBUTOS tratarExpressaoAritmetica(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoLogicaBinaria(string, ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarExpressaoLogicaUnaria(string, ATRIBUTOS);
ATRIBUTOS tratarExpressaoRelacional(string, ATRIBUTOS, ATRIBUTOS);
//string gerarNovaVariavel();

ATRIBUTOS tratarDeclaracaoSemAtribuicao(ATRIBUTOS);
ATRIBUTOS tratarDeclaracaoComAtribuicao(ATRIBUTOS, ATRIBUTOS);
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS, ATRIBUTOS, bool ehDinamica = false);

int conta;

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_STRING

%token TK_OP_ARIT_UNA
%token TK_OP_ARIT_PRIO1
%token TK_OP_ARIT_PRIO2
%token TK_OP_ARIT_PRIO3
%token TK_OP_ARIT_COMP
%token TK_OP_LOG_BIN_PRIO1
%token TK_OP_LOG_BIN_PRIO2
%token TK_OP_LOG_UNA
%token TK_OP_REL_PRIO1
%token TK_OP_REL_PRIO2

//******* I

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

%token TK_TIPO_INT TK_TIPO_FLOAT TK_TIPO_CHAR TK_TIPO_BOOL TK_TIPO_STRING TK_PALAVRA_PRINT TK_PALAVRA_SCAN
//%token TK_FIM TK_ERROR //estes tokens só tinham uma referência nesse sintatica se quebrar descomentar
%token TK_CONVERSAO_EXPLICITA
//*********** F

%token TK_PALAVRA_VAR TK_ID
%token TK_BACKSCOPE TK_PALAVRA_GLOBAL

%start S

%nonassoc IFX
%nonassoc TK_ELSE //Eliminar a ambiguidade inerente do if-else. O yacc por naturalidade já o faz, mas isso evita o reconhecimento do mesmo do conflito de shift/reduce.

%nonassoc TK_OP_ARIT_UNA // ++, --
%nonassoc TK_OP_ARIT_COMP // +=, -=, *=, /=, etc... vide slides LP
%left TK_OP_LOG_BIN_PRIO1 // or
%left TK_OP_LOG_BIN_PRIO2 // and
%nonassoc TK_OP_REL_PRIO1 // ==, !=
%nonassoc TK_OP_REL_PRIO2 // <, <=, >, >=
%left TK_OP_ARIT_PRIO1 // +, -
%left TK_OP_ARIT_PRIO2 // *, /
%right TK_OP_LOG_UNA // not
%left TK_OP_ARIT_PRIO3 //**
%right TK_CONVERSAO_EXPLICITA

%%


S	 		: COMANDOS
			{

//				cout << "/*Compilador TriadNewScript*/\n" << "#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n#define TAMANHO_INICIAL_STRING 10\n#define FATOR_MULTIPLICADOR_STRING 2\n#define FATOR_CARGA_STRING 1\n\n" << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\nint main(void)\n{\n" << $1.traducao << endl << $6.traducao << "FIMCODINTER:\treturn 0;\n}" << endl;
				cout << "/*Compilador TriadNewScript*/\n" << "#include <stdio.h>\n#include <stdlib.h>\n#include <iostream>\n#include <string.h>\n#include <sstream>\n\n#define TRUE 1\n#define FALSE 0\n\n" << constroiDefinesParaStringDinamica() << substituirTodasAsDeclaracoesProvisorias($1.traducaoDeclaracaoDeVariaveis) << "\n\n" << definicoesDeFuncoes() << "\nint main(void)\n{\n" << $1.traducao << "FIMCODINTER:\treturn 0;\n}" << endl;
			}
			;

UP_S		:
			{
				aumentarEscopo();
			}
			;

BLOCO		: UP_S '{' COMANDOS '}'
			{
				$$ = $3;
				diminuirEscopo();
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				if($1.traducao != "" && $1.estruturaDoConteudo != constante_estrutura_bloco){
					$$.traducao = $1.traducao + "\n";// + constroiPrint($1.tipo, $1.label);
				}
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
			;

COMANDO 	: E ';'
			|
			BLOCO
			|
			INICIO_DECLARACAO ';'
			|
			PRINT ';'
			|
			SCAN ';'
			|
			E_FLUXO_CONTROLE
			|
			E_BREAK_CONTINUE ';'
			;

E			: E TK_OP_ARIT_PRIO1 E
			{
				$$ = tratarExpressaoAritmetica($2.label, $1, $3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_ARIT_PRIO2 E
			{
				$$ = tratarExpressaoAritmetica($2.label, $1, $3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_ARIT_PRIO3 E
			{
				$$ = tratarExpressaoAritmetica($2.label, $1, $3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_LOG_BIN_PRIO1 E
			{
				$$ = tratarExpressaoLogicaBinaria($2.label, $1, $3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_LOG_BIN_PRIO2 E
			{
				$$ = tratarExpressaoLogicaBinaria($2.label, $1, $3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			TK_OP_LOG_UNA E
			{
				$$ = tratarExpressaoLogicaUnaria($1.label, $2);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_REL_PRIO1 E
			{
				$$ = tratarExpressaoRelacional($2.label,$1,$3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_REL_PRIO2 E
			{
				$$ = tratarExpressaoRelacional($2.label,$1,$3);
				$$.estruturaDoConteudo = constante_estrutura_expressao;
			}
			|
			E TK_OP_ARIT_COMP E
			{}
			|
			'(' E ')'
			{
				$$ = $2;
			}
/*
	//tratar este caso em especifico depois ... teste : var a = 1; (-a); gera sintax error	
			|
			'(' '-' E ')'
			{

			}
*/
			|
			//por enquanto ambos fazem a msm coisa, mas a ideia seria trocar a ordem das operaçõesç
			TK_OP_ARIT_UNA E
			{
				if($2.estruturaDoConteudo == constante_estrutura_variavel)
				{
					$$ = $2;
					$$.traducao = $2.traducao + "\t" + $2.label + " = " + $2.label + " " + $1.label[0] + " 1;\n";
				}
				else
				{
					string params[2] = {
						$1.label,
						"o operando não é uma variável"
					};
					yyerror(montarMensagemDeErro(MSG_ERRO_OPERADOR_UNARIO_INVALIDO_PARA_OPERANDO, params, 2));
				}
			}
			|
			E TK_OP_ARIT_UNA
			{
				if($1.estruturaDoConteudo == constante_estrutura_variavel)
				{
					$$ = $1;
					$$.traducao = "\t" + $1.label + " = " + $1.label + " " + $2.label[0] + " 1;\n" + $1.traducao;
				}
				else
				{
					string params[2] = {
						$2.label,
						"o operando não é uma variável"
					};
					yyerror(montarMensagemDeErro(MSG_ERRO_OPERADOR_UNARIO_INVALIDO_PARA_OPERANDO, params, 2));
				}
			}
			|
			VALOR
			{
				$$ = $1;
				if($1.estruturaDoConteudo == constante_estrutura_variavel)
					$$.label = recuperarNomeTraducao($$.label);

			}
			|
			ARRAY
			;

ARRAY	: '[' DIMENSOES_INDICES ']' //Criação de array
		{
			$$ = $2;
			
			
			//$$.estruturaDoConteudo = constante_estrutura_array;
		}
		/*
		|
		'{' ELEMENTOS '}' //Criação de array com elementos definidos
		{
			$$ = $2;
		}
		|
		ID '[' DIMENSOES_INDICES ']'
		*/
		;

DIMENSOES_INDICES	: DIMENSOES_INDICES ',' VALOR
					{
						if(!($1.tipo == constante_tipo_inteiro && $3.tipo == constante_tipo_inteiro))
						{
							//dispara erro ...
						}						
					}
					|
					VALOR
					{
						if($1.tipo != constante_tipo_inteiro && $1.estruturaDoConteudo != constante_estrutura_variavel)
						{
							//dispara erro ...
						}
						
						if($1.estruturaDoConteudo == constante_estrutura_variavel);						
					}
					;
		

/*

		void adicionarIndiceDimensaoArray(int);
		void removerTopoIndiceDimensaoArray();
		bool pilhaIndiceDimensaoArrayVazia()
		int obterTopoIndiceDimensaoArray();

	struct ATRIBUTOS
	{
		string label;
		string traducaoDeclaracaoDeVariaveis;
		string traducao;
		string tipo;Hosana...
		int escopoDeAcesso = -1;
		int tamanho = 0;
		bool ehDinamica = false;
		string estruturaDoConteudo;
		string labelTamanhoDinamicoString;
		int valorIndiceDimensaoArray;
		
	};
	
	//	recuperarLabelCodigoIntermediario($x.label)
*/

VALOR		: TK_NUM
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
				$$.estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
			}
			|
			TK_BOOL
			{
				string nomeUpperCase = $1.label;
				transform(nomeUpperCase.begin(), nomeUpperCase.end(), nomeUpperCase.begin(), ::toupper);
				$$.label = nomeUpperCase;
				$$.estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
				//incluirNoMapa($$.label,0, $1.tipo);
				$$.tipo = $1.tipo;
			}
			|
			TK_CHAR
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
				$$.estruturaDoConteudo = constante_estrutura_tipoPrimitivo;
			}
			|
			STRING
			{
				$$ = $1;
				//cout << "//Entrou em VALOR: STRING\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << endl;
				$$.estruturaDoConteudo = constante_estrutura_tipoPrimitivo;

			}
			|
			ID
			{
				//cout << "//Entrou em VALOR: ID" << "\n";
				//se for variavel aqui sempre vai existir, pq vai ter que ter passado pela verificação da regra ID: TK_ID
				//e por passar nessa regra terá o tipo já buscado
				if($1.tipo == ""){
					string params[1] = {$1.label};
					//mensagem variavel precisa ter recebido um valor para ter seu tipo definido e atribuido o valor
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR, params, 1));
				}

				DADOS_VARIAVEL metadata = recuperarDadosVariavel($1.label);
				$1.ehDinamica = metadata.ehDinamica;
				$1.tamanho = metadata.tamanho;
				$$ = $1;
				//$1.tipo = metadata.tipo; //pode ser que precise
			}
			|
			TK_CONVERSAO_EXPLICITA VALOR
			{
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao;
				if(verificarPossibilidadeDeConversaoExplicita($2.tipo, $1.tipo)){
					$$.label = gerarNovaVariavel();
					$$.tipo = $1.tipo;
					$$.tamanho = $1.tamanho;
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $$.tipo + " " + $$.label + ";\n";

					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
				}else{
					string params[2] = {$2.tipo, $1.tipo};
					yyerror(montarMensagemDeErro(MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA, params, 2));
				}
			}
			;


ID			: TK_ID
			{
			//	cout << "//Entrou em ID: TK_ID\n";
				if(variavelJaDeclarada($1.label))
				{
					DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
					$$.label = metaData.nome;
					$$.tipo = metaData.tipo;
					$$.estruturaDoConteudo = constante_estrutura_variavel;
					$$.tamanho = metaData.tamanho;
					$$.ehDinamica = metaData.ehDinamica;
			//		cout << "//Entrou em ID: TK_ID\n" << "metaData.nome: " << metaData.nome << "\nlabel$: " << $$.label << "label1: " << $1.label << endl;
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
					$$.tipo = metaData.tipo;

					if($$.tipo == "")
						$$.estruturaDoConteudo = constante_estrutura_variavelSemTipo;
					else
						$$.estruturaDoConteudo = constante_estrutura_variavel;

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
					$$.tipo = metaData.tipo;
					if($$.tipo == "")
						$$.estruturaDoConteudo = constante_estrutura_variavelSemTipo;
					else
						$$.estruturaDoConteudo = constante_estrutura_variavel;

					$$.escopoDeAcesso = 0;
				}else{
					string params[1] = {$4.label};
					yyerror(montarMensagemDeErro(MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO ,params, 1));
				}
			}
			;

STRING	: TK_STRING
			{
			//	cout << "Entrou em TK_STRING\n";
			//	$$.label = gerarNovaVariavel();
			//	cout << "//Entrou em STRING: TK_STRING\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << endl;
				$$.tamanho = atualizarTamanhoString($1.label.length()); //tamanho modificado pelo \0 e pelas aspas
		//		$$.traducaoDeclaracaoDeVariaveis = "char " + $$.label + "[" + to_string($$.tamanho) + "];\n";
				$$.label = $1.label;
			}
			;



INICIO_DECLARACAO	: CRIACAO_VARIAVEL ',' MULTI_DECLARACAO
					{
						$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $1.traducao + $3.traducao;
					}
					|
					CRIACAO_VARIAVEL
					|
					ATRIBUICAO_VARIAVEL
					;

MULTI_DECLARACAO	: ATRIBUICAO_VARIAVEL_CRIACAO ',' MULTI_DECLARACAO
					{
						$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
						$$.traducao = $1.traducao + $3.traducao;
				//		cout << "//Entrou em MULTI_DECLARACAO: ATRIBUICAO_VARIAVEL_CRIACAO , MULTI_DECLARACAO\n" << "label1: " << $1.label << "\nlabel$: " << $$.label << "\nlabel3" << $3.label <<endl;
					}
					|
					ATRIBUICAO_VARIAVEL_CRIACAO
					;

CRIACAO_VARIAVEL	: TK_PALAVRA_VAR TK_ID
					{
						$$ = tratarDeclaracaoSemAtribuicao($2);
						//$$.tipo = constante_tipo_criacao_sem_atribuicao;
						$$.estruturaDoConteudo = constante_estrutura_variavelSemTipo;
						$$.label = $2.label;
				//		cout << "//Entrou em CRIACAO_VARIAVEL TK_PALAVRA_VAR TK_ID\n" << "label2: " << $2.label << "\nlabel$: " << $$.label << endl;
					}
					|
					TK_PALAVRA_VAR TK_ID '=' E
					{
						$$ = tratarDeclaracaoComAtribuicao($2,$4);
					}
					;

ATRIBUICAO_VARIAVEL_CRIACAO	:  TK_ID '=' E
					{
						$$ = tratarDeclaracaoComAtribuicao($1,$3);
					}
					|
					TK_ID
					{
						$$ = tratarDeclaracaoSemAtribuicao($1);
					}
					;

ATRIBUICAO_VARIAVEL	:  ID '=' E
					{
				//		cout << "//Entrou em ID '=' VALOR_ATRIBUICAO\n";
						$$ = tratarAtribuicaoVariavel($1,$3);
						/*cout << "--ATRIBUICAO_VARIAVEL----------------\n";
						//cout << "label1: " << dolar1.label << " tamaho: " << dolar1.tamanho << endl;
						//cout << "label3: " << dolar3.label << " tamaho: " << dolar3.tamanho << endl;
						cout << "label$$: " << $$.label << " tamaho: " << $$.tamanho << endl;
						cout << "------------------\n";*/
					}
					;

PRINT			: TK_PALAVRA_PRINT '(' ARG_PRINT ')'
			{

				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;

			}
			;


ARG_PRINT: E
			{
				$$.traducao = $1.traducao + "\n" + constroiPrint(recuperarNomeTraducao($1.label));
			}
			;

SCAN			: TK_PALAVRA_SCAN '(' ARGS_SCAN ')'
			{
				//cout << " // Entrei em TK_PALAVRA_SCAN '(' ARGS_SCAN ')'';' \n";
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $$.traducao + $3.traducao;

			}
			;

ARGS_SCAN		: ARG_SCAN ',' ARGS_SCAN
			{
				//cout << $1.traducaoDeclaracaoDeVariaveis << " *******\n";
				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis + $1.traducaoDeclaracaoDeVariaveis;
				$$.traducao = $2.traducao + $1.traducao;

			}
			|
			ARG_SCAN

			;

ARG_SCAN		: ID ':' TIPO
			{
	//			cout << "\n//Entrou em ID TIPO\n";
				/*int tamanho = 0;
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
				}*/
				bool ehDinamica = true;
				$$ = tratarAtribuicaoVariavel($1, $3, ehDinamica);
				$$.label = gerarNovaVariavel();
				string dolarDolar = $$.label;
				int tamanho = 0;
				$$.traducao = "";
				int escopo = numeroEscopoAtual;
				if($$.escopoDeAcesso >= 0)
					escopo = $$.escopoDeAcesso;

				if($3.tipo == constante_tipo_string)
				{
					//adicionarDefinicaoDeTipo($1.label, $3.tipo,tamanho,ehDinamica);

					string labelRecuperada = recuperarNomeTraducao($1.label, escopo);
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "char * " + $$.label + ";\n";
					$$ = traducaoStringDinamica($$, labelRecuperada);
					$$.traducao = $$.traducao + montarCopiarString(labelRecuperada, $$.label) + ";\n";
					//cout << labelRecuperada << " <<< \n";
					//cout << $1.label << "\n";
				}

				else
				{
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario($3.label) + " " + $$.label + ";\n";
					$$.traducao =  constroiScan($$.label, $3.tipo);
					if($3.tipo == constante_tipo_booleano)
					{
						$$ = validarEntradaBooleanEmTempoExecucao($$);

					}


					//adicionarDefinicaoDeTipo($1.label, $3.label,tamanho,ehDinamica);
					$$.traducao = $$.traducao + "\t" + recuperarNomeTraducao($1.label, escopo) + " = " + dolarDolar + ";\n";

				}

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

COMANDO_IF	: TK_IF '(' E ')' COMANDO %prec IFX
			{
				if($3.tipo != constante_tipo_booleano) ;
					//dispara erro ...

				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis +
													constante_tipo_inteiro + " " + $$.label + ";\n";

				string tagFim = gerarNovaTagIf(true);

				$$.traducao = $3.traducao + "\t" + $$.label + " = " + "!" + $3.label + ";\n" +
							"\t" + "if" + "(" + $$.label + ")\n" + "\t\t" + "goto " + tagFim + ";\n" +
							$5.traducao + "\t" + tagFim + ":;\n";
			}
			|
			TK_IF '(' E ')' COMANDO TK_ELSE COMANDO
			{
				if($3.tipo != constante_tipo_booleano) ;
					//dispara erro ...

				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis +
													$7.traducaoDeclaracaoDeVariaveis +
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

COMANDO_WHILE	: EMPILHAR_TAG_WHILE TK_WHILE '(' E ')' COMANDO
				{
					if($4.tipo != constante_tipo_booleano) ;
						//dispara erro ...

					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();

					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + $6.traducaoDeclaracaoDeVariaveis +
														constante_tipo_inteiro + " " + $$.label + ";\n";

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

COMANDO_DOWHILE	: EMPILHAR_TAG_DOWHILE TK_DO COMANDO TK_WHILE '(' E ')' ';' //PROBLEMAS COM O COMANDO ----> RESOLVIDO
				{
					if($6.tipo != constante_tipo_booleano);
						//dispara erro ...

					string tagInicio = obterTopoPilhaInicio();
					string tagFim = obterTopoPilhaFim();

					$$.label = gerarNovaVariavel();
					$$.traducaoDeclaracaoDeVariaveis = $6.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis +
														constante_tipo_inteiro + " " + $$.label + ";\n";

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
			//$1.tipo == constante_tipo_criacao_sem_atribuicao
			if($1.estruturaDoConteudo == constante_estrutura_variavelSemTipo){

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

CONDICAO	: E
			{
				if($1.tipo != constante_tipo_booleano);
					//dispara erro ...
				$$ = $1;
			}
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
		E
		{

			if($1.estruturaDoConteudo == constante_estrutura_expressao){
				//dispara erro ...
				if($1.tipo != constante_tipo_booleano){
					if(variavelJaDeclarada($1.label)){
						$$ = $1;
					}
					else{
						//dispara erro ex: 1 + 1
					}
				}else{
					// dispara erro 10 < 3
				}
			}else{
				//dispara erro ex: vairiavel
			}
		}
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
													$8.traducaoDeclaracaoDeVariaveis + $10.traducaoDeclaracaoDeVariaveis
													+ constante_tipo_inteiro + " " + $$.label + ";\n";

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

COMANDO_SWITCH	: EMPILHAR_TAG_SWITCH TK_SWITCH '(' E ')' '{' CASES DEFAULT'}'
				{	
					if($4.estruturaDoConteudo != constante_estrutura_variavel)
					{
						//dispara erro... precisa ser variavel
					}
				
					//$3.tipo != constante_tipo_string && $3.tipo != constante_tipo_flutuante
					if($4.tipo == $7.tipo) {
						//(...)
						//pair<string,int> tagFimENumProx = gerarNovaTagSwitch(false);
						//string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second);
						pair<string,int> tagFimENumProx = gerarNovaTagSwitch(true);
						string tagCaseAtual = tag_case_inicio + to_string(tagFimENumProx.second-1);
						pair<string,string> condicaoCase = gerarNovaTagCondicaoCase();
						
						
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
										"\t" + condicaoCase.first + ":\n" +
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
			pair<string,string> condicaoCase = gerarNovaTagCondicaoCase();
			
			$$.traducaoDeclaracaoDeVariaveis = $3.traducaoDeclaracaoDeVariaveis;
			$$.traducao = "\t" + condicaoCase.first + ":\n" + 
							"\t" + tagCaseAtual + ":\n" + $3.traducao;
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

CASE	: TK_CASE E ':' COMANDO
		{
			if($2.estruturaDoConteudo != constante_estrutura_tipoPrimitivo)
			{
				//dispara erro ...
			}
			//Regra TERMO possui produção que leva em ID, o que não pode.
			//constante_estrutura_variavel
			//$2.label.find(prefixo_variavel_usuario) == std::string::npos
			if( ($2.tipo == constante_tipo_inteiro || $2.tipo == constante_tipo_caracter) && 
				$2.estruturaDoConteudo == constante_estrutura_variavel){
				
				pair<string,int> tagCaseENumProx = gerarNovaTagSwitch(true);
				string proxCase = tag_case_inicio + to_string(tagCaseENumProx.second);
			
				//Para referenciar o inicio do teste da condição de cada case. Serve como controle para quando devemos executar
				//todos os cases quando algo for verdadeiro.
				pair<string,string> condicaoCase = gerarNovaTagCondicaoCase(); 
				string proxCondicaoCase = tag_condicao_case + condicaoCase.second;
											
				//Gerar primeira label que receberá o resultado da condição de igualdade.
				$$.label = gerarNovaVariavel();
				//Gerar segunda label que receberá a negação da condição de igualdade.
				string tempIrProxCondCase = gerarNovaVariavel();

				$$.traducaoDeclaracaoDeVariaveis = $2.traducaoDeclaracaoDeVariaveis + $4.traducaoDeclaracaoDeVariaveis +
													"\t" + constante_tipo_inteiro + " " + $$.label + ";\n" + 
													"\t" + constante_tipo_inteiro + " " + tempIrProxCondCase + ";\n";
				$$.tipo = $2.tipo;
								
				//Adicionar a tag do inicio do case antes do comando em si.
				$4.traducao = "\t" + tagCaseENumProx.first + ":\n" + $4.traducao + 
													"\t" + "goto " + proxCase + ";\n"; 

				$$.traducao = "\t" + condicaoCase.first + ":\n" + 
								$2.traducao + "\t" + $$.label + " = " + tarja_variavel + " == " + $2.label + ";\n" +
								"\t" + tempIrProxCondCase + " = " + "!" + $$.label + ";\n" +  
								"\t" + "if" + "(" + tempIrProxCondCase + ")\n" + 
								"\t\t" + "goto " + proxCondicaoCase + ";\n" + 
								$4.traducao; //+
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
	conta = 0;
	mapaTipos = criarMapa();
	inicializarMapaDeContexto();
	//inicializarMapaDeStrings();
	//PARA O DEBUG
	//yydebug = 1;
	yyparse();



	return 0;
}

//TEMPORARIA!!!

string definicoesDeFuncoes()
{
	return "";
}


ATRIBUTOS tratarExpressaoAritmetica(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	//cout << "Entrou em exp arti\n";
	ATRIBUTOS dolarDolar;

	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo, op);

	string label_old = dolarDolar.label;

	if(resultado == constante_erro)
	{
		string params[3] = {op,dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
		dolarDolar.tipo = constante_erro;
		return dolarDolar;
	}

	/*
	*TODO
	*Tratar conversão para tipo String
	*
	*/
	if(resultado == constante_tipo_string)
	{
		string varTamDolar1 = gerarNovaVariavel();
		string varTamDolar3 = gerarNovaVariavel();
		string varTamDolarDolar = gerarNovaVariavel();
		string traducao = realizarOperacaoAritmeticaString(op, &dolarDolar,&dolar1,&dolar3, varTamDolarDolar, varTamDolar1, varTamDolar3);

		if(traducao == "") //o operador ainda não está implementado. Fiz assim para não alterar no mapa, vou apagar o if
		{
			string params[3] = {op,dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS	, params, 3));
			dolarDolar.tipo = constante_erro;
			return dolarDolar;

		}

		dolarDolar.traducao = dolarDolar.traducao + traducao;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + realizarTraducaoDeclaracaoDeStringConcatenada(op, &dolarDolar, &dolar1,&dolar3, varTamDolarDolar, varTamDolar1, varTamDolar3);

	}

	else
	{
		if(dolar1.tipo == dolar3.tipo) //se não houver necessidade de conversão
		{
			//cout << "label0\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + dolar1.tipo + " " + dolarDolar.label + ";\n";
		}

		else if(dolar1.tipo != resultado)
		{
			//cout << "label1\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + label_old +  ";\n" + resultado + " " + dolarDolar.label +  ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + label_old + " " + op + " " + dolar3.label + ";\n";
		}
		else if(dolar3.tipo != resultado)
		{
			//cout << "label3\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar3.label + ";\n";
			dolarDolar.label = gerarNovaVariavel();
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + label_old +  ";\n" + resultado + " " + dolarDolar.label +  ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + label_old + ";\n";

		}

	}

	dolarDolar.tipo = resultado;
	return dolarDolar;
}


ATRIBUTOS tratarExpressaoLogicaUnaria(string op, ATRIBUTOS dolar2)
{
	ATRIBUTOS dolarDolar;
	if(dolar2.tipo == constante_tipo_booleano)
	{
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolar2.traducaoDeclaracaoDeVariaveis;
		string tipo = constante_tipo_inteiro;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolar2.traducao;
		dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + op + " "+ dolar2.label + ";\n";
		dolarDolar.tipo = constante_tipo_booleano;
		return dolarDolar;
	}else{
		yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
	}
}

ATRIBUTOS tratarExpressaoLogicaBinaria(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	if(dolar1.tipo == constante_tipo_booleano && dolar3.tipo == constante_tipo_booleano){
		dolarDolar.label = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(constante_tipo_booleano) + " " + dolarDolar.label + ";\n";
		dolarDolar.traducao = dolar1.traducao + dolar3.traducao;
		dolarDolar.traducao = dolarDolar.traducao + "\t\t" + dolarDolar.label + " = " + dolar1.label + " " + op + " " + dolar3.label + ";\n";
		dolarDolar.tipo = constante_tipo_booleano;
		return dolarDolar;
	}
	else{
		yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
	}
}

ATRIBUTOS tratarExpressaoRelacional(string op, ATRIBUTOS dolar1, ATRIBUTOS dolar3)
{
	ATRIBUTOS dolarDolar;
	dolarDolar.label = gerarNovaVariavel();
	dolarDolar.traducaoDeclaracaoDeVariaveis += dolar1.traducaoDeclaracaoDeVariaveis + dolar3.traducaoDeclaracaoDeVariaveis;
	/*dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + "\t\t" + constante_tipo_inteiro + " " + dolarDolar.label + ";\n";*/

	dolarDolar.traducao = dolar1.traducao + dolar3.traducao;

	string resultado = getTipoResultante(dolar1.tipo, dolar3.tipo,op);

	//string label_old = dolarDolar.label;
	dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(constante_tipo_booleano) + " " + dolarDolar.label + ";\n";
	string operador = op;

	//FIXME - remover a verificação de string daqui, após a implementação dessa operações corretamente.
	if(resultado == constante_erro || resultado == constante_tipo_string)
	{

		string params[3] = {op, dolar1.tipo, dolar3.tipo};
		yyerror(montarMensagemDeErro(MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS, params, 3));
		dolarDolar.tipo = constante_erro;
		return dolarDolar;
	}

	if(dolar1.tipo == dolar3.tipo)
	{
		if(dolar1.tipo == constante_tipo_caracter) //se char,ambos são convertidos pra int
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + dolarDolar.label + " = " +"(" + resultado + ")" + dolar1.label + ";\n";

			//dolar1.label = dolarDolar.label;
			string novaVariavel = gerarNovaVariavel();

			dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + resultado + " " + novaVariavel + ";\n";
			dolarDolar.traducao = dolarDolar.traducao + "\t" + novaVariavel + " = " +"(" + resultado + ")" + dolar3.label + ";\n";
			dolar3.label = novaVariavel;
		}

	}

	else
	{
		string varConvert = gerarNovaVariavel();
		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis + tipoCodigoIntermediario(resultado) + " " + varConvert + ";\n";

		if(dolar1.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + tipoCodigoIntermediario(resultado) + ")" + dolar1.label + ";\n";

			dolar1.label = varConvert;
		}

		else if(dolar3.tipo != resultado)
		{
			dolarDolar.traducao = dolarDolar.traducao + "\t" + varConvert + " = " +"(" + tipoCodigoIntermediario(resultado) + ")" + dolar3.label + ";\n";
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
		incluirNoMapa(dolar2.label,0);
		dolarDolar.label = dolar2.label;
		dolarDolar.traducaoDeclaracaoDeVariaveis = construirDeclaracaoProvisoriaDeInferenciaDeTipo(dolar2.label);
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
	else //Você cria a variável e inclui no mapaDeContexto.
	{
		//cout << "Entrou no else: \n\n\n";
		int tamanho = 0;
		incluirNoMapa(dolar2.label,dolar4.tamanho, dolar4.tipo);
		string tipo = dolar4.tipo;
		string label = recuperarNomeTraducao(dolar2.label);

		//meramente para leitura do código intermediário
		string labelPrefix = prefixo_variavel_usuario;
		labelPrefix = labelPrefix + dolar2.label;


		if(tipo == constante_tipo_booleano)
			tipo = constante_tipo_inteiro;

		if(tipo == constante_tipo_string)
		{
			if(dolar4.ehDinamica)
			{
				tipo = constante_tipo_caracter;
					dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " * " + label+ "; //" + labelPrefix + "\n";

					//TENTATIVA ATRIBUICAO COM MALLOC
					//dolarDolar.traducao = dolar4.traducao + "\t" + label +" = (char*) malloc(" + to_string(dolar4.tamanho) + ");\n\t" + montarCopiarString(label, dolar4.label) + ";\n";

					//TENTATIVA ATRIBUINDO PONTEIRO
					dolarDolar.traducao = dolar4.traducao + "\t" + label +" = "+ dolar4.label + "; //" + labelPrefix + "\n";

			}
			else
			{
				tipo = constante_tipo_caracter;
				dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " " + label + "[" + to_string(dolar4.tamanho) + "]; //" + labelPrefix + "\n";
				dolarDolar.traducao = dolar4.traducao + montarCopiarString(label, dolar4.label) + ";\n";

			}

		}

		else
		{
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar4.traducaoDeclaracaoDeVariaveis + tipo + " " + label + "; //" + labelPrefix + "\n";
			dolarDolar.traducao = dolar4.traducao + "\t" + label + " = " + dolar4.label + ";\n";
		}

		dolarDolar.traducaoDeclaracaoDeVariaveis = dolarDolar.traducaoDeclaracaoDeVariaveis;
		dolarDolar.label = label;
		dolarDolar.tipo = dolar4.tipo;
		dolarDolar.ehDinamica = dolar4.ehDinamica;
		dolarDolar.tamanho = dolar4.tamanho;
	}


	return dolarDolar;

}

//ID '=' VALOR_ATRIBUICAO ';'
ATRIBUTOS tratarAtribuicaoVariavel(ATRIBUTOS dolar1, ATRIBUTOS dolar3, bool ehDinamica)
{
	ATRIBUTOS dolarDolar;
	string tipo = "";
	int tamanho = 0;
	string labelRecuperada = recuperarNomeTraducao(dolar1.label);

	//bool ehDinamica = false;
	/*std::cout << "sin dolar1.ehDinamica:" << dolar1.ehDinamica << '\n';
	std::cout << "sin dolar3.ehDinamica:" << dolar3.ehDinamica << '\n';
	std::cout << "sin ehDinamica:" << ehDinamica << '\n';*/

	if(dolar1.label != dolar3.label)
	{
		DADOS_VARIAVEL metaData;
		if(dolar1.escopoDeAcesso >= 0){
			metaData = recuperarDadosVariavel(dolar1.label, dolar1.escopoDeAcesso);
		}
		else{
			metaData = recuperarDadosVariavel(dolar1.label);
		}

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

			metaData.ehDinamica = ehDinamica;
			if(dolar1.escopoDeAcesso >= 0){
				adicionarDefinicaoDeTipo(dolar1.label, tipo, dolar3.tamanho,ehDinamica, dolar1.escopoDeAcesso);
				atualizarNoMapa(metaData, dolar1.escopoDeAcesso);
			}
			else{
				adicionarDefinicaoDeTipo(dolar1.label, tipo,dolar3.tamanho,ehDinamica);
				atualizarNoMapa(metaData);
			}

			dolar1.tipo = dolar3.tipo;
		}
//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
		if(dolar1.tipo == dolar3.tipo)
		{
			dolarDolar.traducaoDeclaracaoDeVariaveis = dolar3.traducaoDeclaracaoDeVariaveis;

			if(dolar3.tipo == constante_tipo_string)
				dolarDolar.traducao = dolar3.traducao + montarCopiarString(labelRecuperada, dolar3.label) + ";\n";
			else
				dolarDolar.traducao = dolar3.traducao + "\t" + labelRecuperada + " = " + dolar3.label + ";\n";
		}
		else
		{

			string strPrefixoVarUsuario = prefixo_variavel_usuario;
			string labelVar = dolar1.label;
			//para remover o prefixo só se tiver prefixo
			if(dolar1.label.find(strPrefixoVarUsuario) == 0)
				labelVar = dolar1.label.replace(0, strPrefixoVarUsuario.length(), "");
			
			string params[3] = {labelVar, dolar1.tipo, dolar3.tipo};
			yyerror(montarMensagemDeErro(MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES, params, 3));
		}

		dolarDolar.label = dolar1.label;
		dolarDolar.tipo = dolar1.tipo;
		dolarDolar.tamanho = dolar3.tamanho;
		dolarDolar.ehDinamica = ehDinamica;
		dolarDolar.escopoDeAcesso = dolar1.escopoDeAcesso;

	}
	else
	{
		dolarDolar = dolar3;
	}


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
