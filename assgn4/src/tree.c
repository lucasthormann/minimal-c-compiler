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

enum mathOP {
  ADD,
  SUB,
  MUL,
  DIV
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
  this->match = 0;
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
  this->match = 0;
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
  this->match = 0;
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

char *getID(tree *node){
  return node->children[1]->nodeName;
}
//int int
//int mul
//int add
//mul add
//mul mul
//add add
//
void performMaths(tree *node){
  if(node->children[0]->nodeKind == INTEGER && node->children[1]->nodeKind == INTEGER){
    if(node->nodeKind == MULOP){
      if(node->val == MUL){
       node->mathVal = node->children[0]->val * node->children[1]->val; 
      }
      else{
       node->mathVal = node->children[0]->val / node->children[1]->val; 
      }
    }
    else if(node->nodeKind == ADDOP){
      if(node->val == ADD){
       node->mathVal = node->children[0]->val + node->children[1]->val; 
      }
      else{
       node->mathVal = node->children[0]->val - node->children[1]->val; 
      }
    } 
  }
  else if(node->children[0]->nodeKind == CHAR || node->children[1]->nodeKind == CHAR){
    return;
  } 
}

void checkMatch(tree *currTree){
  if((currTree->children[0]->nodeKind == ADDOP || currTree->children[0]->nodeKind == MULOP) && (currTree->children[1]->nodeKind == ADDOP || currTree->children[1]->nodeKind == MULOP)){
    //both children are math operations check if one or the other is a mismatch
    if(currTree->children[0]->match == MISSMATCH || currTree->children[1]->match == MISSMATCH){
      currTree->match = MISSMATCH;
    }
  }else if(currTree->children[0]->nodeKind == MULOP || currTree->children[0]->nodeKind == ADDOP){
    //child 0 is a math operation check operation match
    switch(currTree->children[0]->match){
      case MISSMATCH:
        currTree->match = MISSMATCH;
        break;
    }
  }else if(currTree->children[1]->nodeKind == MULOP || currTree->children[1]->nodeKind == ADDOP){
    //child at index 1 is math operation check match
    switch(currTree->children[1]->match){
      case MISSMATCH:
        currTree->match = MISSMATCH;
        break;
    }
  }else{
    //neither of the children are math operations
    //if both nodes are identifiers
    if((currTree->children[0]->nodeKind == IDENTIFIER) && (currTree->children[1]->nodeKind == IDENTIFIER)){
      //check the type of both against each other
      symEntry *lhs = ST_lookup(currTree->children[0]->nodeName);
      symEntry *rhs = ST_lookup(currTree->children[1]->nodeName);
      if(lhs->data_type != rhs->data_type){
        currTree->match = MISSMATCH;
      }
    }else if(currTree->children[0]->nodeKind == IDENTIFIER){ //child 0 is an identifier
      //check the type of 0 to 1 
      //child 1 can have void, char, and integer
      symEntry *lhs = ST_lookup(currTree->children[0]->nodeName);
      int rhs = -1;
      switch(currTree->children[1]->nodeKind){
        case INTEGER:
          rhs = INT_TYPE;
          break;
        case CHAR:
          rhs = CHAR_TYPE;
          break;
        case VOID:
          rhs = VOID_TYPE;
          break;
        default:
          rhs = -900;
      }
      if(lhs->data_type != rhs){
        currTree->match = MISSMATCH;
      }
    }else if(currTree->children[1]->nodeKind == IDENTIFIER){ //child 1 is an identifier
      //check the type of 1 to 0
      symEntry *rhs = ST_lookup(currTree->children[1]->nodeName);
      int lhs = -1;
      switch(currTree->children[0]->nodeKind){
        case INTEGER:
          lhs = INT_TYPE;
          break;
        case CHAR:
          lhs = CHAR_TYPE;
          break;
        case VOID:
          lhs = VOID_TYPE;
          break;
        default:
          lhs = -900;
      }
      if(rhs->data_type != lhs){
        currTree->match = MISSMATCH;
      }
    }else{ // neither child is an identifier
      if(currTree->children[0]->nodeKind != currTree->children[0]->nodeKind){
        currTree->match = MISSMATCH;
      }
    }
  }
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
        printf("integer LITERAL <%d>\n", node->val);
        break;
      case IDENTIFIER:
        printf("Identifier, <%s>\n", node->nodeName);
        break;
      case CHAR:
        printf("char <%c>\n", (char)node->val);
        break;
      case VOID:
        printf("void , <>");
      case FUNDECL:
        printf("FUNDECL: Number of children is %d\n", node->numChildren);
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
