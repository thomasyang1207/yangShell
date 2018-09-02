# Makefile for the calculator

calculator: lexFile yacFiles
	cc -o calculator lex.yy.c y.tab.c -O2


lexFile: 
	lex calculator.l

yacFiles:
	yacc -d calculator.y
