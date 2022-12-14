/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_OBJ_Y_TAB_H_INCLUDED
# define YY_YY_OBJ_Y_TAB_H_INCLUDED
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
    IFTOKEN = 258,
    ELSETOKEN = 259,
    LPAREN = 260,
    RPAREN = 261,
    SEMICLN = 262,
    COMMA = 263,
    KWD_INT = 264,
    KWD_IF = 265,
    KWD_ELSE = 266,
    KWD_WHILE = 267,
    KWD_CHAR = 268,
    KWD_RETURN = 269,
    KWD_VOID = 270,
    OPER_ADD = 271,
    OPER_SUB = 272,
    OPER_MUL = 273,
    OPER_DIV = 274,
    OPER_LTE = 275,
    OPER_GTE = 276,
    OPER_LT = 277,
    OPER_GT = 278,
    OPER_EQ = 279,
    OPER_NEQ = 280,
    OPER_ASGN = 281,
    LSQ_BRKT = 282,
    RSQ_BRKT = 283,
    LCRLY_BRKT = 284,
    RCRLY_BRKT = 285,
    ID = 286,
    INTCONST = 287,
    CHARCONST = 288,
    STRCONST = 289,
    ERROR = 290,
    ILLEGAL_TOKEN = 291
  };
#endif
/* Tokens.  */
#define IFTOKEN 258
#define ELSETOKEN 259
#define LPAREN 260
#define RPAREN 261
#define SEMICLN 262
#define COMMA 263
#define KWD_INT 264
#define KWD_IF 265
#define KWD_ELSE 266
#define KWD_WHILE 267
#define KWD_CHAR 268
#define KWD_RETURN 269
#define KWD_VOID 270
#define OPER_ADD 271
#define OPER_SUB 272
#define OPER_MUL 273
#define OPER_DIV 274
#define OPER_LTE 275
#define OPER_GTE 276
#define OPER_LT 277
#define OPER_GT 278
#define OPER_EQ 279
#define OPER_NEQ 280
#define OPER_ASGN 281
#define LSQ_BRKT 282
#define RSQ_BRKT 283
#define LCRLY_BRKT 284
#define RCRLY_BRKT 285
#define ID 286
#define INTCONST 287
#define CHARCONST 288
#define STRCONST 289
#define ERROR 290
#define ILLEGAL_TOKEN 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "src/parser.y"

    int value;
    struct treenode *node;
    char *strval;

#line 135 "obj/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OBJ_Y_TAB_H_INCLUDED  */
