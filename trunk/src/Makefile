all: c2composite unit_tests

unit_tests: 
	make -C ../unit_tests/

test: exec_tests exec_unit_tests
	
exec_tests:
	make -C ../tests/

exec_unit_tests:
	make -C ../unit_tests/ test

util.o: util.c util.h
	gcc -c util.c

c2composite: ansi.c.grammar.tab.o lex.yy.c util.o
	cc lex.yy.c ansi.c.grammar.tab.o util.o -o c2composite

ansi.c.grammar.tab.c ansi.c.grammar.tab.h: ansi.c.grammar.y
	bison -d ansi.c.grammar.y

ansi.c.grammar.tab.o: ansi.c.grammar.tab.c
	gcc -c ansi.c.grammar.tab.c

lex.yy.c: ansi.c.grammar.tab.h ansi.c.grammar.tab.h ansi.c.grammar.lex
	flex ansi.c.grammar.lex

clean:
	rm -f ansi.c.grammar.tab.c ansi.c.grammar.tab.h lex.yy.c c2composite *.o
	make -C ../unit_tests/ clean
