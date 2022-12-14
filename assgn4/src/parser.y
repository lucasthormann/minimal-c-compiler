%{
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
%}

/* the union describes the fields available in the yylval variable */
%union
{
    int value;
    struct treenode *node;
    char *strval;
}

/*Add token declarations below. The type <value> indicates that the associated token will be of a value type such as integer, float etc., and <strval> indicates that the associated token will be of string type.*/
%token <value> IFTOKEN ELSETOKEN
%token <value> LPAREN RPAREN
%token <value> SEMICLN
%token <value> COMMA
%token <value> KWD_INT
%token <value> KWD_IF
%token <value> KWD_ELSE
%token <value> KWD_WHILE
%token <value> KWD_CHAR
%token <value> KWD_RETURN
%token <value> KWD_VOID
%token <value> OPER_ADD
%token <value> OPER_SUB
%token <value> OPER_MUL
%token <value> OPER_DIV
%token <value> OPER_LTE
%token <value> OPER_GTE
%token <value> OPER_LT
%token <value> OPER_GT
%token <value> OPER_EQ
%token <value> OPER_NEQ
%token <value> OPER_ASGN
%token <value> LSQ_BRKT
%token <value> RSQ_BRKT
%token <value> LCRLY_BRKT
%token <value> RCRLY_BRKT
%token <strval> ID
%token <value> INTCONST
%token <value> CHARCONST
%token <value> STRCONST
%token <value> ERROR
%token <value> ILLEGAL_TOKEN

/* TODO: Add the rest of the tokens below.*/


/* TODO: Declate non-terminal symbols as of type node. Provided below is one example. node is defined as 'struct treenode *node' in the above union data structure. This declaration indicates to parser that these non-terminal variables will be implemented using a 'treenode *' type data structure. Hence, the circles you draw when drawing a parse tree, the following lines are telling yacc that these will eventually become circles in an AST. This is one of the connections between the AST you draw by hand and how yacc implements code to concretize that. We provide with two examples: program and declList from the grammar. Make sure to add the rest.  */

%type <node> program declList decl vardecl typeSpecifier funDecl fundPre formalDeclList formalDecl funBody localDeclList statementList statement assignStmt lhs var expression loopStmt returnStmt compoundStmt condStmt addExpr term addop factor mulop relop funcCallExpr argList

%start program

%%
/* TODO: Your grammar and semantic actions go here. We provide with two example productions and their associated code for adding non-terminals to the AST.*/

program         : { scope = "global"; new_scope(scope);  } declList 
                 {
                    tree* progNode = maketree(PROGRAM);
                    addChild(progNode, $2);
                    ast = progNode;
                 }
                ;

declList        : decl
                 {
                    $$ = maketree(DECLLIST);
                    addChild($$, $1);
                    //$$ = $1;
                 }
                | declList decl
                 {
                    /*
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                    */
                    $$ = $1;
                    addChild($$, $2);
                 }
                ;

decl            : vardecl
                {
                /*
                  tree* decl = maketree(DECL);
                  addChild(decl, $1);
                */
                  if($1->sym_type == SCALAR){
                    char *id = $1->children[1]->nodeName;
                    int type = $1->children[0]->val;
                    int sym = SCALAR;
                    int check = ST_insert(id, scope, type, sym, 0);
                    if(check != -1){
                      yyerror("multiple declaration of symbol");
                    }
                  }else{
                    int type = $1->children[0]->val;
                    char *id = $1->children[1]->nodeName;
                    int sym = ARRAY;
                    int sz = $1->children[2]->val;
                    int check = ST_insert(id, scope, type, sym, sz);
                    if(check != -1){
                      yyerror("multiple declaration of symbol");
                    }
                  }
                  $$ = $1;
                  
                  //$$ = $1;
                }
                | funDecl
                {
                  /*
                  tree *decl = maketree(DECL);
                  addChild(decl, $1);
                  $$ = decl;
                  */
                  $$ = $1;
                }
                ;

