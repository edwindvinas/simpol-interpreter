%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nodes.h"
#include "interpreter.h"
#include "cmd.h"

#include "log.h"

extern FILE* yyin;
extern int* yylineno;

void yyerror(const char *str) {
    fprintf(stderr, "line %d: %s\n", yylineno, str);
}

void yyprint(const char *str) {
    //fprintf(stderr, "line %d: %s\n", yylineno, str);
    LOG_PRINT("line %d: %s\n", yylineno, str);
}

Node* root;

%}
%union {
    int integer;
    char* strval;
    Node* node;
}

%type <node> root
%type <node> stmts
%type <node> stmt
%type <node> expr
/*%type <node> variable_block_expr
%type <node> var_data_types*/
%type <node> arguments
%type <node> argument_list
%type <node> call_arguments
%type <node> call_argument_list
%type <integer> T_INTEGER
%type <integer> T_IDENTIFIER
%type <string> T_STRING
/*%type <string> STRING_LITERAL*/
%type <strval> T_STRING_LITERAL;
%type <boolean> T_BOOL

%token T_VAR T_BEGIN T_END T_LOOP T_FOR T_SUB T_IF T_THEN T_ELSE T_PRINT T_RETURN T_STRING T_BOOL T_VARIABLES T_CODES T_PUT T_ASK T_PRT T_IN T_FALSE T_TRUE
%token T_BIGGER T_LESS T_LESS_EQUAL T_BIGGER_EQUAL T_ASSIGN T_SEMICOLON T_EQUAL T_PLUS T_ADD T_SUBT T_MUL T_DIV T_MOD T_MINUS T_DIVIDE T_MULTIPLY T_MODULO T_NOT T_COMMA T_BINARY_OR T_BINARY_AND T_OPEN_BRACKET T_CLOSE_BRACKET T_UNARY_MINUS T_OPEN_CURLY_BRACKET T_CLOSE_CURLY_BRACKET T_DOLLAR
%token T_IDENTIFIER
%token T_INTEGER
%token T_STRING_LITERAL
/*%token T_FALSE T_TRUE*/
%start root

%left T_BINARY_OR
%left T_BINARY_AND
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_MODULO
%left T_UNARY_MINUS

%%
/*
var b := 3;
print b;
*/
root: stmts {$$ = $1; root = $$; }

stmts: /* empty */ {$$ = create_node(N_END_OF_PROGRAM, NULL, NULL, NULL, 0, ""); yyprint("PATTERN: end of program");}
     | stmt stmts {$$ = create_node(N_STMT, $1, $2, NULL, 0, ""); yyprint("PATTERN: stmt stmts");}

