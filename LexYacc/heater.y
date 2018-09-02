
%token INTEGER
%token HEAT TARGET TEMPERATURE STATE

%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%% 

commands:
	| commands command
	;

command:
	target_set
	{
		printf("\t Command Received \n");
	}
	|
	heat_switch
	{
		printf("\t Command Received \n");
	}
	;


heat_switch:
	HEAT STATE
	;


target_set:
	TARGET TEMPERATURE INTEGER
	;

%%

void yyerror(char * s){
	fprintf(stdout, "%s\n", s);
}

int main(void){
	yyparse();
	return 0; 
}
