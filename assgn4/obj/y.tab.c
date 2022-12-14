#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "src/parser.y"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../src/tree.h"
#include"../src/strtab.h"

extern int yylineno;
/* nodeTypes refer to different types of internal and external nodes that can be part of the abstract syntax tree.*/
/*
enum nodeTypes {PROGRAM=0, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME, VOID};

*/
enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

/* NOTE: mC has two kinds of scopes for variables : local and global. Variables declared outside any
function are considered globals, whereas variables (and parameters) declared inside a function foo are local to foo. You should update the scope variable whenever you are inside a production that matches function definition (funDecl production). The rationale is that you are entering that function, so all variables, arrays, and other functions should be within this scope. You should pass this variable whenever you are calling the ST_insert or ST_lookup functions. This variable should be updated to scope = "" to indicate global scope whenever funDecl finishes. Treat these hints as helpful directions only. You may implement all of the functions as you like and not adhere to my instructions. As long as the directory structure is correct and the file names are correct, we are okay with it. */
char* scope = "";
char *funcN = "";
char *varN = "";
#line 30 "src/parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
    int value;
    struct treenode *node;
    char *strval;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 59 "obj/y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define IFTOKEN 257
#define ELSETOKEN 258
#define LPAREN 259
#define RPAREN 260
#define SEMICLN 261
#define COMMA 262
#define KWD_INT 263
#define KWD_IF 264
#define KWD_ELSE 265
#define KWD_WHILE 266
#define KWD_CHAR 267
#define KWD_RETURN 268
#define KWD_VOID 269
#define OPER_ADD 270
#define OPER_SUB 271
#define OPER_MUL 272
#define OPER_DIV 273
#define OPER_LTE 274
#define OPER_GTE 275
#define OPER_LT 276
#define OPER_GT 277
#define OPER_EQ 278
#define OPER_NEQ 279
#define OPER_ASGN 280
#define LSQ_BRKT 281
#define RSQ_BRKT 282
#define LCRLY_BRKT 283
#define RCRLY_BRKT 284
#define ID 285
#define INTCONST 286
#define CHARCONST 287
#define STRCONST 288
#define ERROR 289
#define ILLEGAL_TOKEN 290
#define lhs 291
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
   28,    0,    1,    1,    2,    2,    3,    3,    4,    4,
    4,   29,    5,    5,    6,    7,    7,    8,    8,   30,
    9,   10,   10,   10,   11,   11,   11,   12,   12,   12,
   12,   12,   16,   17,   17,   18,   13,   13,   19,   19,
   14,   14,   15,   15,   25,   25,   25,   25,   25,   25,
   20,   20,   22,   22,   21,   21,   24,   24,   23,   23,
   23,   23,   23,   26,   26,   27,   27,
};
static const short yylen[] = {                            2,
    0,    2,    1,    2,    1,    1,    6,    3,    1,    1,
    1,    0,    6,    4,    2,    1,    3,    2,    4,    0,
    5,    0,    1,    2,    0,    1,    2,    1,    1,    1,
    1,    1,    5,    2,    3,    3,    4,    2,    5,    7,
    1,    4,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    3,    1,    1,    1,    3,    1,    1,    3,    1,
    1,    1,    1,    4,    3,    1,    3,
};
static const short yydefred[] = {                         1,
    0,    0,    9,   10,   11,    0,    3,    5,    0,    6,
    0,    4,    0,    0,    8,    0,   20,    0,   12,    0,
    0,   14,    0,    0,    0,    0,    0,    0,    0,   20,
   17,    7,   23,    0,    0,   19,   13,    0,    0,    0,
    0,    0,    0,    0,   62,   63,   24,    0,   26,   29,
    0,    0,   31,   32,   28,   30,    0,    0,   55,   61,
   60,    0,    0,    0,   34,    0,    0,    0,    0,   21,
   27,    0,   38,   49,   48,   47,   46,   45,   50,    0,
   53,   54,    0,   57,   58,    0,   59,    0,    0,   35,
   36,   65,    0,    0,    0,    0,    0,    0,   56,    0,
    0,   64,    0,   42,   37,    0,   33,    0,    0,   40,
};
static const short yydgoto[] = {                          1,
    6,    7,    8,    9,   10,   11,   19,   20,   22,   35,
   48,   49,   50,   61,   52,   53,   54,   55,   56,   57,
   58,   83,   59,   86,   80,   60,   94,    2,   25,   23,
};
static const short yysindex[] = {                         0,
    0, -183,    0,    0,    0, -183,    0,    0, -283,    0,
 -252,    0, -235,  -24,    0, -275,    0, -257,    0, -212,
 -210,    0, -189, -186, -164, -183, -158, -183, -185,    0,
    0,    0,    0, -184, -245,    0,    0, -235, -242, -152,
 -150, -204, -154, -256,    0,    0,    0, -208,    0,    0,
 -169,    4,    0,    0,    0,    0, -237, -205,    0,    0,
    0,  -91, -242, -242,    0,   10, -195, -144, -242,    0,
    0, -242,    0,    0,    0,    0,    0,    0,    0, -242,
    0,    0, -242,    0,    0, -242,    0,  -45,  -25,    0,
    0,    0, -114, -250, -266,   16, -237, -205,    0, -154,
 -154,    0, -242,    0,    0, -143,    0, -114, -154,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,  113,    0,    0,    0,    0,
    0,    0, -131,    0,    0,    0,    0,    0,    0, -130,
    0,    0,    0, -213,    0,    0,    0, -166,    0,    0,
    0,    0,    0,    0, -147,    0,    0,    0,    0,    0,
    0,    0, -147, -126,    0,    0,    0,    0,    0,    0,
  -15,    0,    0,    0,    0,    0,  -57, -103,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -199,    0,    0,    0,  -51,  -80,    0,    0,
    0,    0,    0,    0,    0, -160,    0, -175,    0,    0,
};
static const short yygindex[] = {                         0,
    0,  132,   24,    1,    0,    0,  114,    0,  109,    0,
  112,  -47,    0,  -35,  -33,    0,    0,    0,    0,  -32,
   83,    0,   84,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 295
static const short yytable[] = {                         51,
   71,   13,   68,   81,   82,   62,   14,   51,   66,  102,
   21,  103,   51,   39,   18,  104,   39,    3,   40,   71,
   41,    4,   42,    5,   69,   15,   18,   24,   34,   88,
   89,   51,   81,   82,   93,   34,   95,   43,   96,   44,
   45,   46,   44,   45,   46,   16,   18,   97,   18,   26,
   39,   33,  106,  107,   39,   40,   65,   41,   47,   42,
   66,  110,   66,   39,   51,   51,   84,   85,   40,  108,
   41,   27,   42,   51,   43,   70,   44,   45,   46,    3,
   44,   45,   46,    4,   67,    5,   67,   43,   91,   44,
   45,   46,   22,   28,   29,   30,   36,   22,   39,   22,
   38,   22,   32,   39,   39,   39,   63,   39,   64,   40,
   72,   41,    2,   42,   39,   92,   22,   22,   22,   22,
   22,  109,   39,   39,   39,   39,   39,   15,   43,   16,
   44,   45,   46,   41,   41,   41,   25,   12,   37,   31,
   44,   45,   46,   41,   41,   41,   41,   41,   41,   41,
   41,   41,   41,   41,   67,   41,   51,   51,   51,   74,
   75,   76,   77,   78,   79,   98,   51,   51,   87,   99,
   51,   51,   51,   51,   51,   51,    0,    0,   51,   52,
   52,   52,   74,   75,   76,   77,   78,   79,    0,   52,
   52,    0,    0,   52,   52,   52,   52,   52,   52,    0,
    0,   52,   43,   43,   43,    0,    0,    0,   44,   44,
   44,    0,    0,    0,  100,    0,   43,   43,   43,   43,
   43,   43,   44,   44,   44,   44,   44,   44,   74,   75,
   76,   77,   78,   79,  101,   17,    0,    0,    3,    0,
    0,    0,    4,    0,    5,   60,    0,    0,   74,   75,
   76,   77,   78,   79,   60,   60,   60,   60,   60,   60,
   60,   60,   60,   60,   73,    0,    0,    0,    0,    0,
   90,    0,    0,    0,    0,    0,  105,   74,   75,   76,
   77,   78,   79,   74,   75,   76,   77,   78,   79,   74,
   75,   76,   77,   78,   79,
};
static const short yycheck[] = {                         35,
   48,  285,  259,  270,  271,   39,  259,   43,   42,  260,
  286,  262,   48,  259,   14,  282,  259,  263,  264,   67,
  266,  267,  268,  269,  281,  261,   26,  285,   28,   63,
   64,   67,  270,  271,   68,   35,   69,  283,   72,  285,
  286,  287,  285,  286,  287,  281,  260,   80,  262,  262,
  259,   28,  100,  101,  259,  264,  261,  266,   35,  268,
  260,  109,  262,  259,  100,  101,  272,  273,  264,  103,
  266,  282,  268,  109,  283,  284,  285,  286,  287,  263,
  285,  286,  287,  267,  260,  269,  262,  283,  284,  285,
  286,  287,  259,  283,  281,  260,  282,  264,  259,  266,
  285,  268,  261,  264,  259,  266,  259,  268,  259,  264,
  280,  266,    0,  268,  259,  260,  283,  284,  285,  286,
  287,  265,  283,  284,  285,  286,  287,  259,  283,  260,
  285,  286,  287,  260,  261,  262,  284,    6,   30,   26,
  285,  286,  287,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,   43,  282,  260,  261,  262,  274,
  275,  276,  277,  278,  279,   83,  270,  271,  260,   86,
  274,  275,  276,  277,  278,  279,   -1,   -1,  282,  260,
  261,  262,  274,  275,  276,  277,  278,  279,   -1,  270,
  271,   -1,   -1,  274,  275,  276,  277,  278,  279,   -1,
   -1,  282,  260,  261,  262,   -1,   -1,   -1,  260,  261,
  262,   -1,   -1,   -1,  260,   -1,  274,  275,  276,  277,
  278,  279,  274,  275,  276,  277,  278,  279,  274,  275,
  276,  277,  278,  279,  260,  260,   -1,   -1,  263,   -1,
   -1,   -1,  267,   -1,  269,  261,   -1,   -1,  274,  275,
  276,  277,  278,  279,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  261,   -1,   -1,   -1,   -1,   -1,
  261,   -1,   -1,   -1,   -1,   -1,  261,  274,  275,  276,
  277,  278,  279,  274,  275,  276,  277,  278,  279,  274,
  275,  276,  277,  278,  279,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 291
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IFTOKEN","ELSETOKEN","LPAREN",
"RPAREN","SEMICLN","COMMA","KWD_INT","KWD_IF","KWD_ELSE","KWD_WHILE","KWD_CHAR",
"KWD_RETURN","KWD_VOID","OPER_ADD","OPER_SUB","OPER_MUL","OPER_DIV","OPER_LTE",
"OPER_GTE","OPER_LT","OPER_GT","OPER_EQ","OPER_NEQ","OPER_ASGN","LSQ_BRKT",
"RSQ_BRKT","LCRLY_BRKT","RCRLY_BRKT","ID","INTCONST","CHARCONST","STRCONST",
"ERROR","ILLEGAL_TOKEN","lhs",
};
static const char *yyrule[] = {
"$accept : program",
"$$1 :",
"program : $$1 declList",
"declList : decl",
"declList : declList decl",
"decl : vardecl",
"decl : funDecl",
"vardecl : typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN",
"vardecl : typeSpecifier ID SEMICLN",
"typeSpecifier : KWD_INT",
"typeSpecifier : KWD_CHAR",
"typeSpecifier : KWD_VOID",
"$$2 :",
"funDecl : fundPre LPAREN formalDeclList $$2 RPAREN funBody",
"funDecl : fundPre LPAREN RPAREN funBody",
"fundPre : typeSpecifier ID",
"formalDeclList : formalDecl",
"formalDeclList : formalDecl COMMA formalDeclList",
"formalDecl : typeSpecifier ID",
"formalDecl : typeSpecifier ID LSQ_BRKT RSQ_BRKT",
"$$3 :",
"funBody : $$3 LCRLY_BRKT localDeclList statementList RCRLY_BRKT",
"localDeclList :",
"localDeclList : vardecl",
"localDeclList : localDeclList vardecl",
"statementList :",
"statementList : statement",
"statementList : statementList statement",
"statement : compoundStmt",
"statement : assignStmt",
"statement : condStmt",
"statement : loopStmt",
"statement : returnStmt",
"loopStmt : KWD_WHILE LPAREN expression RPAREN statement",
"returnStmt : KWD_RETURN SEMICLN",
"returnStmt : KWD_RETURN expression SEMICLN",
"compoundStmt : LCRLY_BRKT statementList RCRLY_BRKT",
"assignStmt : var OPER_ASGN expression SEMICLN",
"assignStmt : expression SEMICLN",
"condStmt : KWD_IF LPAREN expression RPAREN statement",
"condStmt : KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement",
"var : ID",
"var : ID LSQ_BRKT addExpr RSQ_BRKT",
"expression : addExpr",
"expression : expression relop addExpr",
"relop : OPER_EQ",
"relop : OPER_GT",
"relop : OPER_LT",
"relop : OPER_GTE",
"relop : OPER_LTE",
"relop : OPER_NEQ",
"addExpr : term",
"addExpr : addExpr addop term",
"addop : OPER_ADD",
"addop : OPER_SUB",
"term : factor",
"term : term mulop factor",
"mulop : OPER_MUL",
"mulop : OPER_DIV",
"factor : LPAREN expression RPAREN",
"factor : var",
"factor : funcCallExpr",
"factor : INTCONST",
"factor : CHARCONST",
"funcCallExpr : ID LPAREN argList RPAREN",
"funcCallExpr : ID LPAREN RPAREN",
"argList : expression",
"argList : argList COMMA expression",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 725 "src/parser.y"

int yywarning(char * msg){
    printf("warning: line %d: %s\n", yylineno, msg);
    return 0;
}


int yyerror(char * msg){
    printf("error: line %d: %s\n", yylineno, msg);
    return 0;
}
#line 399 "obj/y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 83 "src/parser.y"
	{ scope = "global"; new_scope(scope);  }
break;
case 2:
#line 84 "src/parser.y"
	{
                    tree* progNode = maketree(PROGRAM);
                    addChild(progNode, yystack.l_mark[0].node);
                    ast = progNode;
                 }
break;
case 3:
#line 92 "src/parser.y"
	{
                    yyval.node = maketree(DECLLIST);
                    addChild(yyval.node, yystack.l_mark[0].node);
                    /*$$ = $1;*/
                 }
break;
case 4:
#line 98 "src/parser.y"
	{
                    /*
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                    */
                    yyval.node = yystack.l_mark[-1].node;
                    addChild(yyval.node, yystack.l_mark[0].node);
                 }
break;
case 5:
#line 111 "src/parser.y"
	{
                /*
                  tree* decl = maketree(DECL);
                  addChild(decl, $1);
                */
                  if(yystack.l_mark[0].node->sym_type == SCALAR){
                    char *id = yystack.l_mark[0].node->children[1]->nodeName;
                    int type = yystack.l_mark[0].node->children[0]->val;
                    int sym = SCALAR;
                    int check = ST_insert(id, scope, type, sym, 0);
                    if(check != -1){
                      yyerror("multiple declaration of symbol");
                    }
                  }else{
                    int type = yystack.l_mark[0].node->children[0]->val;
                    char *id = yystack.l_mark[0].node->children[1]->nodeName;
                    int sym = ARRAY;
                    int sz = yystack.l_mark[0].node->children[2]->val;
                    int check = ST_insert(id, scope, type, sym, sz);
                    if(check != -1){
                      yyerror("multiple declaration of symbol");
                    }
                  }
                  yyval.node = yystack.l_mark[0].node;
                  
                  /*$$ = $1;*/
                }
break;
case 6:
#line 139 "src/parser.y"
	{
                  /*
                  tree *decl = maketree(DECL);
                  addChild(decl, $1);
                  $$ = decl;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 7:
#line 150 "src/parser.y"
	{
                  tree *vardeclNode = maketree(VARDECL);
                  addChild(vardeclNode, yystack.l_mark[-5].node);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER, yystack.l_mark[-4].strval));
                  addChild(vardeclNode, maketreeWithVal(INTEGER, yystack.l_mark[-2].value));
                  vardeclNode->sym_type = ARRAY;
                  yyval.node = vardeclNode;
		  if(yystack.l_mark[-2].value < 1){
		    yyerror("Array variable declared with illegal size");
		  }
                }
break;
case 8:
#line 162 "src/parser.y"
	{
                  tree *vardeclNode = maketree(VARDECL);
                  vardeclNode->sym_type = SCALAR;
                  addChild(vardeclNode, yystack.l_mark[-2].node);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER,yystack.l_mark[-1].strval));
                  yyval.node = vardeclNode;
                }
break;
case 9:
#line 172 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(TYPESPEC, INT_TYPE);
                }
break;
case 10:
#line 176 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(TYPESPEC, CHAR_TYPE);
                }
break;
case 11:
#line 180 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(TYPESPEC, VOID_TYPE);
                }
break;
case 12:
#line 185 "src/parser.y"
	{ connect_params(funcN, scope); }
break;
case 13:
#line 186 "src/parser.y"
	{
                  yyval.node = yystack.l_mark[-5].node;
                  char *name = getID(yyval.node);
                  /*up_scope();*/
                  addChild(yyval.node, yystack.l_mark[-3].node);
                  addChild(yyval.node, yystack.l_mark[0].node);
                  scope = "global";
                  up_scope();
                }
break;
case 14:
#line 196 "src/parser.y"
	{
                  yyval.node = yystack.l_mark[-3].node;
                  addChild(yyval.node, yystack.l_mark[0].node);
                  up_scope();
                }
break;
case 15:
#line 204 "src/parser.y"
	{
                  /*st_insert for current_scope*/
                  if(strcmp(yystack.l_mark[0].strval, "output") == 0){
                    yyerror("found output");
                  }
                  int pass = ST_insert(yystack.l_mark[0].strval, scope, yystack.l_mark[-1].node->val, FUNCTION, 0);
                  if(pass != -1){
                    yyerror("Symbol Declared Multiple Times");
                  }
                  tree *fundPre = maketree(FUNDECL);
                  funcN = yystack.l_mark[0].strval;
                  addChild(fundPre, yystack.l_mark[-1].node);
                  addChild(fundPre, maketreeWithID(IDENTIFIER, yystack.l_mark[0].strval));
                  scope = yystack.l_mark[0].strval;
                  yyval.node = fundPre;
                }
break;
case 16:
#line 223 "src/parser.y"
	{	
                  yyval.node = maketree(FORMALDECLLIST);
                  addChild(yyval.node, yystack.l_mark[0].node);
                }
break;
case 17:
#line 228 "src/parser.y"
	{
                  /*
                  tree* formalDeclListNode = maketree(FORMALDECLLIST);
                  addChild(formalDeclListNode, $1);
                  addChild(formalDeclListNode, $3);
                  $$ = formalDeclListNode;
                  */
                  yyval.node = yystack.l_mark[0].node;
                  addChild(yyval.node, yystack.l_mark[-2].node);
                  /*
                  $$ = $1;
                  addChild($$, $3);
                  */
                }
break;
case 18:
#line 245 "src/parser.y"
	{
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, yystack.l_mark[-1].node);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, yystack.l_mark[0].strval));
                  /*ST_insert($2, "local", $1->val, SCALAR, 0);*/
                  add_param(yystack.l_mark[-1].node->val, yystack.l_mark[-1].node->sym_type, yystack.l_mark[0].strval);
                  yyval.node = formalDeclNode;
                  /*new_scope();*/
                }
