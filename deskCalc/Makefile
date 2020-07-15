all:
	yacc -d yc.y
	lex lex.l
	gcc lex.yy.c y.tab.c -ll -ly