vardecl         : typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN 
                {
                  tree *vardeclNode = maketree(VARDECL);
                  addChild(vardeclNode, $1);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER, $2));
                  addChild(vardeclNode, maketreeWithVal(INTEGER, $4));
                  vardeclNode->sym_type = ARRAY;
                  $$ = vardeclNode;
		  if($4 < 1){
		    yyerror("Array variable declared with illegal size");
		  }
                }
                | typeSpecifier ID SEMICLN
                {
                  tree *vardeclNode = maketree(VARDECL);
                  vardeclNode->sym_type = SCALAR;
                  addChild(vardeclNode, $1);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER,$2));
                  $$ = vardeclNode;
                }
                ;

typeSpecifier   : KWD_INT
                {
                  $$ = maketreeWithVal(TYPESPEC, INT_TYPE);
                }
                | KWD_CHAR
                {
                  $$ = maketreeWithVal(TYPESPEC, CHAR_TYPE);
                }
                | KWD_VOID
                {
                  $$ = maketreeWithVal(TYPESPEC, VOID_TYPE);
                }
                ;

funDecl		      : fundPre LPAREN formalDeclList { connect_params(funcN, scope); } RPAREN funBody
                {
                  $$ = $1;
                  char *name = getID($$);
                  //up_scope();
                  addChild($$, $3);
                  addChild($$, $6);
                  scope = "global";
                  up_scope();
                }
                | fundPre LPAREN RPAREN funBody
                {
                  $$ = $1;
                  addChild($$, $4);
                  up_scope();
                }
                ;

fundPre         : typeSpecifier ID
                {
                  //st_insert for current_scope
                  if(strcmp($2, "output") == 0){
                    yyerror("found output");
                  }
                  int pass = ST_insert($2, scope, $1->val, FUNCTION, 0);
                  if(pass != -1){
                    yyerror("Symbol Declared Multiple Times");
                  }
                  tree *fundPre = maketree(FUNDECL);
                  funcN = $2;
                  addChild(fundPre, $1);
                  addChild(fundPre, maketreeWithID(IDENTIFIER, $2));
                  scope = $2;
                  $$ = fundPre;
                }
                ;

formalDeclList  : formalDecl
                {	
                  $$ = maketree(FORMALDECLLIST);
                  addChild($$, $1);
                }
                | formalDecl COMMA formalDeclList
                {
                  /*
                  tree* formalDeclListNode = maketree(FORMALDECLLIST);
                  addChild(formalDeclListNode, $1);
                  addChild(formalDeclListNode, $3);
                  $$ = formalDeclListNode;
                  */
                  $$ = $3;
                  addChild($$, $1);
                  /*
                  $$ = $1;
                  addChild($$, $3);
                  */
                }
                ;

formalDecl	    : typeSpecifier ID
                {
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, $1);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, $2));
                  //ST_insert($2, "local", $1->val, SCALAR, 0);
                  add_param($1->val, $1->sym_type, $2);
                  $$ = formalDeclNode;
                  //new_scope();
                }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                {
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, $1);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, $2));
                  add_param($1->val, ARRAY, $2);
                  //ST_insert($2, "global", $1->val, ARRAY, 0);
                  $$ = formalDeclNode;
                  //new_scope();
                }
                ;

funBody         : { new_scope(scope); } LCRLY_BRKT  localDeclList statementList RCRLY_BRKT 
                {
                  tree *funBody = maketree(FUNBODY);
                  addChild(funBody, $3);
                  addChild(funBody, $4);
                  $$ = funBody;
                }
                ;

localDeclList   :
                {
                  $$ = NULL;
                }
                | vardecl
                {
                  $$ = maketree(LOCALDECLLIST);
                  addChild($$, $1);
                }
                | localDeclList vardecl
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
                  $$ = $1;
                  addChild($$, $2);
                  //addChild($$, $2);
                  /*
                  $$ = $1;
                  //now we can start check for
                  addChild($$, $2);
                  */
                }
                ;

