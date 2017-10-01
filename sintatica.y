%{
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "MapaTipos.h"

#include "controleDeVariaveis.h"

#define YYSTYPE atributos
/*#define constante_tipo_inteiro "int"
#define constante_tipo_real "float"
#define constante_tipo_booleano "bool"
#define constante_tipo_caracter "char"*/

#define MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN "Os operandos de expressões lógicas precisam ser do tipo booelan"

using namespace std;
using namespace MapaTiposLib;
using namespace ControleDeVariaveis;

struct atributos
{
	string label;
	string traducaoDeclaracaoDeVariaveis;
	string traducao;
	string tipo;
};

/*struct DADOS_VARIAVEL
{
	string tipo;
	string nome;
	string valor;
};*/

int yylex(void);
void yyerror(string);
bool verificarPossibilidadeDeConversaoExplicita(string, string);
string verificarTipoResultanteDeCoercao(string, string, string);

//map<string, string> mapaTipos;

%}

%token TK_NUM
%token TK_BOOL
%token TK_CHAR
%token TK_OP_LOGICO_BIN
%token TK_OP_LOGICO_UNA
%token TK_OP_RELACIONAL
%token TK_MAIN TK_ID TK_TIPO_INT TK_PALAVRA_VAR
%token TK_FIM TK_ERROR
%token TK_COMENTARIO_1L TK_ABRE_COMENTARIO_NL TK_FECHA_COMENTARIO_NL
%token TK_CONVERSAO_EXPLICITA

%start S


%left "not"
%left "and" "or"
%nonassoc "==" "!="
%nonassoc '<' '>' "<=" ">="
%left '+' '-'
%left '*' '/'

%%

S 			: TK_TIPO_INT TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n" << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducaoDeclaracaoDeVariaveis;
				$$.traducao =  $$.traducao + "\n" + $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $2.traducaoDeclaracaoDeVariaveis;
				if($1.traducao != "")				
					$$.traducao = $1.traducao + "\n";
				$$.traducao = $$.traducao + $2.traducao;
			}
			|
			COMANDOS TK_ABRE_COMENTARIO_NL COMANDOS TK_FECHA_COMENTARIO_NL COMANDOS
			{
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $5.traducaoDeclaracaoDeVariaveis;
				if($1.traducao != "")
					$$.traducao = $1.traducao + "\n";
				if($5.traducao != "")
					$$.traducao = $$.traducao + $5.traducao;
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
			|
			TK_COMENTARIO_1L COMANDO
			{
			}
			|
			TK_PALAVRA_VAR TK_ID ';'
			{
				$$.label = $2.label;
				if(variavelJaDeclarada($2.label)){
					yyerror("A variavel com id '" + $2.label + "' já existe");
				}else{
					incluirNoMapa($2.label);
				}
			}
			|
			TK_PALAVRA_VAR TK_ID '=' VALOR_ATRIBUICAO ';'
			{
				if(variavelJaDeclarada($2.label)){
					yyerror("dupla declaração da variavel com id '" + $2.label + "'");
				}else{
					string tipo = $4.tipo;
					if(tipo == constante_tipo_booleano)
						tipo = constante_tipo_inteiro;
					
					$$.traducaoDeclaracaoDeVariaveis = $4.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + $2.label + ";\n";
					$$.traducao = $4.traducao + "\t" + $2.label + " = " + $4.label + ";\n";
					incluirNoMapa($2.label, $4.tipo);
				}
			}
			|
			TK_ID '=' VALOR_ATRIBUICAO ';'
			{				
				if(variavelJaDeclarada($1.label)){
					if($1.label != $3.label){
						DADOS_VARIAVEL metaData = recuperarDadosVariavel($1.label);
						if(metaData.tipo == ""){
	//isso aqui também pode causar problema no futuro devido as lacunas
							metaData.tipo = $3.tipo;
							atualizarNoMapa(metaData);
							string tipo = metaData.tipo;
							if(tipo == constante_tipo_booleano)
								tipo = constante_tipo_inteiro;
							$$.traducaoDeclaracaoDeVariaveis = "\t" + tipo + " " + metaData.nome + ";\n";
						}
					
						$1.tipo = metaData.tipo;
	//provavelmente ainda há lacunas, mas vamos ignorar por enquanto
						if(metaData.tipo == $3.tipo){
							$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
							$$.traducao = $3.traducao + "\t" + $1.label + " = " + $3.label + ";\n";
						}
						else{
							yyerror("Os tipos da atribuição não são compativeis. A de variavel de id '" + $1.label + "' é do tipo '" + $1.tipo + "' e o valor atribuido é do tipo '"+ $3.tipo + "'\n");
						}
					}
					else{
						$$ = $3;
					}
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
			| TK_ID
			{
				if(variavelJaDeclarada($1.label)){
					$$.label = $1.label;
					$$.tipo = recuperarDadosVariavel($1.label).tipo;
				}else{
					yyerror("Variável de id '" + $1.label + "' não declarada");
				}
			}
			;
			
VALOR_ATRIBUICAO: E
			|
			E_UNARIA
			|
			E_LOGICA
			|
			TERMO_CARACTER
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
					//dispara erro de mensagem tipo não pdoe ser convertido
				}
			}
			;

E 			: E '+' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				

				/*string chaveFinal = gerarChaveFinal($1.tipo, $3.tipo,"+");
				string resultado = mapaTipos[chaveFinal];
				
				//caso a chave não exista para a primeira ordem de tipos, testar com a ordem invertida
				if (resultado == "")
				{
					chaveFinal = gerarChaveFinal($3.tipo, $1.tipo,"+");
					resultado = mapaTipos[chaveFinal];
				}*/
				
				
				string resultado = getTipoResultante($1.tipo, $3.tipo,"+");
				
				string label_old = $$.label;
				
				if(resultado == constante_erro)
				{
					string msgErro = gerarMensagemErroOperacaoProibida($1.tipo, $3.tipo, "+");
					yyerror(msgErro);
				}
					
				else if($1.tipo == $3.tipo && $1.tipo == resultado && $3.tipo == resultado)
				{
							
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + $3.label + ";\n";
				}
				
				
				else if($3.tipo == resultado)
				{
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
					
					$$.label = gerarNovaVariavel();
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " + " + label_old + ";\n";
				}
				else if($1.tipo == resultado)
				{
						
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
					$$.label = gerarNovaVariavel();
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " + " + label_old + ";\n";
					
				}
				

				$$.tipo = resultado;	
				
						
				
			}
			|
			E '-' E
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				string resultado = getTipoResultante($1.tipo, $3.tipo,"-");
				
				string label_old = $$.label;
				
				if(resultado == constante_erro)
				{
					string msgErro = gerarMensagemErroOperacaoProibida($1.tipo, $3.tipo, "-");
					yyerror(msgErro);
				}
					
				else if($1.tipo == $3.tipo && $1.tipo == resultado && $3.tipo == resultado)
				{
							
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + $3.label + ";\n";
				}
				
				
				else if($3.tipo == resultado)
				{
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
					
					$$.label = gerarNovaVariavel();
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " - " + label_old + ";\n";
				}
				else if($1.tipo == resultado)
				{
						
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
					$$.label = gerarNovaVariavel();
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " - " + label_old + ";\n";
					
				}
				

				$$.tipo = resultado;	
				
				
				
				
			}
			|
			E1
			;

