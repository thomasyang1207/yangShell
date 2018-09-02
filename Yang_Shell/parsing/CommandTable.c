#include <stdlib.h>
#include <stdio.h>
#include "CommandTable.h"

CommandArgument * MakeCommandArgumentFromWord(char * s){
    CommandArgument * newArg;
    newArg = (CommandArgument *)malloc(sizeof(CommandArgument));
    newArg->data.word = s;
    newArg->nextArgument = NULL;
    newArg->isNumber = false; 

    return newArg;
}

CommandArgument * MakeCommandArgumentFromInt(long i){
    CommandArgument * newArg; 
    newArg = (CommandArgument *)malloc(sizeof(CommandArgument));
    newArg->data.number = i;
    newArg->nextArgument = NULL;
    newArg->isNumber = true;

    return newArg;
}

void ClearAndDeleteCommandArgument(CommandArgument * argument) {
    if(!argument->isNumber){
	free(argument->data.word);
    }
    free(argument);
}


CommandTableEntry * MakeCommandTableEntry(char * command) {
    CommandTableEntry * newEntry; 

    newEntry = (CommandTableEntry *)malloc(sizeof(CommandTableEntry));
    newEntry->command = command;
    newEntry->args = NULL;

    return newEntry;
}

void AddCommandArgument(CommandTableEntry * tableEntry, CommandArgument * argument){
    CommandArgument * curArg;
    if(tableEntry->args == NULL){
	tableEntry->args = argument;
    } else {
	curArg = tableEntry->args;
	while(curArg->nextArgument != NULL){
	    curArg = curArg->nextArgument;
	}
	curArg->nextArgument = argument;
    }
}

void ClearAndDeleteCommandTableEntry(CommandTableEntry * tableEntry){
    CommandArgument * curArg;
    CommandArgument * nextArg; 

    free(tableEntry->command);
    curArg = tableEntry->args;
    while(curArg != NULL){
	nextArg = curArg->nextArgument;
	ClearAndDeleteCommandArgument(curArg);
	curArg = nextArg;
    }
    free(tableEntry);
}

CommandTable * MakeCommandTable(size_t maxSize){
    CommandTable * table;
    
    table = malloc(sizeof(CommandTable));
    table->commandArray = calloc(maxSize, sizeof(CommandTableEntry *));
    table->maxSize = maxSize;
    table->ind = 0;

    return table;
}

void AppendEntry(CommandTable * table, CommandTableEntry * tableEntry) {
    if(table->ind >= table->maxSize){
	table->ind = 0;
    }
    
    if(table->commandArray[table->ind] != NULL) {
	ClearAndDeleteCommandTableEntry(table->commandArray[table->ind]);
    }

    table->commandArray[table->ind] = tableEntry;
    table->ind++;
}

void ClearAndDeleteCommandTable(CommandTable * table){
    size_t i;
    for(i = 0; i < table->maxSize; i++){
	if(table->commandArray[i] != NULL){
	    ClearAndDeleteCommandTableEntry(table->commandArray[i]);
	    table->commandArray[i] = NULL;
	}
    }	
    free(table);
}

CommandTableEntry * AccessCommandTableEntry(CommandTable * table, size_t ind) {
    //if found, return pointer to entry; otherwise, return NULL
    return table->commandArray[ind];
}

void PrintCommandTable(CommandTable * table) {
    size_t i;
    for(i = 0; i < table->maxSize; i++){
	//DO print only if table is NOT empty!!
	if(table->commandArray[i] != NULL){
	    printf("Command: %s \n", table->commandArray[i]->command);
	}
    }
}