statementList   :
                {
                  $$ = NULL;
                }
                | statement
                {
                  $$ = maketree(STATEMENTLIST);
                  addChild($$, $1);
                }
                | statementList statement
                {
                  $$ = $1;
                  addChild($$, $2);
                  //addChild($$, $2);
                  /*
                  $$ = $1;
                  addChild($$, $2);
                  */
                }
                ;

statement       : compoundStmt
                {
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  $$ = $1;
                }
                | assignStmt
                {
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  $$ = $1;
                }
                | condStmt
                { 
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  $$ = $1;
                }
                | loopStmt
                {
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  $$ = $1;
                }
                | returnStmt
                {
                  /*
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                  */
                  $$ = $1;
                }
                ;

loopStmt        : KWD_WHILE LPAREN expression RPAREN statement
                {
                  tree *loopStmt = maketree(LOOPSTMT);
                  addChild(loopStmt, $3);
                  addChild(loopStmt, $5);
                  $$ = loopStmt;
                }
                ;

returnStmt      : KWD_RETURN SEMICLN
                {
                  $$ = maketree(RETURNSTMT);
                }
                | KWD_RETURN expression SEMICLN
                {
                  tree *returnStmt = maketree(RETURNSTMT);
                  addChild(returnStmt, $2);
                  $$ = returnStmt;
                }
                ;

compoundStmt    : LCRLY_BRKT statementList RCRLY_BRKT 
                {
                  tree *compoundStmt = maketree(COMPOUNDSTMT);
                  addChild(compoundStmt, $2);
                  $$ = compoundStmt;
                  //$$ = $2;
                }
                ;

assignStmt      : var OPER_ASGN expression SEMICLN
                {
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, $1);
                  addChild(assignStmt, $3);
                  $$ = assignStmt;
                  if($3->match == MISSMATCH){
                    yyerror("type mismatch");
                  }
                  //we're gonna want to create a new node for this
                  /*
                  $$ = $1;
                  addChild($$,$3);
                  */

                }
                | expression SEMICLN
                {
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, $1);
                  $$ = assignStmt;
                  if($1->match == MISSMATCH){
                    yyerror("type mismatch");
                  }
                  $$ = $1;
                }
                ;

condStmt        : KWD_IF LPAREN expression RPAREN statement
                { 
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, $3);
                  addChild(condStmt, $5);
                  $$ = condStmt;
                }
                | KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement
                {
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, $3);
                  addChild(condStmt, $5);
                  addChild(condStmt, $7);
                  $$ = condStmt;
                }
                ; 


var             : ID
                {
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, $1));
                  $$ = var;
                  /*
                  symEntry *check = ST_lookup($1);
                  int checkV = checkValAgainstParams($1, scope);
                  //we need to see if the param contains the function
                  if(check == NULL && checkV == -1){
                    yyerror("Undeclared Variable");
                  }
                  */
                  //$$ = maketreeWithID(IDENTIFIER, $1);
                }
                | ID LSQ_BRKT addExpr RSQ_BRKT 
                {
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, $1));
                  addChild(var, $3);
                  $$ = var;
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
                ;

expression      : addExpr
                {
                  //tree *expression = maketree(EXPRESSION);
                  //addChild(expression, $1);
                  $$ = $1;
                  //$$ = $1;
                }
                | expression relop addExpr
                {
                  /*
                  tree *expression = maketree(EXPRESSION);
                  addChild($2, $1);
                  addChild(expression, $2);
                  addChild($2, $3);
                  $$ = expression;
                  */
                  $$ = $2;
                  addChild($$, $1);
                  addChild($$, $3);
                }
                ;

relop           : OPER_EQ
                {
                  $$ = maketreeWithVal(RELOP, EQ);
                }
                | OPER_GT 
                {
                  $$ = maketreeWithVal(RELOP, GT);
                }
                | OPER_LT
                {
                  $$ = maketreeWithVal(RELOP, LT);
                }
                | OPER_GTE
                {
                  $$ = maketreeWithVal(RELOP, GTE);
                }
                | OPER_LTE
                {
                  $$ = maketreeWithVal(RELOP, LTE);
                }
                | OPER_NEQ 
                {
                  $$ = maketreeWithVal(RELOP, NEQ);
                }
                ;

