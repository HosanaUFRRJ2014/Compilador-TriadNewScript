#include<iostream>
#include <string>
#include <sstream>


using namespace std;

namespace MensagensDeErro{

	#define MSG_ERRO_DUPLA_DECLARACAO_DE_VARIAVEL "Erro: A variável com id \"\t\" já existe."
	#define MSG_ERRO_VARIAVEL_NAO_DECLARADA "Erro: Variável de id \"\t\" não declarada."
	#define MSG_ERRO_VARIAVEL_UTILIZADA_PRECISA_TER_RECEBIDO_UM_VALOR "Erro: A variável de id \"\t\" precisa ter recebido um valor antes de ser utilizada."
	#define MSG_ERRO_ATRIBUICAO_DE_TIPOS_DIFERENTES "Erro: Os tipos da atribuição são diferentes. A de variavel de id \"\t\" é do tipo \"\t\" e o valor atribuido é do tipo \"\t\"."
	#define MSG_ERRO_VALOR_NAO_PODE_SER_CONVERTIDO "Erro: Não é possível fazer a conversão do tipo \"\t\" para o tipo \"\t\"."
	
	#define MSG_ERRO_OPERACAO_PROIBIDA_ENTRE_TIPOS "Erro: Não é possível efetuar operação com o operador \"\t\" entre os tipos \"\t\" e \"\t\"."
	
	#define MSG_ERRO_CONVERSAO_EXPLICITA_INDEVIDA "Erro: Não é possível efetuar conversão explicita do tipo \"\t\" para o tipo \"\t\". Operação indevida"
	//LÍVIA HERE!	
	#define MSG_ERRO_COMENTARIO "Erro: '*/' não encontrado para fechar comentário."
	#define MSG_ERRO_TIPO_ID_SWITCH_CASE_INVALIDO "Erro: Variável tipo 'string' ou 'float' não permitida no comando switch-case."
	#define MSG_ERRO_BREAK_NAO_PERMITIDO "Erro: Comando 'break' não permitido uso neste escopo."
	#define MSG_ERRO_CONTINUE_NAO_PERMITIDO "Erro: Comando 'continue' não permitido uso neste escopo."
	

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

}
