#include<iostream>
#include <string>
#include <sstream>


using namespace std;

namespace MensagensDeErro{

	#define MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL "Erro: A variável com id \"\t\" já existe no escopo atual."
	#define MSG_ERRO_VARIAVEL_NAO_DECLARADA "Erro: Variável de id \"\t\" não declarada."
	#define MSG_ERRO_VARIAVEL_NAO_DECLARADA_NO_ESCOPO "Erro: Variável de id \"\t\" não declarada no escopo especificado."
	#define MSG_ERRO_PARAMETRO_BACKSCOPE_DEVE_SER_INTEIRO "Erro: O índice de retorno de escopo deve ser do tipo \"inteiro\" e o tipo informado foi \"\t\"."
	#define MSG_ERRO_PARAMETRO_BACKSCOPE_MAIOR_OU_IGUAL_ESCOPO_ATUAL "Erro: O índice de retorno de escopo deve ser menor que o escopo atual. Se for igual use o comando \"(global) <var-id>\" para acessar o escopo global."
	#define MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR "Erro: A variável de id \"\t\" precisa ter recebido um valor antes de ser utilizada."
	#define MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES "Erro: Os tipos da atribuição são diferentes. A de variavel de id \"\t\" é do tipo \"\t\" e o valor atribuido é do tipo \"\t\"."
	#define MSG_ERRO_VALOR_NAO_PODE_SER_CONVERTIDO "Erro: Não é possível fazer a conversão do tipo \"\t\" para o tipo \"\t\"."
	
	#define MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS "Erro: Não é possível efetuar operação com o operador \"\t\" entre os tipos \"\t\" e \"\t\"."
	
	#define MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA "Erro: Não é possível efetuar conversão explicita do tipo \"\t\" para o tipo \"\t\". Operação indevida"
	#define MSG_WARINING_VARIAVEL_DECLARADA_NAO_UTILIZADA "Warning: A variável \"\t\" foi declarada, mas não foi utilizada."
	//LÍVIA HERE!	
	#define MSG_ERRO_COMENTARIO "Erro: '*/' não encontrado para fechar comentário."
	string montarMensagemDeErro(string, string*, int);
	void yywarnning(string);
	
	string SEP_PARAMS = "\t";

	string montarMensagemDeErro(string mensagem, string* parametros = NULL, int qtdParametros = 0){
		int pos;
		for(int i = 0; i < qtdParametros; i++){
			pos = mensagem.find(SEP_PARAMS);
			string param = parametros[i];
			if(pos > 0)
				mensagem.replace(pos, SEP_PARAMS.length(), param);
			else
				return constante_erro;
		}
		
		return mensagem;
	
	}
	
	void yywarning(string MSG)
	{
		cout << MSG << endl;
	}

}