break;
case 19:
#line 255 "src/parser.y"
	{
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, yystack.l_mark[-3].node);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, yystack.l_mark[-2].strval));
                  add_param(yystack.l_mark[-3].node->val, ARRAY, yystack.l_mark[-2].strval);
                  /*ST_insert($2, "global", $1->val, ARRAY, 0);*/
                  yyval.node = formalDeclNode;
                  /*new_scope();*/
                }
break;
case 20:
#line 266 "src/parser.y"
	{ new_scope(scope); }
break;
case 21:
#line 267 "src/parser.y"
	{
                  tree *funBody = maketree(FUNBODY);
                  addChild(funBody, yystack.l_mark[-2].node);
                  addChild(funBody, yystack.l_mark[-1].node);
                  yyval.node = funBody;
                }
break;
case 22:
#line 276 "src/parser.y"
	{
                  yyval.node = NULL;
                }
break;
case 23:
#line 280 "src/parser.y"
	{
                  yyval.node = maketree(LOCALDECLLIST);
                  addChild(yyval.node, yystack.l_mark[0].node);
                }
break;
case 24:
#line 285 "src/parser.y"
	{
                  /*
                  tree *localDeclList = maketree(LOCALDECLLIST);
                  addChild(localDeclList, $1);
                  addChild(localDeclList, $2);
                  int checkDecl = ST_insert($1->children[1]->nodeName, scope, $1->children[0]->val, $1->sym_type, 0);
                  if(checkDecl != -1){
                    yyerror("Multiple Symbols Defined");
                  }
                  $$ = localDeclList;
                  */
                  yyval.node = yystack.l_mark[-1].node;
                  addChild(yyval.node, yystack.l_mark[0].node);
                  /*addChild($$, $2);*/
                  /*
                  $$ = $1;
                  //now we can start check for
                  addChild($$, $2);
                  */
                }
