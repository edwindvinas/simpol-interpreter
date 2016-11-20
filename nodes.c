#include <stdlib.h>

#include "nodes.h"

#include "log.h"

Node* create_node(NodeType type, Node* left, Node* middle, Node* right, int value, char *strValue) {
    Node* node = malloc(sizeof(Node));
    node->type = type;
    node->left = left;
    node->middle = middle;
    node->right = right;
    node->value = value;
    //LOG_PRINT("NODE_TYPE: %d", value);
    return node;
}

char* node_type_to_description(NodeType type) {
    //LOG_PRINT("node_type_to_description");
    switch (type) {
    case N_VARIABLES:
        LOG_PRINT("FOUND: variables");
	return "variables";

    case N_CODES:
        LOG_PRINT("FOUND: codes");
    	return "codes";

    case N_STRING:
        LOG_PRINT("FOUND: string");
   	return "string";

    case N_BOOL:
        LOG_PRINT("FOUND: bool");
   	return "string";

    case N_IN:
        LOG_PRINT("FOUND: in");
   	return "assignment";

    case N_ASK:
        LOG_PRINT("FOUND: ask");
   	return "print";

    case N_INTEGER:
        LOG_PRINT("FOUND: integer");
	return "integer";

    case N_EMPTY:
        LOG_PRINT("FOUND: empty");
        return "empty";

    case N_ASSIGNMENT:
        LOG_PRINT("FOUND: assignment");
        return "assignment";

    case N_INT:
        LOG_PRINT("FOUND: int");
        return "int";

    case N_VARIABLE:
        LOG_PRINT("FOUND: variable");
        return "variable";

    case N_ADDITION:
        LOG_PRINT("FOUND: addition");
        return "addition";

    case N_SUBTRACTION:
        LOG_PRINT("FOUND: subtraction");
        return "subtraction";

    case N_MULTIPLY:
        LOG_PRINT("FOUND: multiply");
        return "multiply";

    case N_DIVIDE:
        LOG_PRINT("FOUND: divide");
        return "divide";

    case N_MODULO:
        LOG_PRINT("FOUND: modulo");
        return "modulo";

    case N_LOOP_BLOCK_FOR:
        LOG_PRINT("FOUND: block for");
        return "loop block for";

    case N_LOOP_FOR_BLOCK:
        LOG_PRINT("FOUND: for block");
        return "loop for block";

    case N_IF:
        LOG_PRINT("FOUND: if");
        return "if";

    case N_IF_ELSE:
        LOG_PRINT("FOUND: if else");
        return "if else";

    case N_SUB:
        LOG_PRINT("FOUND: sub");
        return "sub";

    case N_CALL:
        LOG_PRINT("FOUND: call");
        return "call";

    case N_PRINT:
        LOG_PRINT("FOUND: print");
        return "print";

    case N_STMT:
        LOG_PRINT("FOUND: stmt");
        return "stmt";

    case N_EQUAL:
        LOG_PRINT("FOUND: equal");
        return "equal";

    case N_NOT:
        LOG_PRINT("FOUND: not");
        return "not";

    case N_MINUS:
        LOG_PRINT("FOUND: minus");
        return "minus";

    case N_RETURN:
        LOG_PRINT("FOUND: return");
        return "return";

    case N_ARGUMENT:
        LOG_PRINT("FOUND: argument");
        return "argument";

    case N_BINARY_OR:
        LOG_PRINT("FOUND: or");
        return "binary or";

    case N_BINARY_AND:
        LOG_PRINT("FOUND: and");
        return "binary and";

    case N_LESS:
        LOG_PRINT("FOUND: less");
        return "less";

    case N_LESS_EQUAL:
        LOG_PRINT("FOUND: equal");
        return "less equal";

    case N_BIGGER:
        LOG_PRINT("FOUND: greater");
        return "greater";

    case N_BIGGER_EQUAL:
        LOG_PRINT("FOUND: equal");
        return "greater equal";

    case N_END_OF_PROGRAM:
        LOG_PRINT("FOUND: end of program");
        return "end of program";

    case N_END_OF_ARG_LIST:
        LOG_PRINT("FOUND: end of argument list");
        return "end of argument list";

    default:
        LOG_PRINT("FOUND: unknown");
        return "unknown";
    }

}
