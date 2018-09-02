

%{
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *);

%}

%%

[ \t\n]		{}

"0"		{yylval = 0;
		return INTEGER;}

[1-9][0-9]*	{/* track the value, and return that it is */
			yylval = atoi(yytext); 
			return INTEGER;
		}

[-+]		{return *yytext;}

.		{yyerror("undefined character");}


%%

/*subroutines*/

int yywrap(void) {
	return 1;
}
