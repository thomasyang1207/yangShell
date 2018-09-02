/* calculator yacc file */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
void yyerror(char*);
int yylex();
%}

%token INTEGER

%% 
goal: statement {printf("your answer is %d\n", $1); }

statement:
	addStatement	{$$ = $1;}
	|
	subStatement	{$$ = $1;}
	|
	INTEGER		{$$ = $1;}

addStatement: 
	INTEGER '+' INTEGER	{$$ = $1 + $3;}

subStatement: 
	INTEGER	'-' INTEGER	{$$ = $1 - $3;}

%%

void yyerror(char *s){
	printf(s);
}

int main(void){
	yyparse();
	return 0;
}
