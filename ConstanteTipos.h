/*Biblioteca destinada a armazenar as defines de tipos
que poderão ser modificadas mais tarde. */

//ConstanteTipos.h
namespace ConstanteTipos
{
	#define constante_tipo_inteiro "int"
	#define constante_tipo_flutuante "float"
	#define constante_tipo_booleano "boolean"
	#define constante_tipo_caracter "char"
	#define constante_tipo_string "string"
	#define constante_tipo_array "array"
	#define constante_tipo_funcao "função"
	#define constante_erro "erro"

	#define constante_estrutura_variavel "variavel"
	#define constante_estrutura_variavelSemTipo "variavelSemTipo"
	#define constante_estrutura_tipoPrimitivo "primitivo"
	#define constante_estrutura_expressao "expressao"
	#define constante_estrutura_funcao "funcao"
	#define constante_estrutura_chamadaFuncao "chamadaFuncao"
	#define constante_estrutura_bloco "BLOCO"
	#define constante_estrutura_criacaoArrayPreDefinido "criacaoArrayPreDefinido"
	#define constante_estrutura_comandoReturn "comandpReturn"

	#define constante_tipo_default "default"
	#define constante_tipo_break "break"
	#define constante_tipo_continue "continue"
	//#define constante_tipo_criacao_sem_atribuicao "semAtribuicao"
	#define constante_tipo_condicao_vazia_for "condicaoVazia"

	using namespace std;

	string tipoCodigoIntermediario(string tipo)
	{
		if(tipo == constante_tipo_booleano)
			return constante_tipo_inteiro;

		if(tipo == constante_tipo_string){
			string t = constante_tipo_caracter;
			return t + "*";
		}
		if(tipo == constante_tipo_funcao){
			string t = constante_tipo_caracter;
			return t + "*";
		}
		return tipo;

	}
}
