#include<iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>


namespace TratamentoOperadoresCompostos
{
  string removerSimboloIgualdade(string );

  string removerSimboloIgualdade(string operadorComposto)
  {
    string operadorSimples = operadorComposto.substr(0,operadorComposto.length() - 1);
    return operadorSimples;

  }


}
