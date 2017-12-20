#!/bin/bash

if [ $2 = "t" ]
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < $1
fi

if [ $2 = "run" ]
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < $1 > codigo.cpp
  g++ codigo.cpp -o cod
  ./cod
fi

if [ $2 = "c" ]
then
  clear
  lex lexica.l
  yacc -d -v sintatica.y
  g++ -std=c++0x -o glf y.tab.c -lfl

  ./glf < $1 > codigo.cpp
fi
