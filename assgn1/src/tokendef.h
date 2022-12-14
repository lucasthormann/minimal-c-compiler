#define ID 251
// Constants
#define INTCONST 252
#define CHARCONST 253
#define STRCONST 254
// Keywords
#define KWD_IF 255
#define KWD_ELSE 256
#define KWD_WHILE 257
#define KWD_INT 258
#define KWD_FLOAT 259
#define KWD_STRING 260
#define KWD_CHAR 261
#define KWD_RETURN 262
#define KWD_VOID 263
// OPERANDS
#define OPER_ADD 264
#define OPER_SUB 265
#define OPER_MUL 266
#define OPER_DIV 267
#define OPER_LT 268
#define OPER_GT 269
#define OPER_GTE 270
#define OPER_LTE 271
#define OPER_EQ 272
#define OPER_NEQ 273
#define OPER_ASGN 274
#define OPER_AT 275
#define OPER_INC 276
#define OPER_DEC 277
#define OPER_AND 278
#define OPER_OR 279
#define OPER_NOT 280
#define OPER_MOD 281
// Control Flow
#define LSQ_BRKT 282
#define RSQ_BRKT 283
#define LCRLY_BRKT 284
#define RCRLY_BRKT 285
#define LPAREN 286
#define RPAREN 287
#define COMMA 288
#define SEMICLN 290
// Errors
#define ILLEGAL_TOK 301
#define UNTERM_COMMENT 302
#define UNTERM_STR 303
#define ILLEGAL_STR 304
#define MULTI_LINE_STR 305
#define LEADING_ZERO 306
#define NEGATIVE_NUM 307
#define ILLEGAL_ID 308
#define ERROR 309