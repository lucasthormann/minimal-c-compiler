#include "tokendef.h"
#include <stdio.h>
#include <stdlib.h>

extern char* yytext;
extern int yylineno;
extern int yycol;
extern int blocklineno;

void printToken(int token){
  int val;
  int var = 4340;

  switch(token){
    case ID:
      printf("<ID, %s> : (%d:%d)\n", yytext, yylineno, yycol);
      break;
    case INTCONST:
      printf("<INTEGER, %s> : (%d:%d)\n", yytext, yylineno, yycol);
      break;
    case CHARCONST:
      printf("<CHAR, %s> : (%d:%d)\n", yytext, yylineno, yycol);
      break;
    case STRCONST:
      yylineno += blocklineno;
      break;
    case KWD_IF:
      printf("<IF, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_ELSE:
      printf("<ELSE, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_WHILE:
      printf("<WHILE, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_INT:
      printf("<INT, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_FLOAT:
      printf("<FLOAT, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_STRING:
      printf("<STRING, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_CHAR:
      printf("<CHAR, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_RETURN:
      printf("<RETURN, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case KWD_VOID:
      printf("<VOID, KEYWORD> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_ADD:
      printf("<OPERATION, +> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_SUB:
      printf("<OPERATION, -> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_MUL:
      printf("<OPERATION, *> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_DIV:
      printf("<OPERATION, /> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_LT:
      printf("<OPERATION, <> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_GT:
      printf("<OPERATION, >> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_GTE:
      printf("<OPERATION, >=> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_LTE:
      printf("<OPERATION <=> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_EQ:
      printf("<OPERATION, ==> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_NEQ:
      printf("<OPERATION, !=> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_ASGN:
      printf("<OPERATION, => : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_INC:
      printf("<OPERATION, ++> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_DEC:
      printf("<OPERATION, --> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_AND:
      printf("<OPERATION, &&> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_OR:
      printf("<OPERATION, ||> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_NOT:
      printf("<OPERATION, !> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_MOD:
      printf("<OPERATION, %%> : (%d:%d)\n", yylineno, yycol);
      break;
    case OPER_AT:
      printf("<OPERATION, @> : (%d:%d)\n", yylineno, yycol);
      break;
    case LSQ_BRKT:
      printf("<PUNCTUATION, [> : (%d:%d)\n", yylineno, yycol);
      break;
    case RSQ_BRKT:
      printf("<PUNCTUATION ]> : (%d:%d)\n", yylineno, yycol);
      break;
    case LCRLY_BRKT:
      printf("<PUNCTUATION {> : (%d:%d)\n", yylineno, yycol);
      break;
    case RCRLY_BRKT:
      printf("<PUNCTUATION, }> : (%d:%d)\n", yylineno, yycol);
      break;
    case LPAREN:
      printf("<PUNCTUATION, (> : (%d:%d)\n", yylineno, yycol);
      break;
    case RPAREN:
      printf("<PUNCTUATION, )> : (%d:%d)\n", yylineno, yycol);
      break;
    case COMMA:
      printf("<PUNCTUATION, ,> : (%d:%d)\n", yylineno, yycol);
      break;
    case SEMICLN:
      printf("<PUNCTUATION, ;> : (%d:%d)\n", yylineno, yycol);
      break;
    case ILLEGAL_TOK:
      printf("<ILLEGAL_TOK> : (%d:%d)\n", yylineno, yycol);
      break;
    case UNTERM_COMMENT:
      printf("<UNTERMINATED COMMENT> : (%d:%d)\n", yylineno, yycol);
      break;
    case UNTERM_STR:
      printf("<ERROR, UNTERM_STR> : (%d:%d)\n", yylineno, yycol);
      break;
    case MULTI_LINE_STR:
      printf("<ERROR, MULTIPLE_LINE_STRING> : (%d:%d)\n", yylineno, yycol);
      yylineno += blocklineno;
      break;
    case ILLEGAL_STR:
      yylineno += blocklineno;
      break;
    case LEADING_ZERO:
      printf("<LEADING ZERO> : (%d:%d)\n", yylineno, yycol);
      break;
    case NEGATIVE_NUM:
      printf("<NEGATIVE NUM> : (%d:%d)\n", yylineno, yycol);
      break;
    case ILLEGAL_ID:
      printf("<ILLEGAL ID>\n");
      break;
    case ERROR:
      printf("<ERROR> : (%d:%d)\n", yylineno, yycol);
      break;
    default:
      printf("STOP RIGHT THERE CRIMINAL SCUM! NOBODY BREAKS THE LAW ON MY WATCH! (%d:%d)\n", yylineno, yycol);
  }
}

int main() {
  int ret = yylex();
  while(ret){
    printToken(ret);
    ret = yylex();
  }
  return 0;
}
