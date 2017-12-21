/*
	var a = "qq string";
	var b = "qq ";
	var c = a - b;
*/
#define TRUE 1
#define FALSE 0

int main(){
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int t9;
	int t10;
	int t11;
	int t12;
	
	
	char VARUSER_a[9];
	char VARUSER_b[3];
	char VARUSER_C[9]; //na pior das hipoteses ela não retira nada então pode ter o tamanho da primeira
	int t100[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	//da pra fazer um loop disso no código do yacc e gerar de acordo com o tamanho da string que vai ter os caracteres retirados
	//esse array é só pra guardar os indices removidos
	
	t1 = 0; //indice do loop de fora
	VERIFY1: t2 = t1 < 9;//tamanho da string1
	t2 = !t2;
	if(t2) goto FIMLOOP1;
	
		t3 = 0;//indice do loop de dentro
		t5 = 0;//qtd de "match" das strings
		VERIFY2: t4 = t3 < 3;//tamanho da string1
		t4 = !t4;
		if(t3) goto FIMLOOP2;
			t8 = t1+t3; // pra poder andar nas duas strings
			t9 = t8 > 9; //tamanho da string1 (quer dizer que passou do limite da string1
			if(t9) goto FIMLOOP1;
			
			t6 = VARUSER_a[t8] != VARUSER_b[t3];
			if(t6) goto INCREMENTO1;
			
			t5 = t5+1;
			t7 = t5 == 3; //tamanho da string2;
			if(t7) goto REMOVE_STRING;
			
			INCREMENTO2: t3 = t3 + 1;
			goto VERIFY2;
			
			
/*			//não é necessário, pode ir direto pra incremento 1 pois a var t5 é zerada lá em cima
			RETORNO1: t5 = 0;
			goto INCREMENTO1;
			*/
			
			REMOVE_STRING: 
			t100[t8] = TRUE;
			t8 = t8 - 1;
			t100[t8] = TRUE;
			t8 = t8 - 1;
			t100[t8] = TRUE;
			//repete o qnts vezes for o tamanho da string2
			t3 = t8 + 3;
			goto VERIFY1;
			
		FIMLOOP2:
		
	INCREMENTO1: t1 = t1+1;
	goto VERIFY1;
	
	FIMLOOP1:
	
	t9 = 0;
	t10 = 0;
	VERIFY3: t11 = t10 < 9
	t11 = !t11;
	if(t11) goto FIMLOOP3;
		t12 = t100[t10] == TRUE; //se for pra remover o caracter pula ele
		if(t12) goto INCREMENTO3;
		VARUSER_c[t9] = VARUSER_a[t10];//senão coloca no vetor destino e soma uma posicao
		t9 = t9+1;
		
		INCREMENTO3:
		t10 = t10+1;
		goto VERIFY3;
	FIMLOOP3:
	
	return 0;
}