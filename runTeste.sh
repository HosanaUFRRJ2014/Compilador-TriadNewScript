#!/bin/bash

if [ $2 = "t" ] #imprime código no terminal
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < exemplos/$1
fi

if [ $2 = "run" ] #executa o código fornecido
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < exemplos/$1 > codigo.cpp
  g++ codigo.cpp -o cod
  ./cod
fi

if [ $2 = "c" ] #envia o código fornecido na linguagem de 3 endereços para um arquivo de nome codigo.cpp
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < exemplos/$1 > codigo.cpp
fi

