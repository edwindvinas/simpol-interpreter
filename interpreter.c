#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"
#include "nodes.h"

#include "log.h"

//#define BUF_SIZE 300

Scope* scope;
Sub* subs[26];

/**
 * Creates a new scope
 */
Scope* push_scope(Scope* previous_scope) {
    LOG_PRINT("push_scope()");
    Scope* newScope = malloc(sizeof(Scope));
    int i;

    if (previous_scope == NULL) {
        newScope->previous_scope = NULL;

        for (i=0; i<26; i+=1) {
            newScope->symbols[i] = 0;
        }
    	//LOG_PRINT("newScope: %s", previous_scope);

    } else {
        newScope->previous_scope = previous_scope;
        // if a scope exists, copy all the values from the previous scope so we
        // dont change them; this language is function scoped (like JavaScript muhahaha)
        for (i=0; i<26; i+=1) {
            newScope->symbols[i] = previous_scope->symbols[i];
    	    LOG_PRINT("newScope: %s", newScope->symbols[i]);
        }
    }

    return newScope;
}

/**
 * Pops the current one and returns the previous scope
 */
Scope* pop_scope(Scope* scope) {
    LOG_PRINT("pop_scope");
    if (scope->previous_scope == NULL) {
        LOG_PRINT("Error! Popping last scope");
        printf("Error! Popping last scope\n");
        exit(EXIT_FAILURE);
    } else {
        Scope* previous_scope = scope->previous_scope;
        free(scope);
        return previous_scope;
    }
}

int call_sub(Sub* sub, Node* callArguments, int debug, int indention) {
    LOG_PRINT("call_sub()");
    // a function call creates a new scope and initializes the values
    scope = push_scope(scope);
    Node* subArg = sub->arguments;
    while (subArg != NULL
           && callArguments != NULL
           && callArguments->type != N_END_OF_ARG_LIST
           && subArg->type != N_END_OF_ARG_LIST) {
        int symbol = subArg->value;
        scope->symbols[symbol] = interpret(callArguments->left, debug, indention);
        callArguments = callArguments->middle;
        subArg = subArg->left;
    }

    interpret(sub->stmt, debug, indention);
    int result = scope->return_value;
    scope = pop_scope(scope);
    return result;
}

/**
 * Used to intialize the values like the scope to start interpreting
 */
int start_interpreter(Node* node, int debug, int indention) {
    LOG_PRINT("start_interpreter()");
    scope = push_scope(NULL);
    return interpret(node, debug, indention);
}

/**
 * Interpret a node
 */
