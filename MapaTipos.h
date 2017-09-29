
#include <iostream>
#include <map>
#include <string>

#include "ConstanteTipos.h"


using namespace std;
using namespace ConstanteTipos;


namespace MapaTiposLib
{
	


	/*string inserirNoMapa(string chave, string valor)
	{
		mapaTipos.insert(make_pair(chave,valor));

	}*/


	string gerarChaveFinal(string tipo1, string tipo2, string operador)
	{
		return tipo1 + "_" + tipo2 + "_" + operador;
	}


	map<string, string> criarMapa()
	{
		//mapa formado por chave=tipo1_tipo2_operador	valor=resultado
		map<string, string> mapaTipos;
		

		string tipo1;
		string tipo2;
		string operador;
		string chaveFinal;

		/*****************operações ariméticas******************/
			//soma
			operador = "+";
			
				//inteiro + flutuante
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_real;
				chaveFinal =  gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_tipo_real));


				//inteiro + booleano
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//inteiro + caracter
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));



				//flutuante + booleano
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//flutuante + caracter
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//booleano + caracter
				tipo1 = constante_tipo_booleano;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


			//subtracao
			operador = "-";
			
				//inteiro + flutuante
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_real;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_tipo_real));


				//inteiro + booleano
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//inteiro + caracter
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));



				//flutuante + booleano
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//flutuante + caracter
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//booleano + caracter
				tipo1 = constante_tipo_booleano;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


			//multiplicação
			operador = "*";
			
				//inteiro + flutuante
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_real;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_tipo_real));


				//inteiro + booleano
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//inteiro + caracter
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));



				//flutuante + booleano
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//flutuante + caracter
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//booleano + caracter
				tipo1 = constante_tipo_booleano;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


			//divisao
			operador = "/";
			
				//inteiro + flutuante
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_real;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_tipo_real));


				//inteiro + booleano
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//inteiro + caracter
				tipo1 = constante_tipo_inteiro;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));



				//flutuante + booleano
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_booleano;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//flutuante + caracter
				tipo1 = constante_tipo_flutuante;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


				//booleano + caracter
				tipo1 = constante_tipo_booleano;
				tipo2 = constante_tipo_caracter;
				chaveFinal = gerarChaveFinal(tipo1,tipo2,operador);
				
				mapaTipos.insert(make_pair(chaveFinal, constante_erro));


		/*******************operações relacionais************************/	
















				


		return mapaTipos;


	}
	
	

}


/*namespace MapaTiposLib
{
    struct CelulaMapaTipos
    {
        string tipo1;
        string tipo2;
        string operacao;
        string resultado;
    };


    struct MapaTipos
    {
        int numLinhas;
        int numColunas;
        CelulaMapaTipos ** matrizTipos;

    };


    MapaTipos inicializarMatrizMapa(int numLinhas, int numColunas)
    {
        MapaTipos mapa;

        mapa.numLinhas = numLinhas;
        mapa.numColunas = numColunas;
        
        mapa.matrizTipos = (CelulaMapaTipos **) malloc(sizeof(CelulaMapaTipos) * mapa.numLinhas);
        
        for(int i = 0; i< mapa.numLinhas; i++)
        {
            mapa.matrizTipos[i] = (CelulaMapaTipos *) malloc(sizeof(CelulaMapaTipos) * mapa.numColunas);
        
        }

        return mapa;
    }

    bool adicionarElemento(MapaTipos mapa, CelulaMapaTipos *elemento);

    bool adicionarElemento(MapaTipos mapa,int posLinha, int posColuna, string tipo1, string tipo2, string operacao, string resultado)
    {
        mapa.matrizTipos[posLinha][posColuna].tipo1 = tipo1;
        mapa.matrizTipos[posLinha][posColuna].tipo2 = tipo2;
        mapa.matrizTipos[posLinha][posColuna].operacao = operacao;
        mapa.matrizTipos[posLinha][posColuna].resultado = resultado;
    }

    CelulaMapaTipos acharElementoRetornaCelula(MapaTipos mapa, string tipo1, string tipo2, string operacao)
    {
    	for (int i = 0; i < mapa.numLinhas; i++)
    	{
    		for (int j = 0; j < mapa.numColunas; j++)
    		{
    			if (mapa.matrizTipos[i][j].tipo1 == tipo1 && mapa.matrizTipos[i][j].tipo2 == tipo2 && mapa.matrizTipos[i][j].operacao == operacao)
    			{
    				return mapa.matrizTipos[i][j];
    			}
    		}
    	}

    	//return "";

    }

    string acharElementoRetornaResultado(MapaTipos mapa, string tipo1, string tipo2, string operacao)
    {
    	for (int i = 0; i < mapa.numLinhas; i++)
    	{
    		for (int j = 0; j < mapa.numColunas; j++)
    		{
    			if (mapa.matrizTipos[i][j].tipo1 == tipo1 && mapa.matrizTipos[i][j].tipo2 == tipo2 && mapa.matrizTipos[i][j].operacao == operacao)
    			{
    				return mapa.matrizTipos[i][j].resultado;
    			}
    		}
    	}

    	return "";

    }

    bool removerElemento(CelulaMapaTipos elementoARemover);

    bool removerElemento(int posLinha, int posColuna);

    void imprimirElemento(MapaTipos mapa, int posLinha, int posColuna)
    {
    	
		cout << "Imprimindo elemento: " << posLinha << "  " << posColuna << ":\n";
        cout << mapa.matrizTipos[posLinha][posColuna].tipo1 << "\n";
        cout << mapa.matrizTipos[posLinha][posColuna].tipo2 << "\n";
        cout << mapa.matrizTipos[posLinha][posColuna].operacao << "\n";
        cout << mapa.matrizTipos[posLinha][posColuna].resultado << "\n";

    }

} */