#include <iostream>
#include <string>

using namespace std;

#define tag_while_inicio "INICIO_WHILE"
#define tag_while_fim "FIM_WHILE"

string criarNovaTag(int *num1,int *num2,string tagCmd1,string tagCmd2,bool fim){

	string numInt, tag;

	if(fim)
	{
		*num1 += 1;
		tag = tagCmd1;
		numInt = to_string(*num1);
	}
	else
	{
		*num2 += 1;
		tag = tagCmd2;
		numInt = to_string(*num2);
	}

	return tag + numInt;

}

int main()
{
	static int num1 = 0,num2 = 0;
	string result;
	
	result = criarNovaTag(&num1,&num2,tag_while_fim,tag_while_inicio,false);
	
	cout << "Valor no endereço: de num1 " << num1 << endl << "Endereço de num1: " << &num1 << endl;
	cout << "Valor no endereço de num2: " << num2 << endl << "Endereço de num2: " << &num2 << endl;
	cout << "String resultado: " << result << endl;

	return 0;
}