E1 			: E1 '*' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				string resultado = getTipoResultante($1.tipo, $3.tipo,"*");
				
				string label_old = $$.label;
				
				if(resultado == constante_erro)
				{
					string msgErro = gerarMensagemErroOperacaoProibida($1.tipo, $3.tipo, "*");
					yyerror(msgErro);
				}
					
				else if($1.tipo == $3.tipo && $1.tipo == resultado && $3.tipo == resultado)
				{
							
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + $3.label + ";\n";
				}
				
				
				else if($3.tipo == resultado)
				{
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
					
					$$.label = gerarNovaVariavel();
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + " * " + label_old + ";\n";
				}
				else if($1.tipo == resultado)
				{
						
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
					$$.label = gerarNovaVariavel();
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " * " + label_old + ";\n";
					
				}
				

				$$.tipo = resultado;	
			}
			|
			E1 '/' E1
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				
				string resultado = getTipoResultante($1.tipo, $3.tipo,"/");
				
				string label_old = $$.label;
				
				if(resultado == constante_erro)
				{
					string msgErro = gerarMensagemErroOperacaoProibida($1.tipo, $3.tipo, "/");
					yyerror(msgErro);
				}
					
				else if($1.tipo == $3.tipo && $1.tipo == resultado && $3.tipo == resultado)
				{
							
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + "/" + $3.label + ";\n";
				}
				
				
				else if($3.tipo == resultado)
				{
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $1.label + ";\n";
					
					$$.label = gerarNovaVariavel();
					
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $3.label + "/" + label_old + ";\n";
				}
				else if($1.tipo == resultado)
				{
						
					$$.traducao = $$.traducao + "\t" + $$.label + " = " +"(" + resultado + ")" + $3.label + ";\n";							
					$$.label = gerarNovaVariavel();
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + "/" + label_old + ";\n";
					
				}
				

				$$.tipo = resultado;	
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
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + $$.label + ";\n";
					$$.traducao = $1.traducao + $3.traducao;
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " " + $2.label + " " + $3.label + ";\n";
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
					$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + tipo + " " + $$.label + ";\n";
					$$.traducao = $2.traducao;
					$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + $2.label + ";\n";
					$$.tipo = constante_tipo_booleano;
				}
				else{
					yyerror(MSG_ERRO_OPERADOR_LOGICO_COM_OPERANDOS_NAO_BOOLEAN);
				}
			}
			|
			TK_BOOL
			{
				if(!variavelJaDeclarada($1.label)){
				//no final das contas o 3º campo não foi necessário, mas pode ser util no futuro;
				// o motivo de não ter sido necessario é que as palavras true e false nunca serão reconhecidas como id;
					incluirNoMapa($1.label, $1.tipo, true);
					string valorBoolInt = "0";
					if($1.label == "true")
						valorBoolInt = "1";
					string tipo = constante_tipo_inteiro;
					$$.traducaoDeclaracaoDeVariaveis = "\t" + tipo + " " + $$.label + " = " + valorBoolInt + ";\n";
				}
				
				$$.label = $1.label;
				$$.tipo = $1.tipo;
			}
			|
			TK_ID
			{
				if(variavelJaDeclarada($1.label)){
					if(recuperarDadosVariavel($1.label).tipo == constante_tipo_booleano){
						$$.label = $1.label;
						$$.tipo = constante_tipo_booleano;
					}
					else{
						//disparar mensagem de erro variavel de tipo incompativel
					}		
				}
				else{
					//disparar mensagem de erro variavel não existente				
				}
			}
			|
			'(' E_LOGICA ')'
			{
				$$ = $2;
			}
			|
			E_REL
			;

