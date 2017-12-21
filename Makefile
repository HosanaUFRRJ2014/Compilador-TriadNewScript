all:


		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/wexemplo00.tns > codigo.cpp

all-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/wexemplo00.tns > codigo.cpp
		g++ codigo.cpp -o cod
		./cod


all-no-code:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/wexemplo00.tns


all-clear:
		rm y.tab.c y.tab.h lex.yy.c cod glf y.output


#Makefile para o hexemplo00.tns
all2:


		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/hexemplo00.tns > codigo.cpp

all2-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/hexemplo00.tns > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

all2-no-code:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/hexemplo00.tns

#Makefile para o lexemplo00.tns
all3:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/lexemplo00.tns > codigo.cpp

all3-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/lexemplo00.tns > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

all3-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplos/lexemplo00.tns

#Makefile para o teste1.tns
allT0:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste0.tns > codigo.cpp

allT0-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste0.tns > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

allT0-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste0.tns

#Makefile para o teste1.tns
allT:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste1.tns > codigo.cpp

allT-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste1.tns > codigo.cpp
		g++ arquivos_diversos/codigo.cpp -o cod
		./cod

allT-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste1.tns

#Makefile para o teste2.tns
allT2:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste2.tns > codigo.cpp

allT2-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste2.tns > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

allT2-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < arquivos_diversos/teste2.tns