break;
case 25:
#line 308 "src/parser.y"
	{
                  yyval.node = NULL;
                }
break;
case 26:
#line 312 "src/parser.y"
	{
                  yyval.node = maketree(STATEMENTLIST);
                  addChild(yyval.node, yystack.l_mark[0].node);
                }
break;
case 27:
#line 317 "src/parser.y"
	{
                  yyval.node = yystack.l_mark[-1].node;
                  addChild(yyval.node, yystack.l_mark[0].node);
                  /*addChild($$, $2);*/
                  /*
                  $$ = $1;
                  addChild($$, $2);
                  */
                }
break;
case 28:
#line 329 "src/parser.y"
	{
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 29:
#line 338 "src/parser.y"
	{
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 30:
#line 347 "src/parser.y"
	{ 
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 31:
#line 356 "src/parser.y"
	{
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 32:
#line 365 "src/parser.y"
	{
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 33:
#line 376 "src/parser.y"
	{
                  tree *loopStmt = maketree(LOOPSTMT);
                  addChild(loopStmt, yystack.l_mark[-2].node);
                  addChild(loopStmt, yystack.l_mark[0].node);
                  yyval.node = loopStmt;
                }
break;
case 34:
#line 385 "src/parser.y"
	{
                  yyval.node = maketree(RETURNSTMT);
                }
break;
case 35:
#line 389 "src/parser.y"
	{
                  tree *returnStmt = maketree(RETURNSTMT);
                  addChild(returnStmt, yystack.l_mark[-1].node);
                  yyval.node = returnStmt;
                }
break;
case 36:
#line 397 "src/parser.y"
	{
                  tree *compoundStmt = maketree(COMPOUNDSTMT);
                  addChild(compoundStmt, yystack.l_mark[-1].node);
                  yyval.node = compoundStmt;
                  /*$$ = $2;*/
                }
break;
case 37:
#line 406 "src/parser.y"
	{
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, yystack.l_mark[-3].node);
                  addChild(assignStmt, yystack.l_mark[-1].node);
                  yyval.node = assignStmt;
                  if(yystack.l_mark[-1].node->match == MISSMATCH){
                    yyerror("type mismatch");
                  }
                  /*we're gonna want to create a new node for this*/
                  /*
                  $$ = $1;
                  addChild($$,$3);
                  */

                }
break;
case 38:
#line 422 "src/parser.y"
	{
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, yystack.l_mark[-1].node);
                  yyval.node = assignStmt;
                  if(yystack.l_mark[-1].node->match == MISSMATCH){
                    yyerror("type mismatch");
                  }
                  yyval.node = yystack.l_mark[-1].node;
                }
break;
case 39:
#line 434 "src/parser.y"
	{ 
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, yystack.l_mark[-2].node);
                  addChild(condStmt, yystack.l_mark[0].node);
                  yyval.node = condStmt;
                }
break;
case 40:
#line 441 "src/parser.y"
	{
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, yystack.l_mark[-4].node);
                  addChild(condStmt, yystack.l_mark[-2].node);
                  addChild(condStmt, yystack.l_mark[0].node);
                  yyval.node = condStmt;
                }
break;
case 41:
#line 452 "src/parser.y"
	{
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, yystack.l_mark[0].strval));
                  yyval.node = var;
                  /*
                  symEntry *check = ST_lookup($1);
                  int checkV = checkValAgainstParams($1, scope);
                  //we need to see if the param contains the function
                  if(check == NULL && checkV == -1){
                    yyerror("Undeclared Variable");
                  }
                  */
                  /*$$ = maketreeWithID(IDENTIFIER, $1);*/
                }
