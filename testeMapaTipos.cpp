#include <iostream>

#include "MapaTipos.h"


using namespace std;
using namespace MapaTiposLib;

int main()
{
    
    MapaTipos mapa;

    mapa = inicializarMatrizMapa(4,4);

    							 //tipo1   tipo2    op   //resultado
    adicionarElemento(mapa, 2,3, "string", "float", "+", "string");

    														 //tipo1 tipo2    op
    CelulaMapaTipos celula = acharElementoRetornaCelula(mapa,"string","float","+");

    													  //tipo1   tipo2  op
    string resultado = acharElementoRetornaResultado(mapa,"string","float","+");

    //resultado da conversão que será aplicada. Imprime string
    cout << resultado << "\n";

  //  imprimirElemento(mapa,celula.,3);

    return 0;
}