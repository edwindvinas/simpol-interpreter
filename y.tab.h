/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_VAR = 258,
    T_BEGIN = 259,
    T_END = 260,
    T_LOOP = 261,
    T_FOR = 262,
    T_SUB = 263,
    T_IF = 264,
    T_THEN = 265,
    T_ELSE = 266,
    T_PRINT = 267,
    T_RETURN = 268,
    T_STRING = 269,
    T_BOOL = 270,
    T_VARIABLES = 271,
    T_CODES = 272,
    T_PUT = 273,
    T_ASK = 274,
    T_PRT = 275,
    T_IN = 276,
    T_FALSE = 277,
    T_TRUE = 278,
    T_BIGGER = 279,
    T_LESS = 280,
    T_LESS_EQUAL = 281,
    T_BIGGER_EQUAL = 282,
    T_ASSIGN = 283,
    T_SEMICOLON = 284,
    T_EQUAL = 285,
    T_PLUS = 286,
    T_ADD = 287,
    T_SUBT = 288,
    T_MUL = 289,
    T_DIV = 290,
    T_MOD = 291,
    T_MINUS = 292,
    T_DIVIDE = 293,
    T_MULTIPLY = 294,
    T_MODULO = 295,
    T_NOT = 296,
    T_COMMA = 297,
    T_BINARY_OR = 298,
    T_BINARY_AND = 299,
    T_OPEN_BRACKET = 300,
    T_CLOSE_BRACKET = 301,
    T_UNARY_MINUS = 302,
    T_OPEN_CURLY_BRACKET = 303,
    T_CLOSE_CURLY_BRACKET = 304,
    T_DOLLAR = 305,
    T_IDENTIFIER = 306,
    T_INTEGER = 307,
    T_STRING_LITERAL = 308
  };
#endif
/* Tokens.  */
#define T_VAR 258
#define T_BEGIN 259
#define T_END 260
#define T_LOOP 261
#define T_FOR 262
#define T_SUB 263
#define T_IF 264
#define T_THEN 265
#define T_ELSE 266
#define T_PRINT 267
#define T_RETURN 268
#define T_STRING 269
#define T_BOOL 270
#define T_VARIABLES 271
#define T_CODES 272
#define T_PUT 273
#define T_ASK 274
#define T_PRT 275
#define T_IN 276
#define T_FALSE 277
#define T_TRUE 278
#define T_BIGGER 279
#define T_LESS 280
#define T_LESS_EQUAL 281
#define T_BIGGER_EQUAL 282
#define T_ASSIGN 283
#define T_SEMICOLON 284
#define T_EQUAL 285
#define T_PLUS 286
#define T_ADD 287
#define T_SUBT 288
#define T_MUL 289
#define T_DIV 290
#define T_MOD 291
#define T_MINUS 292
#define T_DIVIDE 293
#define T_MULTIPLY 294
#define T_MODULO 295
#define T_NOT 296
#define T_COMMA 297
#define T_BINARY_OR 298
#define T_BINARY_AND 299
#define T_OPEN_BRACKET 300
#define T_CLOSE_BRACKET 301
#define T_UNARY_MINUS 302
#define T_OPEN_CURLY_BRACKET 303
#define T_CLOSE_CURLY_BRACKET 304
#define T_DOLLAR 305
#define T_IDENTIFIER 306
#define T_INTEGER 307
#define T_STRING_LITERAL 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 27 "parser.y" /* yacc.c:1909  */

    int integer;
    char* strval;
    Node* node;

#line 166 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