stmt: T_LOOP stmt T_FOR expr {$$ = create_node(N_LOOP_BLOCK_FOR, $2, $4, NULL, 0, "");  yyprint("PATTERN: T_LOOP stmt T_FOR expr");}
    | T_LOOP T_FOR expr stmt {$$ = create_node(N_LOOP_FOR_BLOCK, $3, $4, NULL, 0, "");  yyprint("PATTERN: T_LOOP T_FOR expr stmt");}
    | expr T_SEMICOLON {;}
    | T_BEGIN stmts T_END {$$ = $2;  yyprint("PATTERN: T_BEGIN stmts T_END");}
    | T_IF expr T_THEN stmt {$$ = create_node(N_IF, $2, $4, NULL, 0, "");  yyprint("PATTERN: T_IF expr T_THEN stmt");}
    | T_SUB T_IDENTIFIER T_OPEN_BRACKET arguments T_CLOSE_BRACKET stmt {$$ = create_node(N_SUB, $4, $6, NULL, $2, "");  
									yyprint("PATTERN: T_SUB T_IDENTIFIER T_OPEN_BRACKET arguments T_CLOSE_BRACKET stmt");}
    | T_IF expr T_THEN stmt T_ELSE stmt {$$ = create_node(N_IF_ELSE, $2, $4, $6, 0, "");  yyprint("PATTERN: T_IF expr T_THEN stmt T_ELSE stmt");}
    /*| T_VARIABLES T_OPEN_CURLY_BRACKET {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_VARIABLES T_OPEN_CURLY_BRACKET");} 
    | T_CODES T_OPEN_CURLY_BRACKET {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_CODES T_OPEN_CURLY_BRACKET");}*/ 
    | T_VARIABLES T_OPEN_CURLY_BRACKET stmts T_CLOSE_CURLY_BRACKET {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  
									yyprint("PATTERN: T_VARIABLES T_OPEN_CURLY_BRACKET stmts T_CLOSE_CURLY_BRACKET");} 
    | T_CODES T_OPEN_CURLY_BRACKET stmts T_CLOSE_CURLY_BRACKET {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  
									yyprint("PATTERN: T_CODES T_OPEN_CURLY_BRACKET stmts T_CLOSE_CURLY_BRACKET");} 
    | T_STRING T_IDENTIFIER {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_STRING T_IDENTIFIER");} 
    /*| T_IN T_IDENTIFIER {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_IN T_IDENTIFIER");} */
    | T_INTEGER T_IDENTIFIER {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_INTEGER T_IDENTIFIER");} 
    | T_BOOL T_IDENTIFIER {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_BOOL T_IDENTIFIER");} 
    | T_BOOL T_IN expr {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: T_BOOL T_IDENTIFIER");} 
    /*| T_PUT T_DOLLAR STRING_LITERAL T_DOLLAR T_IN expr {$$ = create_node(N_STMT, $3, $6, NULL, 0, "");  yyprint("PATTERN: T_BOOL T_IDENTIFIER");} */
    /*| T_PUT expr T_IN expr {$$ = create_node(N_STMT, $2, $4, NULL, 0, "");  yyprint("PATTERN: T_PUT expr T_IN expr");} 
    | T_IN T_IDENTIFIER {$$ = create_node(N_STMT, NULL, NULL, NULL, 0, $2);  yyprint("PATTERN: T_PUT expr T_IN expr");} */
    | T_PUT expr stmt {$$ = create_node(N_STMT, $2, $3, NULL, 0, "");  yyprint("PATTERN: T_PUT expr T_IN expr");}
    | T_IN expr {$$= create_node(N_STMT, $2, NULL, NULL, 0, "");  yyprint("PATTERN: T_IN expr");}
    | T_ASK expr {$$= create_node(N_STMT, $2, NULL, NULL, 0, "");  yyprint("PATTERN: T_ASK expr");}

/*variable_block_expr: var_data_types expr {$$ = create_node(N_STMT, $2, NULL, NULL, 0, "");  yyprint("PATTERN: var_data_types expr");}

var_data_types: T_STRING expr {$$ = create_node(N_STRING, $2, NULL, NULL, 0, "");  yyprint("PATTERN: T_STRING expr");}*/ 

arguments: /* empty */ {$$ = create_node(N_END_OF_ARG_LIST, NULL, NULL, NULL, 0, "");  yyprint("PATTERN: end of argument list");}
         | argument_list

argument_list: T_IDENTIFIER {$$ = create_node(N_ARGUMENT, NULL, NULL, NULL, $1, "");  yyprint("PATTERN: T_IDENTIFIER");}
             | T_IDENTIFIER T_COMMA argument_list {$$ = create_node(N_ARGUMENT, $3, NULL, NULL, $1, ""); yyprint("PATTERN: T_IDENTIFIER T_COMMA argument_list");}

call_arguments: /* empty */ {$$ = create_node(N_END_OF_ARG_LIST, NULL, NULL, NULL, 0, ""); yyprint("PATTERN: end of call arguments list");}
         | call_argument_list

call_argument_list: expr {$$ = create_node(N_ARGUMENT, $1, NULL, NULL, 0, ""); yyprint("PATTERN: expr");}
                  | expr T_COMMA call_argument_list {$$ = create_node(N_ARGUMENT, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_COMMA call_argument_list");}

expr:
    T_VAR T_IDENTIFIER T_ASSIGN expr {$$ = create_node(N_ASSIGNMENT, $4, NULL, NULL, $2, ""); yyprint("PATTERN: T_VAR T_IDENTIFIER T_ASSIGN expr");}
    | T_DOLLAR T_STRING_LITERAL T_DOLLAR {$$ = create_node(N_STRING, NULL, NULL, NULL, 0, $2); yyprint("PATTERN: T_DOLLAR T_STRING_LITERAL T_DOLLAR");}
    | T_IN T_IDENTIFIER {$$ = create_node(N_IN, NULL, NULL, NULL, $2, ""); yyprint("PATTERN: T_IN T_IDENTIFIER");}
    | T_TRUE T_IN T_IDENTIFIER {$$ = create_node(N_BOOL, NULL, NULL, NULL, $3, "true"); yyprint("PATTERN: T_TRUE T_IN T_IDENTIFIER");}
    | T_FALSE T_IN T_IDENTIFIER {$$ = create_node(N_BOOL, NULL, NULL, NULL, $3, "false"); yyprint("PATTERN: T_FALSE T_IN T_IDENTIFIER");}
    | T_ASK T_IDENTIFIER {$$ = create_node(N_ASK, NULL, NULL, NULL, $2, ""); yyprint("PATTERN: T_ASK T_IDENTIFIER");}
    /*| T_PRINT expr {$$ = create_node(N_PRINT, $2, NULL, NULL, 0, ""); yyprint("PATTERN: T_PRINT expr");}*/
    | T_INTEGER {$$ = create_node(N_INT, NULL, NULL, NULL, $1, ""); yyprint("PATTERN: T_INTEGER");}
    | expr T_EQUAL expr {$$ = create_node(N_EQUAL, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_EQUAL expr");}
    | T_IDENTIFIER T_OPEN_BRACKET call_arguments T_CLOSE_BRACKET {
			$$ = create_node(N_CALL, $3, NULL, NULL, $1, ""); 
			yyprint("PATTERN: T_IDENTIFIER T_OPEN_BRACKET call_arguments T_CLOSE_BRACKET");}
    | T_IDENTIFIER {$$ = create_node(N_VARIABLE, NULL, NULL, NULL, $1, ""); yyprint("PATTERN: T_IDENTIFIER");}
    /*| T_DOLLAR T_INTEGER T_DOLLAR {$$ = create_node(N_INT, NULL, NULL, NULL, $2, ""); yyprint("PATTERN: T_DOLLAR STRING_LITERAL T_DOLLAR");}*/
    | expr T_BINARY_OR expr {$$ = create_node(N_BINARY_OR, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_BINARY_OR expr");}
    | expr T_BINARY_AND expr {$$ = create_node(N_BINARY_AND, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_BINARY_AND expr");}
    | expr T_PLUS expr {$$ = create_node(N_ADDITION, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_PLUS expr");}
    | T_ADD expr expr {$$ = create_node(N_ADDITION, $2, $3, NULL, 0, ""); yyprint("PATTERN: T_ADD expr expr");}
    | expr T_MINUS expr {$$ = create_node(N_SUBTRACTION, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_MINUS expr");}
    | expr T_MULTIPLY expr {$$ = create_node(N_MULTIPLY, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_MULTIPLY expr");}
    | expr T_DIVIDE expr {$$ = create_node(N_DIVIDE, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_DIVIDE expr");}
    | expr T_MODULO expr {$$ = create_node(N_MODULO, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_MODULO expr");}
    | expr T_LESS expr {$$ = create_node(N_LESS, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_LESS expr");}
    | expr T_LESS_EQUAL expr {$$ = create_node(N_LESS_EQUAL, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_LESS_EQUAL expr");}
    | expr T_BIGGER expr {$$ = create_node(N_BIGGER, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_BIGGER expr");}
    | expr T_BIGGER_EQUAL expr {$$ = create_node(N_BIGGER_EQUAL, $1, $3, NULL, 0, ""); yyprint("PATTERN: expr T_BIGGER_EQUAL expr");}
    | T_MINUS expr %prec T_UNARY_MINUS {$$ = create_node(N_MINUS, $2, NULL, NULL, 0, ""); yyprint("PATTERN: T_MINUS expr %prec T_UNARY_MINUS");}
    | T_OPEN_BRACKET expr T_CLOSE_BRACKET {$$ = $2;}
    | T_NOT expr {$$ = create_node(N_NOT, $2, NULL, NULL, 0, ""); yyprint("PATTERN: T_NOT expr");}
    | T_RETURN {$$ = create_node(N_RETURN, NULL, NULL, NULL, 0, ""); yyprint("PATTERN: T_RETURN");}
    | T_RETURN expr {$$ = create_node(N_RETURN, $2, NULL, NULL, 0, ""); yyprint("PATTERN: T_RETURN expr");}


%%

void scan_string(const char* str) {
    LOG_PRINT("SCAN: %s\n", str);
    yy_switch_to_buffer(yy_scan_string(str));
}

/*void getInput() {
    LOG_PRINT("GET INPUT");
}*/

int main(int argc, char *argv[]) {
    Options* options = parse_cmd(argc, argv);

    yyin = fopen(options->file, "r");

    if (yyin == NULL) {
        printf("ERROR: Could not read file!\n");
        LOG_PRINT("ERROR: Could not read file!");
        return EXIT_FAILURE;
    }

    LOG_PRINT("Execute yyparse()");
    yyparse();
    LOG_PRINT("Execute start_interpreter()");
    start_interpreter(root, options->debug, 0);
    return EXIT_SUCCESS;
}

