Test1:
	gcc -o WordNodeListTest wordListNodeTest.c

Test2:
	gcc -o CommandTableTest CommandTable.c CommandTableTest.c

Test2Deb: 
	gcc -o CommandTableTestDeb -g CommandTable.c CommandTableTest.c

Yang: LexFile YaccFile
	gcc -o YangShell lex.yy.c y.tab.c CommandTable.c

LexFile: 
	lex yang.l

YaccFile:
	yacc -d yang.y
