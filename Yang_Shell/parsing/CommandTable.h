#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H
// How to structure a command table? 

//What is a "command" ? - is a WORD followed by other words; 

struct CommandArgument {
    //allows us to use numbers or words; 
    union {
	    char * word;
	    long number;
    } data; 
    struct CommandArgument * nextArgument;
    bool isNumber;
};

typedef struct CommandArgument CommandArgument;

struct CommandTableEntry {
    char * command; 
    CommandArgument * args;
    size_t numArgs;
};

typedef struct CommandTableEntry CommandTableEntry; 

struct CommandTable {
    //List of CommandTableEntries? 
    CommandTableEntry ** commandArray; //array of commandEntries
    size_t maxSize;
    size_t ind; //index marks the head of the CTable... we overwrite the older entries if exceeding the command table..
};

typedef struct CommandTable CommandTable;


// Functions 

CommandArgument * MakeCommandArgumentFromWord(char * s);

CommandArgument * MakeCommandArgumentFromInt(long i);

void ClearAndDeleteCommandArgument(CommandArgument * argument);

CommandTableEntry * MakeCommandTableEntry(char * command);

void AddCommandArgument(CommandTableEntry * tableEntry, CommandArgument * argument);

void ClearAndDeleteCommandTableEntry(CommandTableEntry * tableEntry); 

CommandTable * MakeCommandTable(size_t maxSize);

void AppendEntry(CommandTable * table, CommandTableEntry * tableEntry); 

void ClearAndDeleteCommandTable(CommandTable * table);

CommandTableEntry * AccessCommandTableEntry(CommandTable * table, size_t ind);

void PrintCommandTable(CommandTable * table);

void executeCommand(CommandTableEntry * commandEntry);


#endif 
