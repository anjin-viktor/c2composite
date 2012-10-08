all:
	bison -d ansi.c.grammar.y
	flex ansi.c.grammar.lex
	cc lex.yy.c ansi.c.grammar.tab.c

clean:
	rm ansi.c.grammar.tab.c
	rm ansi.c.grammar.tab.h
	rm lex.yy.c
	rm a.out
