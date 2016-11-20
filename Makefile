all: clean
	lex lexer.l
	yacc -d -v parser.y
	cc lex.yy.c y.tab.c cmd.c interpreter.c nodes.c log.c -o simpol-interpreter -lfl

clean:
	rm -f interpreter
	rm -f lex.yy.c
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f y.output

dist: clean
