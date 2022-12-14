%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../src/tree.h"
#include"../src/strtab.h"

extern int yylineno;
/* nodeTypes refer to different types of internal and external nodes that can be part of the abstract syntax tree.*/
enum nodeTypes {PROGRAM=0, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME, VOID};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

/* NOTE: mC has two kinds of scopes for variables : local and global. Variables declared outside any
function are considered globals, whereas variables (and parameters) declared inside a function foo are local to foo. You should update the scope variable whenever you are inside a production that matches function definition (funDecl production). The rationale is that you are entering that function, so all variables, arrays, and other functions should be within this scope. You should pass this variable whenever you are calling the ST_insert or ST_lookup functions. This variable should be updated to scope = "" to indicate global scope whenever funDecl finishes. Treat these hints as helpful directions only. You may implement all of the functions as you like and not adhere to my instructions. As long as the directory structure is correct and the file names are correct, we are okay with it. */
char* scope = "";
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

%type <node> program declList decl vardecl typeSpecifier funDecl fundPre formalDeclList formalDecl funBody localDeclList statementList statement assignStmt var expression loopStmt returnStmt compoundStmt condStmt addExpr term addop factor mulop relop funcCallExpr argList

%start program

%%
/* TODO: Your grammar and semantic actions go here. We provide with two example productions and their associated code for adding non-terminals to the AST.*/

program         : { new_scope(); } declList 
                 {
                    tree* progNode = maketree(PROGRAM);
                    //addChild(progNode, $1);
                    addChild(progNode, $2);
                    ast = progNode;
                 }
                ;

declList        : decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    $$ = declListNode;
                 }
                | declList decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                 }
                ;

decl            : vardecl
                {
                  tree* decl = maketree(DECL);
                  addChild(decl, $1);
                  $$ = decl;
                }
                | funDecl
                {
                  tree *decl = maketree(DECL);
                  addChild(decl, $1);
                  $$ = decl;
                }
                ;

vardecl         : typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN 
                {
                  tree *vardeclNode = maketree(VARDECL);
                  addChild(vardeclNode, $1);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER, $2));
                  addChild(vardeclNode, maketreeWithVal(INTEGER, $4));
                  ST_insert($2, "", $1->val, ARRAY, $4);
                  $$ = vardeclNode;
                }
                | typeSpecifier ID SEMICLN
                {
                  tree *vardeclNode = maketree(VARDECL);
                  addChild(vardeclNode, $1);
                  addChild(vardeclNode, maketreeWithID(IDENTIFIER,$2));
                  ST_insert($2, "", $1->val, SCALAR, 0);
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

funDecl		      : fundPre LPAREN formalDeclList RPAREN funBody
                {
                  $$ = $1;
                  addChild($$, $3);
                  connect_params($$->children[1]->id, "global");
                  addChild($$, $5);
                  //get the entry for the function from global
                  //we need to get the id and scope, the scope is global.
                  //we connect the params
                  
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
                  tree *fundPre = maketree(FUNDECL);
                  addChild(fundPre, $1);
                  addChild(fundPre, maketreeWithID(IDENTIFIER, $2));
                  new_scope();
                  $$ = maketree(FUNDECL);
                }
                ;

formalDeclList  : formalDecl
                {	
                  tree* formalDeclListNode = maketree(FORMALDECLLIST);
                  addChild(formalDeclListNode, $1);
                  addParam($1->type, $1->sym_type);
                  $$ = formalDeclListNode;
                }
                | formalDecl COMMA formalDeclList
                {
                  tree* formalDeclListNode = maketree(FORMALDECLLIST);
                  addChild(formalDeclListNode, $1);
                  addChild(formalDeclListNode, $3);
                  $$ = formalDeclListNode;
                }
                ;

formalDecl	    : typeSpecifier ID
                {
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, $1);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, $2));
                  //ST_insert($2, "", $1->val, SCALAR, 0);
                  addParam($1->data_type, SCALAR);
                  $$ = formalDeclNode;
                  //new_scope();
                }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                {
                  tree* formalDeclNode = maketree(FORMALDECL);
                  addChild(formalDeclNode, $1);
                  addChild(formalDeclNode, maketreeWithID(IDENTIFIER, $2));
                  addParam($1->data_type, ARRAY);
                  //ST_insert($2, "", $1->val, ARRAY, 0);
                  $$ = formalDeclNode;
                  //new_scope();
                }
                ;