break;
case 42:
#line 467 "src/parser.y"
	{
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, yystack.l_mark[-3].strval));
                  addChild(var, yystack.l_mark[-1].node);
                  yyval.node = var;
                  /*
                  varN = $1;
                  symEntry *check = ST_lookup($1);
                  int checkV = checkValAgainstParams($1, scope);
                  if(check == NULL && checkV == -1){
                    yyerror("Undeclared Variable");
                  }
                  $$ = maketreeWithID(IDENTIFIER, $1);
                  addChild($$, $3);
                  */
                }
break;
case 43:
#line 486 "src/parser.y"
	{
                  /*tree *expression = maketree(EXPRESSION);*/
                  /*addChild(expression, $1);*/
                  yyval.node = yystack.l_mark[0].node;
                  /*$$ = $1;*/
                }
break;
case 44:
#line 493 "src/parser.y"
	{
                  /*
                  tree *expression = maketree(EXPRESSION);
                  addChild($2, $1);
                  addChild(expression, $2);
                  addChild($2, $3);
                  $$ = expression;
                  */
                  yyval.node = yystack.l_mark[-1].node;
                  addChild(yyval.node, yystack.l_mark[-2].node);
                  addChild(yyval.node, yystack.l_mark[0].node);
                }
break;
case 45:
#line 508 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, EQ);
                }
