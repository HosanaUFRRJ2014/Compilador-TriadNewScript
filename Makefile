all:


		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca > codigo.cpp

all-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca > codigo.cpp
		g++ codigo.cpp -o cod
		./cod


all-no-code:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca


all-clear:
		rm y.tab.c y.tab.h lex.yy.c cod glf y.output


#Makefile para o exemplo2.foca
all2:


		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo2.foca > codigo.cpp

all2-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo2.foca > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

all2-no-code:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo2.foca

#Makefile para o exemplo3.foca
all3:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo3.foca > codigo.cpp

all3-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo3.foca > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

all3-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo3.foca
		
#Makefile para o teste1.foca
allT:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste1.foca > codigo.cpp

allT-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste1.foca > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

allT-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste1.foca

#Makefile para o teste2.foca
all2:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste2.foca > codigo.cpp

allT2-run:

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste2.foca > codigo.cpp
		g++ codigo.cpp -o cod
		./cod

allT2-no-code:

		clear
		lex lexica.l
		yacc -d -v -t sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < teste2.foca