int interpret(Node* node, int debug, int indention) {
    //LOG_PRINT("interpret() %s", node);
    if (debug == 1) {
        debug_node(node, indention);
    }
    indention++;

    if (node != NULL) {
        int i;
        int times;
        Sub* sub;
	
	//printf("node->type = %s\n", node->type);
	//printf("%s\n", node);
        switch (node->type) {

        case N_STMT:
            LOG_PRINT("interpret: N_STMT");
            interpret(node->left, debug, indention);
            if (node->middle != NULL) {
                //LOG_PRINT("interpret: N_STMT");
                interpret(node->middle, debug, indention);
                //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            }
            break;

        case N_IF:
            LOG_PRINT("interpret: N_IF");
            if (interpret(node->left, debug, indention)) {
                //LOG_PRINT("interpret: N_IF");
                return interpret(node->middle, debug, indention);
                //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            }
            return 0;

        case N_IF_ELSE:
            LOG_PRINT("interpret: N_IF_ELSE");
            if (interpret(node->left, debug, indention)) {
                //LOG_PRINT("interpret: N_IF_ELSE");
                //LOG_PRINT("%d", interpret(node->middle, debug, indention));
                return interpret(node->middle, debug, indention);
            } else {
                //LOG_PRINT("%d", interpret(node->right, debug, indention));
                return interpret(node->right, debug, indention);
            }
            return 0;

        case N_INT:
            LOG_PRINT("interpret: N_INT");
            LOG_PRINT("%d", node->value);
            return node->value;

        case N_STRING:
            LOG_PRINT("interpret: N_STRING");
            LOG_PRINT("%s", node->value);
            return node->value;

        case N_VARIABLE:
            LOG_PRINT("interpret: N_VARIABLE");
            LOG_PRINT("%d", scope->symbols[node->value]);
            return scope->symbols[node->value];

        case N_EQUAL:
            LOG_PRINT("interpret: N_EQUAL");
            return interpret(node->left, debug, indention) == interpret(node->middle, debug, indention);

        case N_LESS:
            LOG_PRINT("interpret: N_LESS");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) < interpret(node->middle, debug, indention);

        case N_LESS_EQUAL:
            LOG_PRINT("interpret: N_LESS_EQUAL");
           // LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) <= interpret(node->middle, debug, indention);

        case N_BIGGER:
            LOG_PRINT("interpret: N_BIGGER");
           // LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) > interpret(node->middle, debug, indention);

        case N_BIGGER_EQUAL:
            LOG_PRINT("interpret: N_BIGGER_EQUAL");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) >= interpret(node->middle, debug, indention);

        case N_ADDITION:
            LOG_PRINT("interpret: N_ADDITION");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) + interpret(node->middle, debug, indention);

        case N_SUBTRACTION:
            LOG_PRINT("interpret: N_SUBTRACTION");
           // LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) - interpret(node->middle, debug, indention);

        case N_MULTIPLY:
            LOG_PRINT("interpret: N_MULTIPLY");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) * interpret(node->middle, debug, indention);

        case N_DIVIDE:
            LOG_PRINT("interpret: N_DIVIDE");
           // LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) / interpret(node->middle, debug, indention);

        case N_MODULO:
            LOG_PRINT("interpret: N_MODULO");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) % interpret(node->middle, debug, indention);

        case N_BINARY_OR:
            LOG_PRINT("interpret: N_BINARY_OR");
           // LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) | interpret(node->middle, debug, indention);

        case N_BINARY_AND:
            LOG_PRINT("interpret: N_BINARY_AND");
            //LOG_PRINT("%d", interpret(node->left, debug, indention));
            //LOG_PRINT("%d", interpret(node->middle, debug, indention));
            return interpret(node->left, debug, indention) & interpret(node->middle, debug, indention);

        case N_ASSIGNMENT:
            LOG_PRINT("interpret: N_ASSIGNMENT");
            scope->symbols[node->value] = interpret(node->left, debug, indention);
            return 0;

        case N_NOT:
            LOG_PRINT("interpret: N_NOT");
            return ! interpret(node->left, debug, indention);

        case N_MINUS:
            LOG_PRINT("interpret: N_MINUS");
            return -1 * interpret(node->left, debug, indention);

        case N_PRINT:
            LOG_PRINT("interpret: N_PRINT");
           // LOG_PRINT("PRINT: %d", interpret(node->left, debug, indention));
            printf("%d\n", interpret(node->left, debug, indention));
            return 0;

        case N_RETURN:
            LOG_PRINT("interpret: N_RETURN");
            if (node->left == NULL) {
                scope->return_value = 0;
            } else {
                scope->return_value = interpret(node->left, debug, indention);
            }
            return 0;

        case N_LOOP_BLOCK_FOR:
            LOG_PRINT("interpret: N_LOOP_BLOCK_FOR");
            times = interpret(node->middle, debug, indention);
            for (i=0; i<times; i+=1) {
                interpret(node->left, debug, indention);
            }
            return 0;

        case N_LOOP_FOR_BLOCK:
            LOG_PRINT("interpret: N_LOOP_FOR_BLOCK");
            times = interpret(node->left, debug, indention);
            for (i=0; i<times; i+=1) {
                interpret(node->middle, debug, indention);
            }
            return 0;

        case N_SUB:
            LOG_PRINT("interpret: N_SUB");
            sub = malloc(sizeof(Sub));
            sub->stmt = node->middle;
            sub->arguments = node->left;
            subs[node->value] = sub;
            return 0;

        case N_CALL:
            LOG_PRINT("interpret: N_CALL");
            return call_sub(subs[node->value], node->left, debug, indention);

        case N_END_OF_PROGRAM:
            LOG_PRINT("interpret: N_END_OF_PROGRAM");
	    //print_mem(subs, 1000);
            return 0;

        default:
            LOG_PRINT("Unknown node type ");
            printf("Unknown node type!\n");
            return EXIT_FAILURE;
        }
    }
    return 0;
}

/*void print_mem(void const *vp, size_t n)
{
    unsigned char const *p = vp;
    for (size_t i=0; i<n; i++)
        printf("%02x\n", p[i]);
    putchar('\n');
};*/


/**
 * Prints debug statements for a node
 */
void debug_node(Node* node, int indention) {
    //LOG_PRINT("debug_node()");
    char *indentionSpaces = (char*)malloc(sizeof(char)*indention + 1);
    int i;
    for (i=0; i<indention; i++) {
        indentionSpaces[i] = ' ';
    }
    indentionSpaces[indention] = '\0';

    int type = -1;
    int value = -1;
    char* msg = "%sNode with type %s\n";
    if (node != NULL) {
        type = node->type;
        if (type == N_VARIABLE) {
            value = node->value + 'a';
            msg = "%sNode with type %s and value %c\n";
        } else {
            value = node->value;
        }

        /*if (type == N_VARIABLE || type == N_ASSIGNMENT || type == N_INT) {*/
        if (type == N_VARIABLE || type == N_ASSIGNMENT || type == N_INT || type == N_STRING) {
	    //sprintf(logmsg, "%sNode with type %s and value %c\n");
            //LOG_PRINT("DEBUG: %s", logmsg);
            printf(msg, indentionSpaces,
                node_type_to_description(type), value);
        } else {
	    //sprintf(logmsg, "%sNode with type %s and value %c\n");
            //LOG_PRINT("DEBUG: %s", logmsg);
            printf(msg, indentionSpaces, node_type_to_description(type));
        }
    }
}
