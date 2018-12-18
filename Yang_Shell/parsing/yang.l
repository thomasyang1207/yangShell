/* lexer file */

%{

#include <stdio.h>
#include "CommandTable.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

[ \t]* 	{}


0	{
    	yylval.iValue = 0;
    	return INTEGER;}

[1-9][0-9]*	{
    		yylval.iValue = atoi(yytext);
		return INTEGER;
		}

\"*[a-zA-Z][a-zA-Z0-9]*\.*[a-zA-Z][a-zA-Z0-9]*\"*  {
	yylval.sValue = strdup(yytext);
	return WORD;
	}

\n 	return *yytext;

.	yyerror("unknown character");


%%

int yywrap(void) {
	return 1;
}