TERMO_REL	: E
			;

E_REL		: TERMO_REL TK_OP_RELACIONAL TERMO_REL
			{
				//o tipo resultante deve ser constante_tipo_booleano
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = $1.traducaoDeclaracaoDeVariaveis + $3.traducaoDeclaracaoDeVariaveis;
				$$.traducaoDeclaracaoDeVariaveis = $$.traducaoDeclaracaoDeVariaveis + "\t" + constante_tipo_booleano + " " + $$.label + ";\n";
				$$.traducao = $1.traducao + $3.traducao;
				$$.traducao = $$.traducao + "\t" + $$.label + " = " + $1.label + " " + $2.label + " " + $3.label + ";\n";
				$$.tipo = constante_tipo_booleano;
			}
			|
			'(' E_REL ')'
			{
				$$ = $2; 
			}
			;
			
TERMO_CARACTER: TK_CHAR
			{
				$$.label = gerarNovaVariavel();
				$$.traducaoDeclaracaoDeVariaveis = "\t" + $1.tipo + " " + $$.label + ";\n";
				$$.traducao = "\t" + $$.label + " = " + $1.label + ";\n";
				$$.tipo = $1.tipo;
			}
			


%%

#include "lex.yy.c"

DADOS_VARIAVEL d;

std::map<string, DADOS_VARIAVEL > tabelaDeVariaveis;


int yyparse();

int main( int argc, char* argv[] )
{
	
	mapaTipos = criarMapa();
	yyparse();
	
	

	return 0;
}

bool verificarPossibilidadeDeConversaoExplicita(string tipoOrigem, string tipoDestino){
	return true;
}

/*string verificarResultanteDeCoercao(string tipo1, string tipo2, string operacao){
	//a principio será feito com if devido a pouca quantidade de tipo e falta de noção de como fazer o certo
	// mas depois vai ser preciso trocar para matriz
	
	if(tipo1 == constante_tipo_real || tipo2 == constante_tipo_real){
		return constante_tipo_real;
	}else{
		return constante_tipo_inteiro;
	}
}*/
//declaração de variaveis var <nome variavel>;
string gerarNovaVariavel(){
	static int num = 0;
	num++;
	//cout << num << endl;
	string temp = "temp";
	
	/*d.nome = "var1";
	d.valor = "10";
	d.tipo = constante_tipo_inteiro;
	
	tabelaDeVariaveis[d.nome] = d;
	cout << tabelaDeVariaveis[d.nome].valor << endl;
	DADOS_VARIAVEL A = tabelaDeVariaveis["aaa"];
	cout << (A.nome == "") << endl;*/
	
	string numInt = to_string(num);
	return temp + numInt;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