funBody         : LCRLY_BRKT localDeclList statementList RCRLY_BRKT 
                {
                  tree *funBody = maketree(FUNBODY);
                  addChild(funBody, $2);
                  addChild(funBody, $3);
                  $$ = funBody;
                }
                ;

localDeclList   :
                {
                  $$ = NULL;
                }
                | vardecl localDeclList
                {
                  tree *localDeclList = maketree(LOCALDECLLIST);
                  addChild(localDeclList, $1);
                  addChild(localDeclList, $2);
                  $$ = localDeclList;
                }
                ;

statementList   :
                {
                  $$ = NULL;
                }
                | statement statementList
                {
                  tree *statementList = maketree(STATEMENTLIST);
                  addChild(statementList, $1);
                  addChild(statementList, $2);
                  $$ = statementList;
                }
                ;

statement       : compoundStmt
                {
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                }
                | assignStmt
                {
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                }
                | condStmt
                { 
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                }
                | loopStmt
                {
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                }
                | returnStmt
                {
                  tree *statement = maketree(STATEMENT);
                  addChild(statement, $1);
                  $$ = statement;
                }
                ;

loopStmt        : { new_scope(); } KWD_WHILE LPAREN expression RPAREN statement
                {
                  tree *loopStmt = maketree(LOOPSTMT);
                  addChild(loopStmt, $4);
                  addChild(loopStmt, $6);
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
                }
                ;

assignStmt      : var OPER_ASGN expression SEMICLN
                {
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, $1);
                  addChild(assignStmt, $3);
                  $$ = assignStmt;
                }
                | expression SEMICLN
                {
                  tree *assignStmt = maketree(ASSIGNSTMT);
                  addChild(assignStmt, $1);
                  $$ = assignStmt;
                }
                ;

condStmt        : KWD_IF LPAREN expression RPAREN statement
                { 
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, $3);
                  addChild(condStmt, $5);
                  up_scope();
                  $$ = condStmt;
                }
                | KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement
                {
                  tree *condStmt = maketree(CONDSTMT);
                  addChild(condStmt, $3);
                  addChild(condStmt, $5);
                  addChild(condStmt, $7);
                  up_scope();
                  $$ = condStmt;
                }
                ; 


var             : ID
                {
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, $1));
                  $$ = var;
                }
                | ID LSQ_BRKT addExpr RSQ_BRKT 
                {
                  tree *var = maketree(VAR);
                  addChild(var, maketreeWithID(IDENTIFIER, $1));
                  addChild(var, $3);
                  $$ = var;
                }
                ;

expression      : addExpr
                {
                  tree *expression = maketree(EXPRESSION);
                  addChild(expression, $1);
                  $$ = expression;
                }
                | expression relop addExpr
                {
                  tree *expression = maketree(EXPRESSION);
                  addChild(expression, $1);
                  addChild(expression, $2);
                  addChild(expression, $3);
                  $$ = expression;
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
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  $$ = addExpr;
                }
                | addExpr addop term
                {
                  tree *addExpr = maketree(ADDEXPR);
                  addChild(addExpr, $1);
                  addChild(addExpr, $2);
                  addChild(addExpr, $3);
                  $$ = addExpr;
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
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  $$ = term;
                }
                | term mulop factor 
                {
                  tree *term = maketree(TERM);
                  addChild(term, $1);
                  addChild(term, $2);
                  addChild(term, $3);
                  $$ = term;
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
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $2);
                  $$ = factor;
                }
                | var
                {
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                }
                | funcCallExpr
                {
                  tree *factor = maketree(FACTOR);
                  addChild(factor, $1);
                  $$ = factor;
                }
                | INTCONST
                {
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(INTEGER, $1));
                  $$ = factor;
                }
                | CHARCONST
                {
                  tree *factor = maketree(FACTOR);
                  addChild(factor, maketreeWithVal(CHAR, $1));
                  $$ = factor;
                }
                ;

funcCallExpr    : ID LPAREN argList RPAREN
                {
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, $1));
                  addChild(funcCallExpr, $3);
                  //st_lookup plays here
                  $$ = funcCallExpr;
                }
                | ID LPAREN RPAREN
                {
                  tree *funcCallExpr = maketree(FUNCCALLEXPR);
                  addChild(funcCallExpr, maketreeWithID(IDENTIFIER, $1));
                  //st_lookup plays here
                  $$ = funcCallExpr;
                }
                ;

argList         : expression
                {
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, $1);
                  $$ = argList;
                }
                | argList COMMA expression
                {
                  tree *argList = maketree(ARGLIST);
                  addChild(argList, $1);
                  addChild(argList, $3);
                  $$ = argList;
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