break;
case 46:
#line 512 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, GT);
                }
break;
case 47:
#line 516 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, LT);
                }
break;
case 48:
#line 520 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, GTE);
                }
break;
case 49:
#line 524 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, LTE);
                }
break;
case 50:
#line 528 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(RELOP, NEQ);
                }
break;
case 51:
#line 534 "src/parser.y"
	{
                  
                  /*
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  $$ = addExpr;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 52:
#line 544 "src/parser.y"
	{
                  /*
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  addChild(addExpr, $2);
                  addChild(addExpr, $3);
                  $$ = addExpr;
                  */
                  yyval.node = yystack.l_mark[-1].node;
                  addChild(yyval.node,yystack.l_mark[-2].node);
                  addChild(yyval.node,yystack.l_mark[0].node);
                  /*checkMatch($$);*/
                }
break;
case 53:
#line 560 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(ADDOP, ADD);
                }
break;
case 54:
#line 564 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(ADDOP, SUB);
                }
break;
case 55:
#line 570 "src/parser.y"
	{
                  /*
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  $$ = term;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 56:
#line 579 "src/parser.y"
	{
                  /*
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  addChild(term, $2);
                  addChild(term, $3);
                  $$ = term;
                  */
                  yyval.node = yystack.l_mark[-1].node;
                  addChild(yyval.node, yystack.l_mark[-2].node);
                  addChild(yyval.node, yystack.l_mark[0].node);
                  /*checkMatch($$);*/
                }
