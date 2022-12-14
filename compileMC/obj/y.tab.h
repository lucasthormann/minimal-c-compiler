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
extern YYSTYPE yylval;
