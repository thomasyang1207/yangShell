Test1:
	gcc -o WordNodeListTest wordListNodeTest.c

Yang: LexFile YaccFile
	gcc -o YangShell lex.yy.c y.tab.c

LexFile: 
	lex yang.l

YaccFile:
	yacc -d yang.y