break;
case 57:
#line 595 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(MULOP, MUL);
                }
break;
case 58:
#line 599 "src/parser.y"
	{
                  yyval.node = maketreeWithVal(MULOP, DIV);
                }
break;
case 59:
#line 605 "src/parser.y"
	{
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $2);
                  $$ = factor;
                  */
                  yyval.node = yystack.l_mark[-1].node;
                }
break;
case 60:
#line 614 "src/parser.y"
	{
                  /*check against the type here we have func name.*/
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                  */
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 61:
#line 624 "src/parser.y"
	{
                /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                */
                  /*ST_lookup, we'll need to check the params, probably best to just check the children*/
                  /*we don't know how many arguments a function call can have.*/
                  /*at least if the children is greater than the number of arguments from symEntry then we just need to know the size of the params list*/
                  /*how do we check the list?, well if we pass in the tree node then we can simply check the children since they are not nested.*/
                  yyval.node = yystack.l_mark[0].node;
                }
break;
case 62:
#line 637 "src/parser.y"
	{
                  
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(INTEGER, $1));
                  $$ = factor;
                  */
                  yyval.node = maketreeWithVal(INTEGER, yystack.l_mark[0].value);
                }
break;
case 63:
#line 647 "src/parser.y"
	{
                  
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(CHAR, $1));
                  $$ = factor;
                  */
                  yyval.node = maketreeWithVal(CHAR, yystack.l_mark[0].value);
                }
