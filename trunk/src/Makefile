all:
	bison -d ansi.c.grammar.y
	flex ansi.c.grammar.lex
	cc lex.yy.c ansi.c.grammar.tab.c -o c2composite

clean:
	rm ansi.c.grammar.tab.c ansi.c.grammar.tab.h lex.yy.c c2composite
