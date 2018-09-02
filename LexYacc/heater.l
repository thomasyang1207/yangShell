%{
#include "y.tab.h"
#include "stdio.h"
%}

%%

[ \t]	{/*ignore*/}

heat	{printf("\t heat detected");
	return HEAT;}

on|off	{printf("\t on/off detected");
	return STATE;}

target	return TARGET;

temperature	return TEMPERATURE;

[1-9][0-9]*	return INTEGER;

.		{}

%%

int yywrap(void) {
	return 1;
}
