#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
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
    newEntry->numArgs = 0;

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
    tableEntry->numArgs++;
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

void executeCommand(CommandTableEntry * commandEntry){
    //
    if (strcmp(commandEntry->command, "dt") == 0){
        PrintCommandTable(commandTable);
        return;
    }
    
    if (strcmp(commandEntry->command, "cd") == 0){
        char * dir;
        if(commandEntry->args == NULL){
            dir = (char*)calloc(2, sizeof(char));
            sprintf(dir, "/");
        } else {
            size_t dirLen = strlen(commandEntry->args->data.word);
            dir = (char*)calloc(dirLen + 1, sizeof(char));
            sprintf(dir, "%s", commandEntry->args->data.word);
        }
        chdir(dir);
        free(dir);
        return;
    }
    
    int pid; 
    if((pid = fork()) == 0){
        //allocate space for an argv array;
        int argc = commandEntry->numArgs + 1;
        char ** argv = (char **) calloc(argc + 1, sizeof(char *));
        CommandArgument * cArg = commandEntry->args;
        
        for(int i = 1; i < argc; i++){
            char * thisArg = cArg->data.word;
            
            if(cArg->isNumber){
                sprintf(thisArg, "%li", cArg->data.number);
            }
            
            argv[i] = thisArg;
            cArg = cArg -> nextArgument;
        }
        
        //get path to program
        int pathLength = 5 + strlen(commandEntry->command) + 1;
        char * path = (char *)calloc(pathLength, sizeof(char));
        sprintf(path, "/bin/%s", commandEntry->command);
        
        argv[0] = path;
        execv(path, argv);
        
        //if still here, then try to execute from etc
        pathLength += 4;
        free(path);
        path = (char *)calloc(pathLength, sizeof(char));
        sprintf(path, "/usr/bin/%s", commandEntry->command);
        execv(path, argv);
        
        printf("Invalid command %s. Check if you've spelled everything correctly\n", commandEntry->command);
        free(path);
        free(argv);
        exit(1); // exit code during failure...
    } 
    while(pid != wait(0)); //wait for the process to end...

}

void printPrompt(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Yang(%s) >> ", cwd);
    } else {
        perror("getcwd() error");
        return;
    }
   return;
};



