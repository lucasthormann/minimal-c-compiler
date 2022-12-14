#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nodeNames[32] = {
    "PROGRAM",      "DECLLIST",      "DECL",           "VARDECL",
    "TYPESPEC",     "FUNDECL",       "FORMALDECLLIST", "FORMALDECL",
    "FUNBODY",      "LOCALDECLLIST", "STATEMENTLIST",  "STATEMENT",
    "COMPOUNDSTMT", "ASSIGNSTMT",    "CONDSTMT",       "LOOPSTMT",
    "RETURNSTMT",   "EXPRESSION",    "RELOP",          "ADDEXPR",
    "ADDOP",        "TERM",          "MULOP",          "FACTOR",
    "FUNCCALLEXPR", "ARGLIST",       "INTEGER",        "IDENTIFIER",
    "VAR",          "ARRAYDECL",     "CHAR",           "FUNCTYPENAME"};

enum dataType {INT_TYPE, CHAR_TYPE, VOID_TYPE};
enum symbolType {SCALAR, ARRAY, FUNCTION};

enum nodeKinds {
  PROGRAM,
  DECLLIST,
  DECL,
  VARDECL,
  TYPESPEC,
  FUNDECL,
  FORMALDECLLIST,
  FORMALDECL,
  FUNBODY,
  LOCALDECLLIST,
  STATEMENTLIST,
  STATEMENT,
  COMPOUNDSTMT,
  ASSIGNSTMT,
  CONDSTMT,
  LOOPSTMT,
  RETURNSTMT,
  EXPRESSION,
  RELOP,
  ADDEXPR,
  ADDOP,
  TERM,
  MULOP,
  FACTOR,
  FUNCCALLEXPR,
  ARGLIST,
  INTEGER,
  IDENTIFIER,
  VAR,
  ARRAYDECL,
  CHAR,
  FUNCTYPENAME,
  VOID
};

tree *ast; /* pointer to AST root */

//make tree constructs a tree with a nodeKind value
//returns the tree that has been constructed
tree *maketree(int kind) {
  if(kind < 0 || kind > 31){
    return NULL;
  }
  tree *this = (tree *)malloc(sizeof(struct treenode));
  this->nodeKind = kind;
  this->numChildren = 0;
  return this;
}

//maketreeWithVal makes a tree wtih a nodeKind and sets val for a treenode struct
//returns the tree that has been constructed
tree *maketreeWithVal(int kind, int val) {
  if(kind < 0 || kind > 31){
    return NULL;
  }
  tree *this = (tree *)malloc(sizeof(struct treenode));
  this->nodeKind = kind;
  this->numChildren = 0;
  this->val = val;
  return this;
}

//maketreeWithVal makes a tree wtih a nodeKind and sets the id for a treenode struct
//returns the tree that has been constructed
tree *maketreeWithID(int kind, char *name) {
  tree *this = (tree *)malloc(sizeof(struct treenode));
  if(kind < 0 || kind > 31){
    return NULL;
  }
  this->nodeKind = kind;
  this->numChildren = 0;
  this->nodeName = name;
  return this;
}

//addChild adds a child given a parent node
//will not add a child if the parent or child are NULL
void addChild(tree *parent, tree *child) {
  if (child == NULL || parent == NULL){
    return;
  }
  if (parent->numChildren == MAXCHILDREN) {
    printf("Cannot add child to parent node\n");
    exit(1);
  }
  nextAvailChild(parent) = child;
  parent->numChildren++;
}

//printAst prints the entire tree structure given a treenode
void printAst(tree *node, int nestLevel) {
  if (node != NULL) {
    if(nestLevel > 1){
      fprintf(stdout, "%*s", nestLevel*2, "");
    }
    if (node->nodeKind > 31 || node->nodeKind < 0){
      printf("Crashed here\n");
      return;
    }
    switch (node->nodeKind) {
      case ADDOP:
        switch(node->val){
          case 0:
            printf("Addop +\n");
            break;
          case 1:
            printf("Addop -\n");
            break;
        }
        break;
      case MULOP:
        switch(node->val){
          case 2:
            printf("Mulop *\n");
            break;
          case 3:
            printf("Mulop /\n");
            break;
        }
        break;
      case INTEGER:
        printf("integer <%d>\n", node->val);
        break;
      case IDENTIFIER:
        printf("Identifier, <%s>\n", node->nodeName);
        break;
      case CHAR:
        printf("<%c>\n", (char)node->val);
        break;
      case FUNCTYPENAME:
        break;
      case TYPESPEC:
        switch(node->val){
          case INT_TYPE:
            printf("typespecifier, int\n");
            break;
          case CHAR_TYPE:
            printf("typespecifier, char\n");
            break;
          case VOID_TYPE:
            printf("typespecifier, void\n");
            break;
        }
        break;
      default:
        if (node->nodeKind > 31 || node->nodeKind < 0){
          printf("what is going on here?\n");
        }else{
          printf("%s\n", nodeNames[node->nodeKind]);
        }
    }
    int i, j;

    for (i = 0; i < node->numChildren; i++) {
      printAst(getChild(node, i), nestLevel + 1);
    }
  }
}
