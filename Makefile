all: 	


		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca > codigo.c


all-run:
	clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca > codigo.c
		g++ codigo.c -o cod
		./cod

all-no-code: 	

		clear
		lex lexica.l
		yacc -d -v sintatica.y
		g++ -std=c++0x -o glf y.tab.c -lfl

		./glf < exemplo.foca


no-string-lib-mode:
		clear
		lex lexica.l
		yacc -d sintatica.y
		g++ -o glf y.tab.c -lfl

		./glf < exemplo.foca
