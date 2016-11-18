# Simpol Interpreter written in C for a fictional SIMPOL language

## Authors:

* Edwin D. Vinas

## About
* Simpol Interpreter written in C for a fictional SIMPOL language
* For someone who didn't study Computer Science, it is difficult to create an interpreter from scratch, let alone studying C
* We were taught about the basics of how compilers and interpreters work
* This project is a requirement to create a simple interpreter using C/C++/C#/Java but I am not comfortable coding in all of these language but given my college subject Turbo C, I decided to look for an existing interpreter in Github
* Forked Original Codes from: https://github.com/BernhardPosselt/interpreter
* Created own repository called https://github.com/edwindvinas/simpol-interpreter
* So what now? How to start? Where to start?
* https://docs.google.com/drawings/d/1bP3Y9BvOFyAi5F0yo8LWfVUbtyUkNCrsADHyaYRH1pE/edit
* Looking at the sample C interpreter, it uses Lex and Yacc for lexing and parsing

## What is Lex & Yacc?
Before 1975 writing a compiler was a very time-consuming process. Then Lesk [1975] and Johnson [1975] published papers on lex and yacc. These utilities greatly simplify compiler writing. Implementation details for lex and yacc may be found in Aho [2006]. Flex and bison, clones for lex and yacc, can be obtained for free from GNU [http://www.gnu.org/] and Cygwin [http://www.cygwin.com/].

Lex and Yacc tutorials:
* http://epaperpress.com/lexandyacc/
* http://epaperpress.com/lexandyacc/download/LexAndYaccTutorial.pdf
* http://epaperpress.com/lexandyacc/download/LexAndYaccCode.zip

![Compilation sequence using Lex and Yacc](http://lh3.googleusercontent.com/3-WIepgg26Dp0xiC5bFLaK_j6ui6xKywX10hKi7ft6dxMeLXD7LrZGYa027FuTpHu7kyvQ65cjHBrcv2UDMCFPJ7Lyox)

### Patterns
The patterns in the above diagram is a file you create with a text editor. Lex will read your patterns
and generate C code for a lexical analyzer or scanner. The lexical analyzer matches strings in the
input, based on your patterns, and converts the strings to tokens. Tokens are numerical
representations of strings, and simplify processing.

When the lexical analyzer finds identifiers in the input stream it enters them in a symbol table. The
symbol table may also contain other information such as data type (integer or real) and location of
each variable in memory. All subsequent references to identifiers refer to the appropriate symbol
table index.

### Grammar
The grammar in the above diagram is a text file you create with a text edtior. Yacc will read your
grammar and generate C code for a syntax analyzer or parser. The syntax analyzer uses grammar
rules that allow it to analyze tokens from the lexical analyzer and create a syntax tree. The syntax
tree imposes a hierarchical structure the tokens. For example, operator precedence and
associativity are apparent in the syntax tree. The next step, code generation, does a depth-first
walk of the syntax tree to generate code. Some compilers produce machine code, while others, as
shown above, output assembly language.

### Modules

    edwin_d_vinas  4096 Nov 19 00:07 .
    edwin_d_vinas  4096 Nov 19 00:07 ..
    edwin_d_vinas   603 Nov 18 22:32 cmd.c
    edwin_d_vinas   125 Nov 18 22:32 cmd.h
    edwin_d_vinas  4096 Nov 18 22:42 .git
    edwin_d_vinas 35112 Nov 18 22:42 interpreter <-- executable
    edwin_d_vinas  7147 Nov 18 22:32 interpreter.c
    edwin_d_vinas   332 Nov 18 22:32 interpreter.h
    edwin_d_vinas   904 Nov 18 22:32 lexer.l <-- contains patterns
    edwin_d_vinas 49583 Nov 18 22:42 lex.yy.c <-- temp file (generated lexical analyzer)
    edwin_d_vinas   215 Nov 18 22:32 Makefile <-- compile options
    edwin_d_vinas  1872 Nov 18 22:32 nodes.c
    edwin_d_vinas   949 Nov 18 22:32 nodes.h
    edwin_d_vinas  4341 Nov 18 22:32 parser.y <-- your grammar/token delarations
    edwin_d_vinas  4096 Nov 18 22:32 programs
    edwin_d_vinas  1971 Nov 18 22:42 README.md
    edwin_d_vinas 55708 Nov 18 22:42 y.output <-- temp file
    edwin_d_vinas 58805 Nov 18 22:42 y.tab.c <-- temp file (generated parser)
    edwin_d_vinas  3514 Nov 18 22:42 y.tab.h <-- temp file (token definitions)

### Generating Executable Compiler/Interpreter
![Building a compiler with Lex and Yacc](http://lh3.googleusercontent.com/cof5y0SLOc6yeNT-Em8Lm4S-FFzwr5B6w4HXg3ENZIGJHvJc-Djn5PY80NfTjR0r2teFWmEujQdabfCtZ7fzugydIhrC)

Yacc reads the grammar descriptions in bas.y and generates a syntax analyzer (parser), that
includes function yyparse, in file y.tab.c. Included in file bas.y are token declarations. The –d
option causes yacc to generate definitions for tokens and place them in file y.tab.h. Lex reads the
pattern descriptions in bas.l, includes file y.tab.h, and generates a lexical analyzer, that includes
function yylex, in file lex.yy.c.

    yacc –d bas.y                 # create y.tab.h, y.tab.c
    lex bas.l                     # create lex.yy.c
    cc lex.yy.c y.tab.c –obas.exe # compile/link

Finally, the lexer and parser are compiled and linked together to create executable bas.exe. From
main we call yyparse to run the compiler. Function yyparse automatically calls yylex to obtain
each token.

A more detailed discussion of the Lex and Yacc are in this tutorial: http://epaperpress.com/lexandyacc/download/LexAndYaccTutorial.pdf

### Makefile for simpol-interpreter

    all: clean
    	lex lexer.l
    	yacc -d -v parser.y
    	cc lex.yy.c y.tab.c cmd.c interpreter.c nodes.c -o simpol-interpreter -lfl
    
    clean:
    	rm -f interpreter
    	rm -f lex.yy.c
    	rm -f y.tab.c
    	rm -f y.tab.h
    	rm -f y.output
    
    dist: clean

## Dependencies

* getopt
* bison
* flex
* make

## Downloading
Clone a copy to your local machine

	git clone https://github.com/edwindvinas/simpol-interpreter.git
	cd simpol-interpreter/
	
## Compiling
Run:

    make

## Running a sample .sim file
To execute a file pass the path as its first argument like:

    ./simpol-interpreter programs/myprogram.sim

## Run in Debug Mode

Run:

    ./simpol-interpreter programs/myprogram.sim -d
	
## Sample Simpol file (.sim)

	variable {
	STG str
	STG name
	INT num1
	INT num2
	INT num3
	BLN bol1
	BLN bol2
	}
	 
	code {
	PUT $The result is: $ IN str
	ASK name
	PUT true IN bol1
	PUT false IN bol2
	PUT ADD 1 2 IN num1
	PUT 100 IN num2
	 
	PRT $Your name is $
	PRT name
	PRT OHR true AND bol1 bol2
	PUT MUL 10 ADD num1 num2 IN num3
	PRT num3
	PRT DIV MUL 10 ADD num1 num2 MUL 10 ADD num1 num2
	PRT $Goodbye!$
	}
	
## Updating Github Repo (Initial commit)

	vi README.md
	git init
	git add README.md
	git commit -m "first commit"
	git remote add origin https://github.com/edwindvinas/simpol-interpreter.git
	git push -u origin master
	
	
## Push updates to Github Repo
	
	git add --all
	git commit -m "your commit comments"
	git remote add origin https://github.com/edwindvinas/simpol-interpreter.git
	git push -u origin master
	
## Running in Google Cloud Shell

	sudo apt-get install flex
	git clone https://github.com/edwindvinas/simpol-interpreter.git
	cd simpol-interpreter/	
	make
	./simpol-interpreter programs/myprogram.sim -d


### CUSTOMIZATION
### Makefile
You can update the destination filename of the interpreter.

    cc lex.yy.c y.tab.c cmd.c interpreter.c nodes.c -o simpol-interpreter -lfl

### cmd.c
You can output a text everytime the interpreter is run such as showing the interpreter name or version.

    /* SIMPOL INTERPRETER */
        printf("**********************************\n");
        printf("* Simpol Interpreter v2016.11.19 *\n");
        printf("**********************************\n");

## ERRORS & FIXES
	
## Error - recipe for target 'all' failed
	edwin_d_vinas@gcp-testbed:~/simpol-interpreter$ make
	rm -f interpreter
	rm -f lex.yy.c
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f y.output
	lex lexer.l
	make: lex: Command not found
	Makefile:2: recipe for target 'all' failed

## Fix
	sudo apt-get install flex
	make
	...
	

