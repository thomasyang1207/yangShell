#include "CommandTable.h"
#include <stdio.h>
#include <string.h>
static CommandTable * globalTable;
static CommandTableEntry * currentEntry;

int main() {

    // Test 1 
    CommandTableEntry * testEntry;
    CommandArgument * wordArgContainer;
    CommandArgument * intArgContainer;
    char * testWord;

    globalTable = MakeCommandTable(10);
    testWord = strdup("what");
    wordArgContainer = MakeCommandArgumentFromWord(testWord);
    intArgContainer = MakeCommandArgumentFromInt(1);
    testWord = strdup("get");
    testEntry = MakeCommandTableEntry(testWord);
    
    AddCommandArgument(testEntry, wordArgContainer); 
    AddCommandArgument(testEntry, intArgContainer);
    AppendEntry(globalTable, testEntry);

    PrintCommandTable(globalTable);
    ClearAndDeleteCommandTable(globalTable);
    printf("Test 1: success!\n");

    /**************************************************************/

    // Test 2 
    globalTable = MakeCommandTable(3);
    testWord = strdup("ls");
    testEntry = MakeCommandTableEntry(testWord);
    AppendEntry(globalTable, testEntry); 

    testWord = strdup("cd"); 
    testEntry = MakeCommandTableEntry(testWord); 
    AppendEntry(globalTable, testEntry);

    testWord = strdup("bs"); 
    testEntry = MakeCommandTableEntry(testWord);
    AppendEntry(globalTable, testEntry);

    PrintCommandTable(globalTable);

    printf("Test 2: success!\n");

    return 0;
}
