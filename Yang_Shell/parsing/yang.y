%{
#include <stdio.h>
#include <stdlib.h>
#include "wordListNode.h"
#include "CommandTable.h"
 
int yylex(void);
void yyerror(char * s);
CommandTable * commandTable;

%}

%union{
	long iValue;
	char * sValue;
	CommandArgument * cArg;
	CommandTableEntry * cEntry;
}

%token<sValue> WORD
%token<iValue> INTEGER

%type<cArg> argument
%type<cEntry> commandEntry

%%

shell: shell commandLine
	| 
	;

commandLine :	commandEntry '\n'	{
		    			//execute the command; pass the command to some other func; 
					AppendEntry(commandTable, $1);
    					}
		| '\n'
		;

commandEntry:	WORD	{
				$$ = MakeCommandTableEntry($1);
    			}
		|
		commandEntry argument	{
				AddCommandArgument($1, $2);
		}
		;

argument:	WORD 	{
    				$$ = MakeCommandArgumentFromWord($1);
    			}
		|
		INTEGER {
				$$ = MakeCommandArgumentFromInt($1);
		    	}
		;

%%

void yyerror(char * s){
	printf("%s \n", s);
}

int main(void) {
	commandTable = MakeCommandTable(20); // initializes the list; 
	yyparse();
	free(commandTable);
	return 0;
}
