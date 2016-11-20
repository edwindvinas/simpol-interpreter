%option noyywrap

%{
#include <stdio.h>
#include "nodes.h"
#include "y.tab.h"
#include <ctype.h>
#include <stdlib.h>
//char *s;
#include <string.h>
//#include <string>
//#include "StringBuffer.h"
//static StringBuffer strbuf;
%}

%%
variable {yyprint("KEYWORD: variable"); return T_VARIABLES;}
code {yyprint("KEYWORD: code"); return T_CODES;}
STG {yyprint("KEYWORD: STG"); return T_STRING;}
BLN {yyprint("KEYWORD: BLN"); return T_BOOL;}
INT {yyprint("KEYWORD: INT"); return T_INTEGER;}
	/*ASK {yyprint("KEYWORD: ASK"); return T_ASK;}*/
ASK {yyprint("KEYWORD: ASK"); getUserInput(); return T_ASK;}
PUT {yyprint("KEYWORD: PUT"); return T_PUT;}
true {yyprint("KEYWORD: true"); return T_TRUE;}
false {yyprint("KEYWORD: false"); return T_FALSE;}
IN {yyprint("KEYWORD: IN"); return T_IN;}
PRT {yyprint("KEYWORD: PRT"); return T_PRT;}
ADD {yyprint("KEYWORD: ADD"); return T_ADD;}
SUB {yyprint("KEYWORD: SUB"); return T_SUBT;}
MUL {yyprint("KEYWORD: MUL"); return T_MUL;}
DIV {yyprint("KEYWORD: DIV"); return T_DIV;}
MOD {yyprint("KEYWORD: MOD"); return T_MOD;}
var {yyprint("KEYWORD: var"); return T_VAR;}
begin {yyprint("KEYWORD: begin"); return T_BEGIN;}
end {yyprint("KEYWORD: end"); return T_END;}
for {yyprint("KEYWORD: for"); return T_FOR;}
loop {yyprint("KEYWORD: loop"); return T_LOOP;}
sub {yyprint("KEYWORD: sub"); return T_SUB;}
if {yyprint("KEYWORD: if"); return T_IF;}
then {yyprint("KEYWORD: then"); return T_THEN;}
else {yyprint("KEYWORD: else"); return T_ELSE;}
not {yyprint("KEYWORD: not"); return T_NOT;}
return {yyprint("KEYWORD: return"); return T_RETURN;}
print {yyprint("KEYWORD: print"); return T_PRINT;}


[a-zA-Z][0-9a-zA-Z_]* {yyprint("IDENTIFIER: "); yyprint(yytext); yylval.integer = *yytext - 'a'; return T_IDENTIFIER;}
[0123456789]+ {yyprint("INTEGER: "); yyprint(yytext); yylval.integer = atoi(yytext); return T_INTEGER;}
	/* \$                  { BEGIN string; ClearBuffer(strbuf); }
	<string>[^\\$\n]*   { AppendBufferString(strbuf, yytext); }
	<string>\\n         { AppendBufferChar(strbuf, '\n'); }
	<string>\\t         { AppendBufferChar(strbuf, '\t'); }
	<string>\\[0-7]*    { AppendBufferChar(strbuf, strtol(yytext+1, 0, 8)); }
	<string>\\[\\"]     { AppendBufferChar(strbuf, yytext[1]); }
	<string>\"          { yylval.string = strdup(BufferData(strbuf)); BEGIN 0; yyprint("found string literal"); return T_STRING_LITERAL; }
	<string>\\.         { yyprint("Error: bogus escape"); printf("bogus escape '%s' in string\n", yytext); }
	<string>\n          { yyprint("Error: newline in string"); printf("newline in string\n"); }
	*/
	/*\"[^"\n]*["\n] {*/

\$[^$\n]*[$] {
        yylval.strval = strdup(yytext+1);
       // if (yylval.strval[yyleng-2] != '"')
       //     warning("improperly terminated string");
       // else
       //     yylval.strval[yyleng-2] = 0;
        yyprint("STRING_LITERAL");
        yyprint(yylval.strval);
        //printf("found '%s'\n", yylval.strval);
	char mystr[60];
	//strcpy(mystr, strdup(yytext+1));
	strcpy(mystr, yylval.strval);
	char *p = mystr;
	p++[strlen(p)-1] = 0;
        yylval.strval = p;
        yyprint(yylval.strval);
    }
; {yyprint(yytext); return T_SEMICOLON;}
, {yyprint(yytext); return T_COMMA;}
\< {yyprint(yytext); return T_LESS;}
\> {yyprint(yytext); return T_BIGGER;}
\<= {yyprint(yytext); return T_LESS_EQUAL;}
\>= {yyprint(yytext); return T_BIGGER_EQUAL;}
= {yyprint(yytext); return T_EQUAL;}
:= {yyprint(yytext); return T_ASSIGN;}
\* {yyprint(yytext);  return T_MULTIPLY;}
\/ {yyprint(yytext); return T_DIVIDE;}
\+ {yyprint(yytext); return T_PLUS;}
- {yyprint(yytext); return T_MINUS;}
% {yyprint(yytext); return T_MODULO;}
\| {yyprint(yytext); return T_BINARY_OR;}
& {yyprint(yytext); return T_BINARY_AND;}
\( {yyprint(yytext); return T_OPEN_BRACKET;}
\) {yyprint(yytext); return T_CLOSE_BRACKET;}
\{ {yyprint(yytext); return T_OPEN_CURLY_BRACKET;}
\} {yyprint(yytext); return T_CLOSE_CURLY_BRACKET;}
\$ {yyprint(yytext); return T_DOLLAR;}
[ \t\r]+ /* ignore whitespace */;
\n {yylineno++;}
. {yyprint(yytext); printf("Encountered invalid character");}
%%

getUserInput()
{
    yyprint("Getting user input from keyboard");
    int max = 20;
    char* name = (char*)malloc(max); /* allocate buffer */
    if (name == 0) {
    	fprintf(stderr, "memory exhausted\n");
    	exit(1);
    }

    printf("Enter your name: ");

    while (1) { /* skip leading whitespace */
        int c = getchar();
        if (c == EOF) break; /* end of file */
        if (!isspace(c)) {
             ungetc(c, stdin);
             break;
        }
    }

    int i = 0;
    while (1) {
        int c = getchar();
        if (isspace(c) || c == EOF) { /* at end, add terminating zero */
            name[i] = 0;
            break;
        }
        name[i] = c;
        unput(c);
        if (i == max - 1) { /* buffer full */
            max = max + max;
            name = (char*)realloc(name, max); /* get a new and larger buffer */
            if (name == 0) {
    		fprintf(stderr, "memory exhausted\n");
    		exit(1);
	    } 
        }
        i++;
    }
    yyprint(name);
    //unput(yytext[yyleng-1]);
    //unput(name);
	//char mystr[60];
	//strcpy(mystr, strdup(yytext+1));
	//strcpy(mystr, name);
	//char *p = mystr;
	//p++[strlen(p)-1] = 0;
        //yylval.strval = p;
        //yyprint(yylval.strval);
    return;

}