addExpr         : term
                {
                  
                  /*
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  $$ = addExpr;
                  */
                  $$ = $1;
                }
                | addExpr addop term
                {
                  /*
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  addChild(addExpr, $2);
                  addChild(addExpr, $3);
                  $$ = addExpr;
                  */
                  $$ = $2;
                  addChild($$,$1);
                  addChild($$,$3);
                  //checkMatch($$);
                }
                ;

addop           : OPER_ADD
                {
                  $$ = maketreeWithVal(ADDOP, ADD);
                }
                | OPER_SUB
                {
                  $$ = maketreeWithVal(ADDOP, SUB);
                }
                ;

term            : factor 
                {
                  /*
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  $$ = term;
                  */
                  $$ = $1;
                }
                | term mulop factor 
                {
                  /*
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  addChild(term, $2);
                  addChild(term, $3);
                  $$ = term;
                  */
                  $$ = $2;
                  addChild($$, $1);
                  addChild($$, $3);
                  //checkMatch($$);
                }
                ;

mulop           : OPER_MUL
                {
                  $$ = maketreeWithVal(MULOP, MUL);
                }
                | OPER_DIV
                {
                  $$ = maketreeWithVal(MULOP, DIV);
                }
                ;

factor          : LPAREN expression RPAREN
                {
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $2);
                  $$ = factor;
                  */
                  $$ = $2;
                }
                | var
                {
                  //check against the type here we have func name.
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                  */
                  $$ = $1;
                }
                | funcCallExpr
                {
                /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                */
                  //ST_lookup, we'll need to check the params, probably best to just check the children
                  //we don't know how many arguments a function call can have.
                  //at least if the children is greater than the number of arguments from symEntry then we just need to know the size of the params list
                  //how do we check the list?, well if we pass in the tree node then we can simply check the children since they are not nested.
                  $$ = $1;
                }
                | INTCONST
                {
                  
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(INTEGER, $1));
                  $$ = factor;
                  */
                  $$ = maketreeWithVal(INTEGER, $1);
                }
                | CHARCONST
                {
                  
                  /*
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(CHAR, $1));
                  $$ = factor;
                  */
                  $$ = maketreeWithVal(CHAR, $1);
                }
                ;

funcCallExpr    : ID LPAREN argList RPAREN
                {
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, $1));
                  addChild(funcCallExpr, $3);
                  symEntry *funcName = ST_lookup($1);
                  if(strcmp("output", $1)){
                    if(funcName != NULL){
                      int sz = paramSize(funcName, $1);
                      if($3->numChildren < sz){
                        //too many arguments
                        yyerror("too few arguments for function call");
                      }else if($3->numChildren > sz){
                        yyerror("Too many arguments");
                      }else{
                        //start checking the children
                        for(int i = 0; i < $3->numChildren; i++){
                          //for each children check the param and value
                          // check the value, and the symbal type
                          param *params = funcName->params;
                          char *id = $3->children[i]->nodeName;
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
                  $$ = funcCallExpr;
                }
                | ID LPAREN RPAREN
                {
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, $1));
                  symEntry *funcName = ST_lookup($1);
                  if(funcName == NULL){
                    //throw an error
                    yyerror("Undeclared Function");
                  }
                  $$ = funcCallExpr;
                }
                ;

argList         : expression
                {
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, $1);
                  $$ = argList;
                  //$$ = $1;
                }
                | argList COMMA expression
                {
                /*
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, $1);
                  addChild(argList, $3);
                  $$ = argList;
                  */
                  $$ = $1;
                  addChild($$, $3);
                }
                ;
%%

int yywarning(char * msg){
    printf("warning: line %d: %s\n", yylineno, msg);
    return 0;
}


int yyerror(char * msg){
    printf("error: line %d: %s\n", yylineno, msg);
    return 0;
}
