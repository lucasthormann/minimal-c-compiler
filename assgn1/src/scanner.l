/* Defs */
%{
  #include "stdio.h"
  #include "tokendef.h"
  #include "string.h"
  int validStr(const char *text);
  void updateCol();
  void checkComment(const char *text);
  int yycol = 1;
  int scan_col = 1;
  int blocklineno = 0;
%}

digit [0-9]
number [1-9][0-9]*|0
negative_number -[1-9][0-9]*
leading_zero 0[0-9]+
letter [a-zA-Z]
identifier [a-zA-Z_][0-9a-zA-Z_]*
whitespace [ \t]
newline \n 
oper_div [/]
lsq_brkt [\[]
rsq_brkt [\]]
rcrly_brkt [\{]
lcrly_brkt [\}]
lparen [\(]
rparen [\)]
comma [\,]
semicln [\;]
not [!]
inc \+\+
dec \-\-
oper_or \|\|
oper_and \&\&
oper_asgn \=
oper_eq ==
oper_neq "!="
oper_lte "<="
oper_gte ">="
oper_lt "<"
oper_gt ">"
oper_add \+
oper_sub \-
oper_mul "\*"
oper_mod "\%"
oper_at "\@"
single_comment \/\/[^\n]*
multi_comment \/\*(\*[^\/]|\/\*|\/|[^\*\/])*\*\/
unterm_comment \/\*|\*\/
yylineno = 1;
%%
  /* rules */
{oper_add} { updateCol(); return OPER_ADD; }
{oper_sub} { updateCol(); return OPER_SUB; }
{oper_mul} { updateCol(); return OPER_MUL; }
{oper_div} { updateCol(); return OPER_DIV; }
{oper_lt} { updateCol(); return OPER_LT; }
{oper_gt} { updateCol(); return OPER_GT; }
{oper_gte} { updateCol(); return OPER_GTE; }
{oper_lte} { updateCol(); return OPER_LTE; }
{oper_eq} { updateCol(); return OPER_EQ; }
{oper_neq} { updateCol(); return OPER_NEQ; }
{oper_asgn} { updateCol(); return OPER_ASGN; }
{oper_and} { updateCol(); return OPER_AND; }
{oper_or} { updateCol(); return OPER_OR; }
{oper_mod} { updateCol(); return OPER_MOD; }
{oper_at} { updateCol(); return OPER_AT; }
{not} { updateCol(); return OPER_NOT; }
{inc} { updateCol(); return OPER_INC; }
{dec} { updateCol(); return OPER_DEC; }
{lsq_brkt} { updateCol(); return LSQ_BRKT; }
{rsq_brkt} { updateCol(); return RSQ_BRKT; }
{lcrly_brkt} { updateCol(); return LCRLY_BRKT; }
{rcrly_brkt} { updateCol(); return RCRLY_BRKT; }
{lparen} { updateCol(); return LPAREN; }
{rparen} { updateCol(); return RPAREN; }
{comma} { updateCol(); return COMMA; }
{semicln} { updateCol(); return SEMICLN; } 
{single_comment} { updateCol(); }
{multi_comment} { checkComment(yytext), updateCol(); }
{unterm_comment} { updateCol(); }
int { updateCol(); return KWD_INT; }
float { updateCol(); return KWD_FLOAT; }
if { updateCol(); return KWD_IF; }
else { updateCol(); return KWD_ELSE; }
void { updateCol(); return KWD_VOID; }
char { updateCol(); return KWD_CHAR; }
string { updateCol(); return KWD_STRING; }
while { updateCol(); return KWD_WHILE; }
return { updateCol(); return KWD_RETURN; }
{number} { updateCol(); return INTCONST; }
{leading_zero} { updateCol(); return LEADING_ZERO; }
{negative_number} { updateCol(); return NEGATIVE_NUM; }
{identifier} { updateCol(); return ID; }
[\"](\\.|[^\"\\])*[\"] { updateCol(); return validStr(yytext); }
\"(\\.|[^\n\"\\])* { updateCol(); return UNTERM_STR; }
{whitespace} { updateCol(); }
{newline} { scan_col=1; yycol=1; ++yylineno;}
. { return ERROR;}
%%

// user functions
int validStr(const char *text) {
  blocklineno = 0;
  int i = 0;
  int j = 0;
  int z = 0;
  int printindexflag = 0;
  int multilineflag = 0;
  int illstrflag = 0;
  size_t sz = strlen(text);
  char *buffptr;
  buffptr = (char *) malloc(sz*sizeof(char));
  for (i = 0; i < sz; i++) {
    if (text[i] == '\n'){
      blocklineno++;
      multilineflag = 1;
    }else if(text[i] == '"' && i == sz-1){
      buffptr[z] = '\0';
    }else if(text[i] == '"' && i == 0){
      continue;
    }else if (text[i] == '\\'){
      j = i + 1;
      
      switch (text[j]){
        case 'n':
          buffptr[z] = '\n';
          break;
        case 't':
          buffptr[z] = '\t';
          break;
        case '\\':
          buffptr[z] = '\\';
          break;
        case '"':
          buffptr[z] = '"';
          break;
        default:
          illstrflag = 1;
          if (!printindexflag){
            printf("<ERROR, Unrecognized escape character in String>: (%d:%d)\n",yylineno, yycol+j);
                  printindexflag=1;
          }
      }
      i = j;
      z++;
    }else {
      buffptr[z] = text[i];
      z++;
    }
  }
  if (multilineflag){
    return MULTI_LINE_STR;
  }
  else if (illstrflag){
    return ILLEGAL_STR;
  }
  printf("<STRING, %s> : (%d,%d)\n", buffptr, yylineno, yycol);
  free(buffptr);
  return STRCONST;
}

void updateCol(){
  yycol = scan_col;
  scan_col += yyleng;
}

void checkComment(const char *text){
  blocklineno = 0; 
  int sz = strlen(text);
  for (int i = 0; i < sz; i++){
    if (text[i]=='\n'){
        blocklineno++; 
      }
  }
 
}