break;
case 64:
#line 659 "src/parser.y"
	{
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, yystack.l_mark[-3].strval));
                  addChild(funcCallExpr, yystack.l_mark[-1].node);
                  symEntry *funcName = ST_lookup(yystack.l_mark[-3].strval);
                  if(strcmp("output", yystack.l_mark[-3].strval)){
                    if(funcName != NULL){
                      int sz = paramSize(funcName, yystack.l_mark[-3].strval);
                      if(yystack.l_mark[-1].node->numChildren < sz){
                        /*too many arguments*/
                        yyerror("too few arguments for function call");
                      }else if(yystack.l_mark[-1].node->numChildren > sz){
                        yyerror("Too many arguments");
                      }else{
                        /*start checking the children*/
                        for(int i = 0; i < yystack.l_mark[-1].node->numChildren; i++){
                          /*for each children check the param and value*/
                          /* check the value, and the symbal type*/
                          param *params = funcName->params;
                          char *id = yystack.l_mark[-1].node->children[i]->nodeName;
                          int check = checkParams(params, id, i);
                          if(check == MISS){
                            yyerror("Arguments Mismatched");
                            break;
                          }
                        }
                      }
                    }else{
                      yyerror("Undeclared Function");
                    }
                  }
                  yyval.node = funcCallExpr;
                }
break;
case 65:
#line 693 "src/parser.y"
	{
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, yystack.l_mark[-2].strval));
                  symEntry *funcName = ST_lookup(yystack.l_mark[-2].strval);
                  if(funcName == NULL){
                    /*throw an error*/
                    yyerror("Undeclared Function");
                  }
                  yyval.node = funcCallExpr;
                }
break;
case 66:
#line 706 "src/parser.y"
	{
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, yystack.l_mark[0].node);
                  yyval.node = argList;
                  /*$$ = $1;*/
                }
break;
case 67:
#line 713 "src/parser.y"
	{
                /*
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, $1);
                  addChild(argList, $3);
                  $$ = argList;
                  */
                  yyval.node = yystack.l_mark[-2].node;
                  addChild(yyval.node, yystack.l_mark[0].node);
                }
break;
#line 1330 "obj/y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
